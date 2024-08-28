#ifndef SRC_STRATEGY_STRATEGY_H
#define SRC_STRATEGY_STRATEGY_H

#include "Strategy/TradeUtil.h"
#include <json/json.h>



namespace ts{

    class StrategyCtx;

    class IStrategy{
        protected:
            string name_;
            vector<string> targetCode_;
            string exg_;
            vector<pair<string, Position>> profolio_;
            //vector of list of profolio, in form of <volume, price>
        public:
            IStrategy(rapidjson::Document config){};
            virtual const char* getName() const = 0;
            virtual void onUpdateData(ts::StrategyCtx*) = 0;
            virtual void onSeissionBegin()  = 0;

    };

}





#endif