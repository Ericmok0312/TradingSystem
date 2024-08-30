#ifndef SRC_STRATEGY_STRATEGY_H
#define SRC_STRATEGY_STRATEGY_H

#include "Strategy/TradeUtil.h"
#include <rapidjson/document.h>



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

            //vector of list of profolio, in form of <volume, price>
        public:
                
            /*
            config

            {
                "Name" : string,
                "TargetCode" : [string],
                "Exchange" : String,
                "Type" : Int,
                "Position" : 
                    {
                        "{targetcode}" : [volume, price];
                    }
                ,
                "Size" : Int
            }
            
            
            */
           static bool checkValidParam(const rapidjson::Document& config){ //called before constructor called
                if(!(config.HasMember("Name") && config["Name"].IsString())) return false;

                if(!(config.HasMember("TargetCode") && config["TargetCode"].IsArray()))return false;

                for(auto& item:config["TargetCode"].GetArray()){
                    if(!(item.IsString())) return false;
                }

                if(!(config.HasMember("Exchange") && config["Exchange"].IsString()))return false;

                if(!(config.HasMember("Type") && config["Type"].IsInt()))return false;

                if(!(config.HasMember("Size") && config["Size"].IsInt()))return false;

                if(!(config.HasMember("Position") && config["Position"].IsObject()))return false;

                for(rapidjson::Value::ConstMemberIterator itr = config["Position"].MemberBegin(); itr!=config["Position"].MemberEnd(); ++itr){
                    if(!(itr->value[0].IsDouble() && itr->value[1].IsDouble())) return false;
                }

                return true;
            }

            IStrategy(const rapidjson::Document& config){ //checking whether a config is valid is done in getStrategy
                name_ = move(config["Name"].GetString());
                for(rapidjson::SizeType i = 0; i<config["TargetCode"].Size(); ++i){
                    targetCode_.emplace_back(move(config["TargetCode"][i].GetString()));
                }
                exg_ = move(config["Exchange"].GetString());
                type_ = static_cast<SubType>(move(config["Type"].GetInt()));
                for(rapidjson::Value::ConstMemberIterator itr = config["Position"].MemberBegin(); itr!=config["Position"].MemberEnd(); ++itr){
                    Position temp (itr->name.GetString(), exg_.c_str(), itr->value.GetArray()[0].GetDouble(), itr->value.GetArray()[1].GetDouble());
                    profolio_.emplace_back(make_pair(itr->name.GetString(), move(temp)));  
                }
                size_ = move(config["Size"].GetInt());
            };
            const char* getName() {return name_.c_str();};
            virtual void init() = 0;
            virtual void onUpdateData(ts::StrategyCtx*)=0;
            virtual void onSessionBegin(ts::StrategyCtx*)  = 0;
            const char* getExg(){return exg_.c_str();};
            vector<string>& getTargetCode(){return targetCode_;};
            int getSize() {return size_;};
            SubType getType() {return type_;};
            

    };

}





#endif