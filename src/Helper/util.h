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
#include "chrono"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;
using namespace google;
using namespace boost::posix_time;   
using namespace boost::gregorian;  

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


        // Get current date
        ptime now = second_clock::local_time();
        date today = now.date();

        // Calculate N days before
        date targetDate = today - days(N);

        // Format the date as YYYY-MM-DD
        std::ostringstream oss;
        oss << targetDate.year() << "-" 
        << std::setw(2) << std::setfill('0') << targetDate.month().as_number() << "-" 
        << std::setw(2) << std::setfill('0') << targetDate.day().as_number();
        cout<<oss.str()<<endl;
        return oss.str();
    }

    inline uint64_t Date2TimeStamp(const char* dateStr){
        cout<<dateStr<<endl;
        std::istringstream iss(dateStr);
        std::string year, month, day;

        // Split the input string by '-'
        std::getline(iss, year, '-');
        std::getline(iss, month, '-');
        std::getline(iss, day);

    // Convert to integers and create the date
        
    // Convert to boost::posix_time::ptime
        boost::posix_time::ptime ptime(boost::gregorian::date(std::stoi(year), std::stoi(month), std::stoi(day)));

        auto epochTime = std::chrono::system_clock::from_time_t((ptime - boost::posix_time::from_time_t(0)).total_seconds());

        return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(
            epochTime.time_since_epoch()).count());


    }
}


#endif