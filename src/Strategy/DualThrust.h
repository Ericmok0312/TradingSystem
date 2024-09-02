#ifndef SRC_STRATEGY_DUALTHRUST_H
#define SRC_STRATEGY_DUALTHRUST_H

#include "Strategy/Strategy.h"
#include <rapidjson/document.h>


namespace ts{
    class DualThrust:public IStrategy{
    
    private:
        int n;
        float k1;  
        float k2;

        double range;

    public:

        DualThrust(const rapidjson::Document& config);

        ~DualThrust();
        
        void init(ts::StrategyCtx*) override;

        virtual void onSessionBegin(ts::StrategyCtx*) override;

        virtual void onUpdateData(ts::StrategyCtx*) override;

    };
}




#endif