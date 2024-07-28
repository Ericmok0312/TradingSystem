#include <DataManager/DataWriter.h>
#include <boost/filesystem.hpp>
#include <DataManager/LMDBKeys.h>
#include <Helper/util.h>
#include <Helper/ThreadPool.hpp>
#include <chrono>
#include <iomanip>

namespace ts{




    std::mutex DataWriter::q_db_mutex;
    std::mutex DataWriter::getIns_mutex;
    shared_ptr<DataWriter> DataWriter::instance_ = nullptr;

    

    DataWriter::DataWriter():ThreadPool(0,12,1){
        init();
    }


    DataWriter::~DataWriter(){
        logger_->info("Destructing DataWriter");
        WriteDataBase();
        instance_.reset();
        //sleep(4);
    }

    void DataWriter::init(){
        logger_ = make_unique<Logger>("DataWriter");;
    }


    shared_ptr<DataWriter> DataWriter::getInstance(){
        std::lock_guard<mutex> lock(getIns_mutex);
        if(!instance_){
            instance_ = make_shared<DataWriter>();
        }
        return instance_;
    }


    void DataWriter::WriteQuote(std::shared_ptr<BaseData> quote){
        uint64_t init = GetTimeStamp();
        stringstream ss;
        shared_ptr<Quote> nquote = static_pointer_cast<Quote>(quote);
        if(!nquote){
            logger_->info("error");
            return;
        }
        TSLMDBPtr db = get_q_db(nquote->exg_, nquote->code_);
        
        TSQryLMDB query(*db); // create a query object
        
        LMDBKey key (nquote->exg_, nquote->code_, nquote->timestamp_);
        
        if(!query.put_and_commit(move(key.getString()), move(nquote->getString()))){
            logger_->error(fmt::format("wrtie tick of {} error {}", nquote->code_, db->errmsg()).c_str());
        }
        if (IS_BENCHMARK) {
            logger_->info(fmt::format("WriteQuote latency final: {}", to_string(GetTimeStamp()-init)).c_str());
            logger_->info(fmt::format("Total latency final: {}", to_string(GetTimeStamp()-nquote->timestamp_)).c_str());}
    }

    void DataWriter::WriteDataBase(){
        string path;
        int count = 0;
        std::time_t temp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        stringstream ss;
        ss << std::put_time(std::localtime(&temp), "%Y_%m_%d");
        string time = ss.str();

        auto now = std::chrono::system_clock::now();
        time_t now_c = std::chrono::system_clock::to_time_t(now);
        tm* localTime = localtime(&now_c);

        localTime->tm_hour = 0;
        localTime->tm_min = 0;
        localTime->tm_sec = 0;
        string midtime = to_string(mktime(localTime));

        localTime->tm_hour = 23;
        localTime->tm_min = 59;
        localTime->tm_sec = 59;

        string endtime = to_string(mktime(localTime));
        logger_->warn(endtime.c_str());
        for(auto i = quote_dbs_.begin(); i!=quote_dbs_.end(); i++){
            path = fmt::format("{}/{}/{}", BASE_FILE_LOC, i->first, time);
            boost::filesystem::create_directories(path);
            std::ofstream file(path+"/data.csv");
            file<<"key,data\n";
            TSQryLMDB query(*i->second);
            string lkey = i->first+"/"+move(midtime);
            string rkey = i->first+"/"+ move(endtime);
            count  = query.get_all([&file](const ValueArray& key, const ValueArray& val){
                for(int i = 0; i<val.size(); i++){
                    file<<key[i]<<','<<val[i]<<'\n';
                }
            });
            logger_->info(fmt::format("Writting {} of data from {} into csv", count, i->first).c_str());
        }
        logger_->info("Finish writting all data into csv");   
    }




    DataWriter::TSLMDBPtr DataWriter::get_q_db(const char* exg, const char* code){
        uint64_t init = GetTimeStamp();
        string key = fmt::format("{}/{}", exg, code);

        auto it = quote_dbs_.find(key);
        if(it != quote_dbs_.end()){
            if(IS_BENCHMARK)
                logger_->info(fmt::format("Get_q_db latency: {}", to_string(GetTimeStamp()-init)).c_str());
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
        if(IS_BENCHMARK)
        logger_->info(fmt::format("Get_q_db latency: {}", to_string(GetTimeStamp()-init)).c_str());
        return dbPtr;
    }



}