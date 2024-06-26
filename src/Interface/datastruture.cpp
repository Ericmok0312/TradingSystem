#include <Interface/datastructure.h>
#include <string>
#include <vector>
#include <Helper/util.h>


using namespace std;

namespace ts{


    /*
    
    Default construtor for Msg object, used when converting string into Msg
    
    */
    Msg::Msg(){}; 
    /*
    
    Msg(const string& des, const string& src, MSG_TYPE type, Json::Value data)
    constructor for Msg object, used when all 4 parameters are known
    
    */
    Msg::Msg(const string& des, const string& src, MSG_TYPE type, Json::Value data){
        destination_ = des;
        source_ = src;
        msgtype_ = type;
        data_ = data;
    }

    /*
    string serialize()
    - Function used to serialize Msg object into string for sending in NNG
    - SERIALIZAITON_SEP is used to separate each field
    */

    char* Msg::serialize(){
        string temp;
        Json2String(data_,temp);
        temp = (destination_ + SERIALIZATION_SEP + source_ + SERIALIZATION_SEP + std::to_string(msgtype_) + SERIALIZATION_SEP + temp);
        char* res = new char[temp.size()+1];
        strcpy(res, temp.c_str()); 
        return res;
    }

    /*
    void deserialize(const string& msgin)
    - Function used to unpack string into Msg
    */
    

    void Msg::deserialize(const string& msgin){
        vector<string> info;
        split(msgin.c_str(), SERIALIZATION_SEP, info);

        if(info.size()<4){
            throw std::out_of_range("OutofRange in message deserialize.");
        }

        destination_ = info[0];
        source_ = info[1];
        msgtype_ = static_cast<MSG_TYPE>(stoi(info[2]));
        String2Json(info[3], data_);
    }

    void Msg::deserialize(const char* msgin){
        vector<string> info;
        split(msgin, SERIALIZATION_SEP, info);

        if(info.size()<4){
            throw std::out_of_range("OutofRange in message deserialize.");
        }

        destination_ = info[0];
        source_ = info[1];
        msgtype_ = static_cast<MSG_TYPE>(stoi(info[2]));
        String2Json(info[3], data_);
    }

   

}