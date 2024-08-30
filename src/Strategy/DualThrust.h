#ifndef SRC_STRATEGY_DUALTHRUST_H
#define SRC_STRATEGY_DUALTHRUST_H

#include "Strategy/Strategy.h"
#include "Strategy/StrategyManufacturer.h"

class DualThrust : public IStrategy{
    friend class StrategyManufacturer;
    
    private:
        int n;
        float k1;  
        float k2;

        double HH; // maximum of high in past N days
        double HC; // maximum of close price in past N days
        double LC; // minimum of close price in past N days
        double LL; // minimum of low price in past N days

    public:

        DualThrust(const rapidjson::Document& config);

        void init();

        void onSessionBegin(ts::StrategyCtx*) override;

        void onUpdateData(ts::StrategyCtx*) override;

}








#endif