#ifndef SRC_DATAMANAGER_DATAWRITER_H
#define SRC_DATAMANAGER_DATAWRITER_H
#include <Helper/ThreadPool.h>
#include <DataManager/tslmdb.hpp>
#include <Helper/logger.h>
#include <rapidjson/document.h>
#include <functional>

namespace ts{

    #define BASE_FILE_LOC "./src/DataBase"

    class DataWriter: public ThreadPool<std::function<void(shared_ptr<BaseData>)>, std::shared_ptr<BaseData>>{
        public:
            friend class DataManager;

            std::unique_ptr<Logger> logger_;


            DataWriter();
            ~DataWriter();


            void init();

            static shared_ptr<DataWriter> getInstance();

            void WriteTick(std::shared_ptr<BaseData> ticker){};

            void WriteKline(std::shared_ptr<BaseData> kline){};

            void WriteAccessList(std::shared_ptr<BaseData> list){};

            void WriteAccountInfo(std::shared_ptr<BaseData> info){};

            void WriteQuote(std::shared_ptr<BaseData> quote);
    
            void WriteDataBase();


            typedef std::shared_ptr<TsLMDB> TSLMDBPtr;
            typedef std::unordered_map<std::string, TSLMDBPtr> TSLMDBMap;
        
        private:

            TSLMDBMap quote_dbs_; 
            TSLMDBMap excahnge_m1_dbs;
            TSLMDBMap exchange_m5_dbs;
            TSLMDBMap excange_d1_dbs;

            static shared_ptr<DataWriter> instance_;

            static std::mutex q_db_mutex;   
            static std::mutex getIns_mutex;

            TSLMDBPtr get_q_db(const char* exg, const char* code);
    };


}

#endif