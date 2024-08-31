#ifndef SRC_HELPER_UTIL_H
#define SRC_HELPER_UTIL_H


#include "google/protobuf/stubs/common.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/message.h"
#include "google/protobuf/util/json_util.h"


#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <boost/chrono.hpp>


using namespace std;
using namespace google;

namespace ts{
    
    #define IS_BENCHMARK 0

    inline void split(const char* src, char sep, vector<string>& result){


        stringstream ss (string{src});
        string temp;

        while(getline(ss, temp, sep)){
            result.emplace_back(move(temp));
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

    inline uint64_t GetTimeStamp(){
        return static_cast<uint64_t>(boost::chrono::duration_cast<boost::chrono::microseconds>(boost::chrono::system_clock::now().time_since_epoch()).count());
    }



    inline std::string dateNDaysBefore(int N) {
    
        auto now = std::chrono::system_clock::now();
        
        // Calculate N days before
        auto daysBefore = std::chrono::duration_cast<std::chrono::days>(std::chrono::hours(24 * N));
        auto targetDate = now - daysBefore;

        // Convert to time_t for formatting
        std::time_t targetTime = std::chrono::system_clock::to_time_t(targetDate);
        
        // Convert to tm structure
        std::tm* tmPtr = std::localtime(&targetTime);
        
        // Format the date as YYYY-MM-DD
        std::ostringstream oss;
        oss << std::put_time(tmPtr, "%Y-%m-%d");
        
        return move(oss.str());
    }

    inline uint64_t Date2TimeStamp(const char* date){
        std::tm tm = {};
        std::istringstream ss(date);
        
        // Parse the date
        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (ss.fail()) {
            throw std::invalid_argument("Invalid date format. Use YYYY-MM-DD.");
        }
        
        // Convert to time_t
        std::time_t time = std::mktime(&tm);
        
        // Check if conversion was successful
        if (time == -1) {
            throw std::runtime_error("Failed to convert date to time_t.");
        }
        
        // Convert to microseconds since epoch
        auto timestamp = std::chrono::time_point<std::chrono::system_clock>(
            std::chrono::seconds(time)
        ).time_since_epoch();
        
        // Return timestamp in microseconds
        return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(timestamp));
    }

}


#endif