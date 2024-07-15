#ifndef SRC_DATAMANAGER_DATAWRITER_H
#define SRC_DATAMANAGER_DATAWRITER_H
#include <Helper/ThreadPool.h>
#include <DataManager/tslmdb.hpp>
#include <Helper/logger.h>
#include <rapidjson/document.h>
#include <Helper/ThreadPool.hpp>
namespace ts{

    #define BASE_FILE_LOC "./src/DataBase"

    class DataWriter: public ThreadPool<void(*)(std::shared_ptr<BaseData>), std::shared_ptr<BaseData>>{
        public:
      
            static std::shared_ptr<Logger> logger_;


            DataWriter();
            ~DataWriter();


            void init();

            static void WriteTick(std::shared_ptr<BaseData> ticker){};

            static void WriteKline(std::shared_ptr<BaseData> kline){};

            static void WriteAccessList(std::shared_ptr<BaseData> list){};

            static void WriteAccountInfo(std::shared_ptr<BaseData> info){};

            static void WriteQuote(std::shared_ptr<BaseData> quote);
    
            typedef std::shared_ptr<TsLMDB> TSLMDBPtr;
            typedef std::unordered_map<std::string, TSLMDBPtr> TSLMDBMap;
        
        private:

            static TSLMDBMap quote_dbs_; 
            static TSLMDBMap excahnge_m1_dbs;
            static TSLMDBMap exchange_m5_dbs;
            static TSLMDBMap excange_d1_dbs;

            static std::mutex q_db_mutex;

            static TSLMDBPtr get_q_db(const char* exg, const char* code);
    };


}

#endif