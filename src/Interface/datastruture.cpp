#include <datastructure.h>
#include <string>
#include <vector>
#include <util.h>


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
            throw std::out_of_range("OutofRange in Msg deserialize.");
        }
        destination_ = info[0];
        source_ = info[1];
        data_ = info[3];
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
                data_.market_ = HKSTOCK;
                break;
            case 1:
                data_.market_ = HKOPTIONS;
                break;
            case 2:
                data_.market_ = HKOPTIONS;
                break;
        }
    }
    

    AccountInfoMsg::AccountInfoMsg(string des, string src){
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
         + SERIALIZATION_SEP + to_string(data_.cash_) + SERIALIZATION_SEP +
         to_string(data_.totalAssets_) + SERIALIZATION_SEP + to_string(data_.power_)
         + SERIALIZATION_SEP + to_string(data_.securitiesAssets_) + SERIALIZATION_SEP
         + to_string(data_.fundAssets_) + SERIALIZATION_SEP + to_string(data_.bondAssets_);
    }

    void AccountInfoMsg::deserialize(const string& msgin){

        vector<string> info = split(msgin, SERIALIZATION_SEP);

        if(info.size()<9){
            throw std::out_of_range("OutofRange in SubscribeMsg deserialize.");
        }

        destination_ = info[0];
        source_ = info[1];
        data_.cash_ = stod(info[3]);
        data_.totalAssets_ = stod(info[4]);
        data_.power_ = stod(info[5]);
        data_.securitiesAssets_ = stod(info[6]);
        data_.fundAssets_ = stod(info[7]);
        data_.bondAssets_ = stod(info[8]);

    }


}