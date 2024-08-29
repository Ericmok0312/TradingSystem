#ifndef SRC_STRATEGY_STRATEGYENGINE_H
#define SRC_STRATEGY_STRATEGYENGINE_H


#include "Helper/ThreadPool.hpp"
#include "Interface/IEngine.h"
#include "Strategy/TradeUtil.h"
#include "json/json.h"
#include "functional"
#include "mutex"
namespace ts{

    typedef rapidjson::Document Parameter;
    //typedef function<void(Parameter)>


    /*
    
    Engine will manage Loaders of different targetted stocks/futures,
    whenever loaders get new data, a event will be triggered, and the
    callback function of strategies will be called.

    Loader will also be responsible for managing the profolio of the particular
    stock / futures


    In the callback function, loaders will be passed in, and strategies will be executed
    (initiated by loader)

    Loaders will share a copy of profolio data with profolio manager

    Changes in other part:
        DataManager should support event emission of ticker/quote update to replace the current
        scheduled ticker update by pub/sub

        maybe pull/push needed?


    When a new strategy is added to the engine, strategy engine will do the following
        1. initialize a new strategy object and control the lifetime of these objects
        2. get the information of which kind of data are needed in the strategy
        3. search in the current loader map to see if certain loader exists
            3.1 if yes, then add the function of onDataUpdate in the corresponding strategy to the event pool in loaders
            3.2 if no, create corresponding loader, sending reg callback to FutuEngine
    
    */


    class StrategyEngine: public IEngine{
        public:


            typedef unordered_map<string, StrategyCtx*> QuoteLoaderMap;// "exg/code" as key
            typedef unordered_map<string, IStrategy*> StrategyMap; // using pointer to accept polymorphism
            //typedef unordered_map<stirng, Loader<KlineSlice>> KlineLoaderMap;
            //typedef unordered_map<string, Loader<TickerSlice> TickerLoaderMap;

            StrategyEngine();
            virtual ~StrategyEngine();
            
            void start() override;
            void stop() override;
            void addStrategy(IStrategy* stg);
            static shared_ptr<StrategyEngine> getInstance();

        private:
            static shared_ptr<StrategyEngine> instance_;
            static mutex getInstanceMutex_;
            QuoteLoaderMap quoteMap_;
            StrategyMap strategyMap_;
            //KlineLoaderMap klineMap_;
            //TickerLoaderMap tickermap_
            

            void init() override;
            void running() override;


    };




}







#endif