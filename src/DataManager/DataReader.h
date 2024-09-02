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
            void readCurQuoteSlicefromLMDB(shared_ptr<ARG>);

            void readHistKlineSlicefromLMDB(shared_ptr<ARG>); // read hist data

            
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


            typedef struct KlineList_
            {
                std::string exg_;
                std::string code_;
                uint64_t last_req_time_;

                boost::circular_buffer<Kline> klines_;

                KlineList_():last_req_time_(0){};
            }KlineList;

            typedef unordered_map<std::string, KlineList> KlineCache;

            KlineCache m1_kline_cache_; // caches for 1min kline
            KlineCache m5_kline_cache_; // caches for 5min kline
            KlineCache d1_kline_cache_; // caches for 1day kline


            //getting hist cache for maintaining the lifetime and not to disrupt the frequent reading of data for normal cache
            KlineCache m1_kline_hist_cache_; // caches for 1min kline
            KlineCache m5_kline_hist_cache_; // caches for 5min kline
            KlineCache d1_kline_hist_cache_; // caches for 1day kline

            QuoteCache quote_kline_hist_cache_;

        private:

            TSLMDBMap quote_dbs_; 
            TSLMDBMap kline_m1_dbs_;
            TSLMDBMap kline_m5_dbs_;
            TSLMDBMap kline_d1_dbs_;


            static shared_ptr<DataReader> instance_;
            static std::mutex q_db_mutex;
            static std::mutex getIns_mutex;

            TSLMDBPtr get_q_db(const char* exg, const char* code, TSLMDBMap& source, SubType type);

    };
}             





#endif