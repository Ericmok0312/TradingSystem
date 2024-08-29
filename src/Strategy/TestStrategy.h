#ifndef SRC_STRATEGY_TESTSTRATEGY_H
#define SRC_STRATEGY_TESTSTRATEGY_H

#include "Strategy/Strategy.h"
#include <rapidjson/document.h>

namespace ts{


    class TestStrategy : public IStrategy{
        public:


            TestStrategy(const rapidjson::Document& config);
        
            void onSessionBegin() override;

            void onUpdateData(StrategyCtx*) override;
    };

}

#endif