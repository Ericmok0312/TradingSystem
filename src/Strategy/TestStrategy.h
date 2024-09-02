#ifndef SRC_STRATEGY_TESTSTRATEGY_H
#define SRC_STRATEGY_TESTSTRATEGY_H

#include "Strategy/Strategy.h"
#include <rapidjson/document.h>

namespace ts{


    class TestStrategy : public IStrategy{
        public:


            TestStrategy(const rapidjson::Document& config);
        
            void init(ts::StrategyCtx*);

            void onSessionBegin(ts::StrategyCtx*) override;

            void onUpdateData(StrategyCtx*) override;
    };

}

#endif