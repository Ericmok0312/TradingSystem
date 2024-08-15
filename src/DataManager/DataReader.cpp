#include <DataManager/DataReader.h>
#include <boost/filesystem.hpp>
#include <DataManager/LMDBKeys.h>
#include <Helper/util.h>


namespace ts{


    shared_ptr<DataReader> DataReader::instance_ = nullptr;
    std::mutex DataReader::q_db_mutex;
    std::mutex DataReader::getIns_mutex;

    DataReader::DataReader():ThreadPool(0, 4, 1){//
        init();
    }

    DataReader::~DataReader(){
        logger_->info("Destructing DataReader");
        instance_.reset();
    }

    void DataReader::init(){
        logger_ = make_unique<Logger>("DataReader");
    }


    shared_ptr<DataReader> DataReader::getInstance(){
        std::lock_guard<mutex> lock(getIns_mutex);
        if(!instance_){
            instance_ = make_shared<DataReader>();
        }
        return instance_;
    }


    void DataReader::readQuoteSlicefromLMDB(shared_ptr<ARG> arg){
        char* temp = new char[strlen(arg->exg)+strlen(arg->code)+2];
        strcpy(temp, arg->exg);
        strcat(temp, "/");
        strcat(temp, arg->code);
        uint32_t count = arg->count;
        QuoteList& quotelist = quote_cache_[temp];
        uint64_t last_access_time = 0;
        uint32_t reload_flag = 0;
        do
        {
            if (quotelist.quotes_.capacity()<count){ // not enough data in cache
                reload_flag = 2;
                quotelist.quotes_.rset_capacity(count);
                quotelist.quotes_.clear();
            }

            if (quotelist.last_req_time_ < arg->etime){ // data stored is earlier than arg->etime
                reload_flag = 1;
                last_access_time = quotelist.last_req_time_;
                break;
            }
        } while (false);
        
        TSLMDBPtr db = get_q_db(arg->exg, arg->code);
        if(db == nullptr) return;
        if (reload_flag == 1){
            TSQryLMDB query(*db);
            last_access_time += 1;
            LMDBKey lkey(arg->exg, arg->code, last_access_time);
            LMDBKey rkey(arg->exg, arg->code, arg->etime);
            int cnt = query.get_range(lkey.getString(), rkey.getString(), [this, &quotelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                for(const std::string& item: ayVals){
                    Quote q(item);
                    quotelist.quotes_.push_back(q);
                }
            });
            if(cnt > 0) logger_->info(fmt::format("{} ticks after {} of stock {} append to cache", cnt, last_access_time, arg->code).c_str());
        }
        else if(reload_flag == 2){
            TSQryLMDB query(*db);
            LMDBKey lkey(arg->exg, arg->code, 0);
            LMDBKey rkey(arg->exg, arg->code, arg->etime);
            int cnt = query.get_lowers(lkey.getString(), rkey.getString(), count, [this, &quotelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                quotelist.quotes_.resize(ayVals.size());
                for(std::size_t i=0; i<ayVals.size(); i++){
                    const string& item = ayKeys[i];
                    memcpy(&quotelist.quotes_[i], item.data(), item.size());
                }
            });

            logger_->info(fmt::format("{} ticks after {} of stock {} loaded to cache for the first time", cnt, last_access_time, arg->code).c_str());
        }
        quotelist.last_req_time_ = arg->etime;
        delete[] temp;
        count = min((uint32_t)quotelist.quotes_.size(), count);
        auto ayTwo = quotelist.quotes_.array_two(); // getting array of quotes
        auto count_2 = ayTwo.second;
        QuoteSlice* ret;
        if(count_2 >= count){
            ret = QuoteSlice::create(arg->code, &quotelist.quotes_[count_2 - count], count);
        }
        else{
            auto ayOne = quotelist.quotes_.array_one();
            auto diff = count - count_2;
            ret = QuoteSlice::create(arg->code, &quotelist.quotes_[ayOne.second - diff], diff);
            if(count_2 > 0) ret->appendBlock(ayTwo.first, count_2);
        }
        stringstream ss;
        ss<<ret;
        arg->callback(move(ss.str()), move(arg->des));
    }

    DataReader::TSLMDBPtr DataReader::get_q_db(const char* exg, const char* code){
        
        string key = fmt::format("{}/{}", exg, code);

        auto it = quote_dbs_.find(key);
        if(it != quote_dbs_.end()){
            return it->second; 
        }

        TSLMDBPtr dbPtr(new TsLMDB(false)); // not found

        std::string path = fmt::format("{}/{}/{}", BASE_FILE_LOC, exg, code); //create the dir

        boost::filesystem::create_directories(path);

        if(!dbPtr->open(path.c_str())){
            logger_->error(fmt::format("Opening quote db at {} failed: {}", path, dbPtr->errmsg()).c_str());
            return std::move(TSLMDBPtr()); // return an empty one;
        }
        std::lock_guard<mutex> lock (q_db_mutex); // modifying unordered map
        quote_dbs_[key] = dbPtr;
        return dbPtr;
    }   


}