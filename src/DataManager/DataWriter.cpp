#include <DataManager/DataWriter.h>
#include <boost/filesystem.hpp>
#include <DataManager/LMDBKeys.h>
#include <Helper/util.h>
namespace ts{



    std::shared_ptr<ts::Logger> DataWriter::logger_ = nullptr;


    std::mutex DataWriter::q_db_mutex;
    std::mutex DataWriter::getIns_mutex;
    shared_ptr<DataWriter> DataWriter::instance_ = nullptr;

    

    DataWriter::DataWriter():ThreadPool(1,4,6){
        init();
    }


    DataWriter::~DataWriter(){
    }

    void DataWriter::init(){
        logger_ = make_shared<Logger>("DataWriter");
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

    DataWriter::TSLMDBPtr DataWriter::get_q_db(const char* exg, const char* code){
        
        string key = fmt::format("{}.{}", exg, code);

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