#ifndef SRC_STRATEGY_TRADEUTIL_H
#define SRC_STRATEGY_TRADEUTIL_H

#include "Interface/datastructure.h"
#include "Interface/IMessenger.h"
#include "Strategy/Strategy.h"
#include "atomic"
#include "mutex"

namespace ts{
    //volume, price
    


    /*
    StrategyCtx class, encapsulate loading of data from DataReader
    Each context will get a corresponding strategy and trigger the 
    OnXXXXUpdate function in strategy to update data. 
    Each strategy will maintain a copy of pointer to the required data.

    Planned to support the following functions
    1. keeping track of historic data in form of quoteslice
    2. keeping track of current price or other data
    3. calling the update function of strategy
    4. provide stratgy transection interface (long short etc.)
    5. strategy Engine will keep a list of these context and responsible for
        the lifetime of these ctx
    6. Strategy engine will also keep track of these strategy, each strategy
        can have different ctx
    7. (create strategy -> check context -> add strategy to context)

   // ctx in WonderTrader
    */

    class IStrategy;
    class StrategyCtx{
        private:
            BaseData* data_; 
            int size_;
            string code_;
            string exg_;
            string name_;
            double lprice_;
            int frequency_;
            SubType type_;

            Position position_;

            static std::atomic<int> StrategyCtxcount_;
            shared_ptr<MsgqTSMessenger> messenger_;
            shared_ptr<Logger> logger_;

            std::mutex mutexData_;
            std::mutex strategyMutex_;
            atomic<ts::Estate> estate_;


            unordered_map<string, IStrategy*> StrategyMap_;


            void regRequest();
            void OnDataUpdate();
           

            void init();



        public:

            StrategyCtx(const char* code, const char* exg, int size, SubType type, int freq = 100);
            ~StrategyCtx();
            void start();
            void stop();

            const BaseData* getCur(); //going to depricate
            BaseData* getSlice(); //going to depreciate
            void addStrategy(IStrategy* stg);

            

            //Strategy Interface
            void SendMessage(shared_ptr<Msg> msg);
            void LoggingInfo(const char * info);
            const char* getCode(){return code_.c_str();}
            const char* getExchange(){return exg_.c_str();}
            unique_ptr<BaseData> StratgeyGetOneTimeData(shared_ptr<Msg> msg2futu, shared_ptr<Msg> msg, const char* returnName);

    };
}


#endif