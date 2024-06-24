#ifndef SRC_HELPER_UTIL_H
#define SRC_HELPER_UTIL_H


#include "google/protobuf/stubs/common.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/message.h"
#include "google/protobuf/util/json_util.h"

#include <json/json.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>


using namespace std;
using namespace google;

namespace ts{


    inline vector<string> split(const string& src, char sep){
        vector<string> result;

        stringstream ss (src);
        string temp;

        while(getline(ss, temp, sep)){
            result.push_back(temp);
        }

        string& last = result.back();


        if (last.back() == '\0'){
            result.pop_back();
        }

        return result;
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


    inline void ProtoBufToJson(const protobuf::Message& pbObj, Json::Value& root){
        string res;
        Json::String err;
        ProtoBufToString(pbObj, res);

        Json::CharReaderBuilder reader;
        std::istringstream jsonStream(res);
        Json::parseFromStream(reader, jsonStream, &root, &err);
        
    }


    inline string Json2String(const Json::Value& json){
        Json::StreamWriterBuilder writer;
        std::string s_param = Json::writeString(writer, json);
        return s_param;
    }

    inline Json::Value String2Json(const string& res){
        Json::CharReaderBuilder reader;
        std::istringstream jsonStream(res);
        Json::Value root;
        Json::parseFromStream(reader, jsonStream, &root, nullptr);
        return root;
    }

}




#endif