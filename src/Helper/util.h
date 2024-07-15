#ifndef SRC_HELPER_UTIL_H
#define SRC_HELPER_UTIL_H


#include "google/protobuf/stubs/common.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/message.h"
#include "google/protobuf/util/json_util.h"


#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>


using namespace std;
using namespace google;

namespace ts{


    inline void split(const char* src, char sep, vector<string>& result){


        stringstream ss (string{src});
        string temp;

        while(getline(ss, temp, sep)){
            result.push_back(temp);
        }

        string& last = result.back();


        if (last.back() == '\0'){
            result.pop_back();
        }

        return;
    }


    inline void ProtoBufToString(const protobuf::Message& pbObj, string& strBody)
        {
        protobuf::util::JsonPrintOptions ops;
        ops.add_whitespace = true;
        ops.always_print_enums_as_ints = true;

        protobuf::util::Status status = MessageToJsonString(pbObj, &strBody, ops);
        if (status.error_code() != protobuf::util::error::OK)
        {
            strBody.clear();
        }
    }


    inline void ProtoBufToChar(const protobuf::Message& pbObj, char* res)
        {
        string strBody;
        protobuf::util::JsonPrintOptions ops;
        ops.add_whitespace = true;
        ops.always_print_enums_as_ints = true;

        protobuf::util::Status status = MessageToJsonString(pbObj, &strBody, ops);
        if (status.error_code() != protobuf::util::error::OK)
        {
            strBody.clear();
        }
        strcpy(res, strBody.data());
    }



    inline void Json2String(const rapidjson::Document& json, string& string){
        rapidjson::StringBuffer buff;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
        json.Accept(writer);
        string = buff.GetString();
        return;
    }


    inline void String2Json(const string& res, rapidjson::Document& root){
        root.Parse(res.c_str());
        return;
    }

    inline void ProtoBufToJson(const protobuf::Message& pbObj, rapidjson::Document& root){
        string res;
        ProtoBufToString(pbObj, res);
        root.Parse(res.c_str());
    }


}


#endif