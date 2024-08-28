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
            SubType type_;
            int size_;

            IStrategy(rapidjson::Document config){ //checking whether a config is valid is done in getStrategy
                name_ = move(config["Name"].GetString());
                for(rapidjson::SizeType i = 0; i<config["TargetCode"].Size(); ++i){
                    targetCode_.emplace_back(move(config["TargetCode"][i].GetString()));
                }
                exg_ = move(config["Exchange"].GetString());
                type_ = static_cast<SubType>(move(config["Type"].GetInt()));
                for(rapidjson::Value::ConstMemberIterator itr = config["Position"].MemberBegin(); itr!=config["Position"][i].MemberEnd(); ++itr){
                    profolio_.emplace_back(make_pair(itr->name.GetString(), itr->value.GetDouble()))  
                }
            };
            //vector of list of profolio, in form of <volume, price>
        public:
            


            virtual const char* getName() {return name_.c_str();};
            virtual void onUpdateData(ts::StrategyCtx*)=0;
            virtual void onSeissionBegin()  = 0;
            virtual const char* getExg(){return exg_.c_str();};
            virtual vector<string>& getTargetCode(){return targetCode_;};
            virtual int getSize() {return size_;};
            virtual SubType getType() {return type_;};

    };

}





#endif