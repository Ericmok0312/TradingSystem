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

    string Msg::serialize(){
        return destination_ + SERIALIZATION_SEP + source_ + SERIALIZATION_SEP + std::to_string(msgtype_) + SERIALIZATION_SEP + Json2String(data_);
    }

    /*
    void deserialize(const string& msgin)
    - Function used to unpack string into Msg
    */
    

    void Msg::deserialize(const string& msgin){
        vector<string> info = split(msgin, SERIALIZATION_SEP);

        if(info.size()<4){
            throw std::out_of_range("OutofRange in message deserialize.");
        }

        destination_ = info[0];
        source_ = info[1];
        msgtype_ = static_cast<MSG_TYPE>(stoi(info[2]));
        data_ = String2Json(info[3]);
    }


   

}