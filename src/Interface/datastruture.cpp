#include <Interface/datastructure.h>
#include <string>
#include <vector>
#include <Helper/util.h>


using namespace std;

namespace ts{

    /*
    
    
    For all Msg derived class, implement two functions 
    1. serialize
    2. deserialize
    
    
    
    */

    void Msg::deserialize(const string& msgin){
        vector<string> info = split(msgin, SERIALIZATION_SEP);

        if(info.size()<4){
            throw std::out_of_range("OutofRange in message deserialize.");
        }

        destination_ = info[0];
        source_ = info[1];
        data_ = String2Json(info[3]);
    }


    string SubscribeMsg::serialize(){
        return destination_ + SERIALIZATION_SEP + source_ + SERIALIZATION_SEP + std::to_string(msgtype_)
         + SERIALIZATION_SEP + data_.code_ + SERIALIZATION_SEP + std::to_string(data_.market_);
    }


    void SubscribeMsg::deserialize(const string& msgin){
        vector<string> info = split(msgin, SERIALIZATION_SEP);

        if(info.size()<5){
            throw std::out_of_range("OutofRange in SubscribeMsg deserialize.");
        }

        destination_ = info[0];
        source_ = info[1];
        data_.code_ = info[3];

        switch (stoi(info[4])){
            case 0:
                data_.market_ = TrdMarket_HK;
                break;
            case 1:
                data_.market_ = TrdMarket_HK;
                break;
            case 2:
                data_.market_ = TrdMarket_Futures;
                break;
        }
    }
    

    AccountInfoMsg::AccountInfoMsg(const string& des, const string& src){
        destination_ = des;
        source_ = src;
        msgtype_ = MSG_TYPE_ACCOUNTINFO;
    }

    AccountInfoMsg::AccountInfoMsg(){
        msgtype_ = MSG_TYPE_ACCOUNTINFO;
    }

    AccountInfoMsg::~AccountInfoMsg(){};

    string AccountInfoMsg::serialize(){
        return destination_ + SERIALIZATION_SEP + source_ + SERIALIZATION_SEP + std::to_string(msgtype_)
         + SERIALIZATION_SEP + Json2String(data_);
        }



    EngineOperationMsg::EngineOperationMsg(const string& des, const string& src, MSG_TYPE msgtype,Json::Value data){
        destination_ = des;
        source_ = src;
        msgtype_ = msgtype;
        data_ = data;
    }

    EngineOperationMsg::EngineOperationMsg(){};

    EngineOperationMsg::~EngineOperationMsg(){};

    string EngineOperationMsg::serialize(){
         return destination_ + SERIALIZATION_SEP + source_ + SERIALIZATION_SEP + std::to_string(msgtype_)
         + SERIALIZATION_SEP + Json2String(data_);
    }


}