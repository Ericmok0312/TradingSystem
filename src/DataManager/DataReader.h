#ifndef SRC_DATAMANAGER_DATAREADER_H
#define SRC_DATAMANAGER_DATAREADER_H

#include <Helper/ThreadPool.hpp>
#include <DataManager/tslmdb.hpp>
#include <Helper/logger.h>
#include <boost/circular_buffer.hpp>

namespace ts{


    

    class DataReader: public ThreadPool<std::function<void(shared_ptr<ARG>)>, shared_ptr<ARG>>{
        //exg, code, count, etime
        public:
        


            #define BASE_FILE_LOC "./src/DataBase"
            std::shared_ptr<Logger> logger_;

            
            DataReader();
            ~DataReader();

            void init();

            static shared_ptr<DataReader> getInstance();

            void readQuoteSlicefromCSV(shared_ptr<ARG>);
            void readQuoteSlicefromLMDB(shared_ptr<ARG>);

            
            typedef std::shared_ptr<TsLMDB> TSLMDBPtr;
            typedef std::unordered_map<std::string, TSLMDBPtr> TSLMDBMap;


            typedef struct QuoteList_
            {
                std::string exg_;
                std::string code_;
                uint64_t last_req_time_;

                boost::circular_buffer<Quote> quotes_;

                QuoteList_():last_req_time_(0){};
            }QuoteList;

            typedef unordered_map<std::string, QuoteList> QuoteCache;

            QuoteCache quote_cache_; // caches for quote

        private:

            TSLMDBMap quote_dbs_; 
            TSLMDBMap excahnge_m1_dbs;
            TSLMDBMap exchange_m5_dbs;
            TSLMDBMap excange_d1_dbs;


            static shared_ptr<DataReader> instance_;
            static std::mutex q_db_mutex;
            static std::mutex getIns_mutex;

            TSLMDBPtr get_q_db(const char* exg, const char* code);

    };
}             





#endif