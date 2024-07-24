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

    

    DataWriter::DataWriter():ThreadPool(0,4,6){
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
        stringstream ss;
        shared_ptr<Quote> nquote = static_pointer_cast<Quote>(quote);
        if(!nquote){
            logger_->info("error");
            return;
        }
        TSLMDBPtr db = get_q_db(nquote->exg_, nquote->code_);
        TSQryLMDB query(*db); // create a query object
        logger_->info(nquote->exg_);
        vector<string> temp;
        split(nquote->time_,' ',temp);
        LMDBKey key (nquote->exg_, nquote->code_, temp[0].data(), temp[1].data());
        if(!query.put_and_commit(key.getString(), nquote->getString())){
            logger_->error(fmt::format("wrtie tick of {} error {}", nquote->code_, db->errmsg()).c_str());
        }
    }

    void DataWriter::WriteDataBase(){
        string path;
        int count = 0;
        std::time_t temp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        stringstream ss;
        ss << std::put_time(std::localtime(&temp), "%Y_%m_%d");
        string time = ss.str();
        for(auto i = quote_dbs_.begin(); i!=quote_dbs_.end(); i++){
            path = fmt::format("{}/{}/{}", BASE_FILE_LOC, i->first, time);
            boost::filesystem::create_directories(path);
            std::ofstream file(path+".csv");
            file<<"key,data\n";
            TSQryLMDB query(*i->second);
            count  = query.get_all([&file](const ValueArray& key, const ValueArray& val){
                for(int i = 0; i<key.size()-1; i++){
                    file<<key[i]<<','<<val[i]<<'\n';
                }
            });
            logger_->info(fmt::format("Writting {} of data from {} into csv", count-1, i->first).c_str());
        }
        logger_->info("Finish writting all data into csv");   
    }




    DataWriter::TSLMDBPtr DataWriter::get_q_db(const char* exg, const char* code){
        
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