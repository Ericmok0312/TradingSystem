#include <DataManager/DataReader.h>
#include <boost/filesystem.hpp>
#include <DataManager/LMDBKeys.h>
#include <Helper/util.h>


namespace ts{


    shared_ptr<DataReader> DataReader::instance_ = nullptr;
    std::shared_ptr<ts::Logger> DataReader::logger_ = nullptr;
    std::mutex DataReader::q_db_mutex;
    std::mutex DataReader::getIns_mutex;

    DataReader::DataReader():ThreadPool(1,4,6){
        init();
    }

    DataReader::~DataReader(){}

    void DataReader::init(){
        logger_ = make_shared<Logger>("DataReader");
    }


    shared_ptr<DataReader> DataReader::getInstance(){
        std::lock_guard<mutex> lock(getIns_mutex);
        if(!instance_){
            instance_ = make_shared<DataReader>();
        }
        return instance_;
    }


    QuoteSlice* DataReader::readQuoteSlicefromLMDB(const char* exg, const char* code, uint32_t count, uint64_t etime){
        char* temp = new char[strlen(exg)+strlen(code)+2];
        strcpy(temp, exg);
        strcat(temp, "/");
        strcat(temp, code);
        
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

            if (quotelist.last_req_time_ < etime){ // data stored is earlier than etime
                reload_flag = 1;
                last_access_time = quotelist.last_req_time_;
                break;
            }
        } while (false);
        
        TSLMDBPtr db = get_q_db(exg, code);
        if(db == nullptr) return NULL;
        if (reload_flag == 1){
            TSQryLMDB query(*db);
            last_access_time += 1;
            LMDBKey lkey(exg, code, to_string(last_access_time/1000000000).data(), to_string(last_access_time%1000000000).data());
            LMDBKey rkey(exg, code, to_string(etime/1000000000).data(), to_string(etime%1000000000).data());
            int count = query.get_range(lkey.getString(), rkey.getString(), [this, &quotelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                for(const std::string& item: ayVals){
                    Quote* curtick = (Quote*)item.data();
                    quotelist.quotes_.push_back(*curtick);
                }
            });
            if(count > 0) logger_->info(fmt::format("{} ticks after {} of stock {} append to cache", count, last_access_time, code).c_str());
        }
        else if(reload_flag == 2){
            TSQryLMDB query(*db);
            LMDBKey lkey(exg, code, 0, 0);
            LMDBKey rkey(exg, code, to_string(etime/1000000000).data(), to_string(etime%1000000000).data());
            int count = query.get_lowers(lkey.getString(), rkey.getString(), count, [this, &quotelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                quotelist.quotes_.resize(ayVals.size());
                for(std::size_t i=0; i<ayVals.size(); i++){
                    const string& item = ayKeys[i];
                    memcpy(&quotelist.quotes_[i], item.data(), item.size());
                }
            });

            logger_->info(fmt::format("{} ticks after {} of stock {} loaded to cache for the first time", count, last_access_time, code).c_str());
        }

        quotelist.last_req_time_ = etime;

        count = min((uint32_t)quotelist.quotes_.size(), count);
        auto ayTwo = quotelist.quotes_.array_two(); // getting array of quotes
        auto count_2 = ayTwo.second;
        if(count_2 >=count){
            return QuoteSlice::create(code, &quotelist.quotes_[count_2 - count], count);
        }
        else{
            auto ayOne = quotelist.quotes_.array_one();
            auto diff = count - count_2;
            auto ret = QuoteSlice::create(code, &quotelist.quotes_[ayOne.second - diff], diff);
            if(count_2 > 0) ret->appendBlock(ayTwo.first, count_2);
            return ret;
        }

    }   


}