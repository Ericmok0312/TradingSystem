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
        logger_ = Logger::getInstance("DataReader");
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
        
        TSLMDBPtr db = get_q_db(arg->exg, arg->code, this->quote_dbs_, QUOTE);
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



    //copy of readQuoteSlicefromLMDB, but change to read from the most current data
     void DataReader::readCurQuoteSlicefromLMDB(shared_ptr<ARG> arg){
        char* temp = new char[strlen(arg->exg)+strlen(arg->code)+2];
        strcpy(temp, arg->exg);
        strcat(temp, "/");
        strcat(temp, arg->code);
        uint32_t count = arg->count;
        arg->etime = GetTimeStamp();
        QuoteList& quotelist = quote_cache_[temp];
        uint64_t last_access_time = 0;
        uint32_t reload_flag = 0;
        do
        {
            if (quotelist.quotes_.capacity()<count){ // cache size is smaller than required
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
        
        TSLMDBPtr db = get_q_db(arg->exg, arg->code, this->quote_dbs_, QUOTE);
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


    //this function will not modify cache and will not read from cache, might need to think of new way of caching
    void DataReader::readHistKlineSlicefromLMDB(shared_ptr<ARG> arg){
        char* temp = new char[strlen(arg->exg)+strlen(arg->code)+2];
        strcpy(temp, arg->exg);
        strcat(temp, "/");
        strcat(temp, arg->code);
        uint32_t count = arg->count;


        
        KlineCache* cache;
        switch(arg->type){
            case KLINE_1D:
                cache = &d1_kline_hist_cache_;
                break;
            case KLINE_1MIN:
                cache = &m1_kline_hist_cache_;
                break;
            default:
                cache = &m5_kline_hist_cache_;
                break;
        }

        
        KlineList& klinelist = (*cache)[temp];

        auto startit = lower_bound(klinelist.klines_.begin(), klinelist.klines_.end(), Date2TimeStamp(arg->start), 
        [](const Kline& a, const uint64_t& val){return a.updateTimestamp_<val;});

        auto endit = upper_bound(klinelist.klines_.begin(), klinelist.klines_.end(), Date2TimeStamp(arg->end), 
        [](const uint64_t& val, const Kline& a){return a.updateTimestamp_>val;});

        int flag;

        if(klinelist.klines_.empty()){ // no data
            flag = 0;
        }
        else if(startit!=klinelist.klines_.begin()&&startit!=klinelist.klines_.end()&&endit!=klinelist.klines_.begin()&&endit!=klinelist.klines_.end()){ //range of cache larger than required
            flag = 1;
        }
        else if(startit == klinelist.klines_.begin() && endit!=klinelist.klines_.begin() && endit != klinelist.klines_.end()){
            flag = 2;
        } // got some/none of the data, but some earlier data are needed
        else if(startit != klinelist.klines_.begin()&&startit!=klinelist.klines_.end() && endit==klinelist.klines_.end()){
            flag = 3;
        } // got some/none of the data, but some later data are needed
        else if(startit == klinelist.klines_.begin()&&startit==klinelist.klines_.end()){
            flag = 4;
        } // got some of the data but both the earlier and later data are needed
  
        delete[] temp;
        cout<<flag<<endl;
        TSLMDBPtr db;
        switch(arg->type){
            case KLINE_1D:
                db = get_q_db(arg->exg, arg->code, kline_d1_dbs_, arg->type);
                break;
            case KLINE_1MIN:
                db = get_q_db(arg->exg, arg->code, kline_m1_dbs_, arg->type);
                break;
            default:
                db = get_q_db(arg->exg, arg->code, kline_m5_dbs_, arg->type);
                break;
        }
        if(db == nullptr) return;
        
        TSQryLMDB query(*db);
        KlineSlice* ret;
        int cnt;
        switch(flag){
            case 0:
            { 
                LMDBKey lkey(arg->exg, arg->code, Date2TimeStamp(arg->start));
                LMDBKey rkey(arg->exg, arg->code, Date2TimeStamp(arg->end));
                
                cnt = query.get_range(lkey.getString(), rkey.getString(), [this, &klinelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                    for(const std::string& item: ayVals){
                        if(klinelist.klines_.size() == klinelist.klines_.capacity()){
                            klinelist.klines_.resize(klinelist.klines_.size()*2);
                        }
                        Kline q(item);
                        klinelist.klines_.push_back(q);
                    }
                });
                ret = KlineSlice::create(arg->code, &klinelist.klines_[0], cnt);
                break;
            }
            case 1:
            {
                ret = KlineSlice::create(arg->code, &(*startit), std::distance(startit, endit)+1);
                break;
            }
            case 2:
            {
                LMDBKey lkey(arg->exg, arg->code, Date2TimeStamp(arg->start));
                LMDBKey rkey(arg->exg, arg->code, startit->updateTimestamp_);
                cnt = distance(startit, endit)+1;
                cnt += query.get_range(lkey.getString(), rkey.getString(), [this, &klinelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                    for(const std::string& item: ayVals){
                        if(klinelist.klines_.size() == klinelist.klines_.capacity()){
                            klinelist.klines_.resize(klinelist.klines_.size()*2);
                        }
                        Kline q(item);
                        klinelist.klines_.push_front(q);
                    }
                });
                ret = KlineSlice::create(arg->code, &klinelist.klines_[0], cnt);
                break;
            }
            case 3:
            {
                LMDBKey lkey(arg->exg, arg->code, endit->updateTimestamp_);
                LMDBKey rkey(arg->exg, arg->code, Date2TimeStamp(arg->end));
                cnt = distance(startit, endit)+1;
                cnt += query.get_range(lkey.getString(), rkey.getString(), [this, &klinelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                    for(const std::string& item: ayVals){
                        if(klinelist.klines_.size() == klinelist.klines_.capacity()){
                            klinelist.klines_.resize(klinelist.klines_.size()*2);
                        }
                        Kline q(item);
                        klinelist.klines_.push_back(q);
                    }
                });
                ret = KlineSlice::create(arg->code, &(*startit), cnt);
                break;
            }
            case 4:
            {
                LMDBKey lkey(arg->exg, arg->code, Date2TimeStamp(arg->start));
                LMDBKey rkey(arg->exg, arg->code, klinelist.klines_.begin()->updateTimestamp_);
                cnt = distance(startit, endit)+1;
                cnt += query.get_range(lkey.getString(), rkey.getString(), [this, &klinelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                    for(const std::string& item: ayVals){
                        if(klinelist.klines_.size() == klinelist.klines_.capacity()){
                            klinelist.klines_.resize(klinelist.klines_.size()*2);
                        }
                        Kline q(item);
                        klinelist.klines_.push_front(q);
                    }
                });

                LMDBKey lkey2(arg->exg, arg->code, (klinelist.klines_.end()-1)->updateTimestamp_);
                LMDBKey rkey2(arg->exg, arg->code, Date2TimeStamp(arg->end));
                cnt += query.get_range(lkey2.getString(), rkey2.getString(), [this, &klinelist](const ValueArray& ayKeys, const ValueArray& ayVals){
                    for(const std::string& item: ayVals){
                        if(klinelist.klines_.size() == klinelist.klines_.capacity()){
                            klinelist.klines_.resize(klinelist.klines_.size()*2);
                        }
                        Kline q(item);
                        klinelist.klines_.push_back(q);
                    }
                });
                ret = KlineSlice::create(arg->code, &klinelist.klines_[0], cnt);
                break;
            }
        }

        stringstream ss;
        ss<<ret;
        arg->callback(move(ss.str()), move(arg->des));
    }






    DataReader::TSLMDBPtr DataReader::get_q_db(const char* exg, const char* code, TSLMDBMap& source, SubType type){
        
        uint64_t init = GetTimeStamp();
        string key = fmt::format("{}/{}", exg, code);

        auto it = source.find(key);
        if(it != source.end()){
            if(IS_BENCHMARK)
                logger_->info(fmt::format("Get_q_db latency: {}", to_string(GetTimeStamp()-init)).c_str());
            return it->second; 
        }

        TSLMDBPtr dbPtr(new TsLMDB(false)); // not found

        string tn;
        switch (type)
        {
        case QUOTE:
            tn = move("QUOTE");
            break;
        case KLINE_1D:
            tn = move("KLINE_1D");
            break;
        case KLINE_1MIN:
            tn = move("KLINE_1MIN");
            break;
        default:
            tn = move("UNKOWN");
            break;
        }
        std::string path = fmt::format("{}/{}/{}/{}", BASE_FILE_LOC, tn, exg, code); //create the dir

        boost::filesystem::create_directories(path);

        if(!dbPtr->open(path.c_str())){
            logger_->error(fmt::format("Opening quote db at {} failed: {}", path, dbPtr->errmsg()).c_str());
            return std::move(TSLMDBPtr()); // return an empty one;
        }
        std::lock_guard<mutex> lock (q_db_mutex); // modifying unordered map
        source[key] = dbPtr;
        if(IS_BENCHMARK)
        logger_->info(fmt::format("Get_db latency: {}", to_string(GetTimeStamp()-init)).c_str());
        return dbPtr;
    }   


}