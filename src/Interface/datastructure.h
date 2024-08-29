#ifndef SRC_INTERFACE_DATASTRUCTURE_H
#define SRC_INTERFACE_DATASTRUCTURE_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#if defined(_WIN32) || defined(_WIN64)
#ifdef DLL_EXPORT
#define DLL_EXPORT_IMPORT  __declspec(dllexport)   // export DLL information
#else
#define DLL_EXPORT_IMPORT  __declspec(dllimport)   // import DLL information
#endif
#else
#define DLL_EXPORT_IMPORT
#endif

using namespace std;




namespace ts{


    #define SERIALIZATION_SEP '|'
    #define RELAY_DESTINATION '@'
    #define DESTINATION_ALL '*'
    #define DESTINATION_SEP '.'
    #define ARGV_SEP '^'

    #define MAX_SYMBOL_SIZE 20
    #define MAX_TIME_SIZE 20
    #define MAX_EXG_SIZE 5

    struct ARG{
        char exg[MAX_EXG_SIZE];
        char code[MAX_SYMBOL_SIZE];
        uint32_t  count;
        uint64_t  etime;
        string des; 
        std::function<void(string&&, string&& des)> callback {};
        ARG(){};
    };

    typedef unordered_map<string, tuple<function<void(function<void(shared_ptr<ARG>)>, shared_ptr<ARG>)>, function<void(shared_ptr<ARG>)>, shared_ptr<ARG>>> CallBackTabletype;

    /*
        Engine state
        For futu, the connection is done on its OpenD software, no need to handle other situations 

        DISCONNECTED = not connected to the futu's OpenD
        CONNECTED = connected to OpenD
        STOP = Engine stop
    */


    enum Estate :int32_t{
        DISCONNECTED = 0,
        CONNECTED,
        STOP 
    };
    /*
        Engine trading mode
        HISTORY = using history data from data base to simulate trade, used for testing
        SIMULATION = using FUTU's simulation mode for trading on real market
        REAL = trading in the real market
    */
    enum ETmode :int32_t{

        SIMULATION =0,
        REAL = 1,
        HISTORY = 2
    };
    /*
    Whenther trading is allowed in the API
        LOCKED = not allowed
        UNLOCKED = allowed
    */
    enum ETlock: int32_t{
        LOCKED =0,
        UNLOCKED
    };

    /*
    MSG_TYPE: used to indicate which type of message the Msg object belongs to
    
    */

    enum MSG_TYPE: int32_t
    {
        //futures
        MSG_TYPE_FUTURE_KLINE = 1000,
        MSG_TYPE_FUTURE_QUOTE = 1001,

        //stocks
        MSG_TYPE_STOCK_KLINE = 1002,
        MSG_TYPE_STOCK_QUOTE = 1003,

        //options
        MSG_TYPE_OPTIONS_KLINE = 1004,
        MSG_TYPE_OPTIONS_QUOTE = 1005,

        MSG_TYPE_STORE_TICKER = 1500,
        MSG_TYPE_STORE_KLINE_1M = 1501,
        MSG_TYPE_STORE_QUOTE = 1502,


        
        MSG_TYPE_HIST_KLINE_DAY = 1700,
        

        //account information
        MSG_TYPE_ACCESSLIST = 1998,
        MSG_TYPE_ACCOUNTINFO = 1999,
        
        //operations on TS
        MSG_TYPE_SUBSCRIBE_MARKET_DATA = 2000, // use to initiate the registration of loader
        MSG_TYPE_GET_ACCOUNTINFO = 2001,
        MSG_TYPE_GET_ACCESSLIST = 2002,
        MSG_TYPE_REGCALLBACK = 2003,
        MSG_TYPE_NEW_STRATEGY = 2004, //adding new strategy by dynamic library

        MSG_TYPE_GET_QUOTE = 2500,
        MSG_TYPE_GET_QUOTE_BLOCK = 2501,

        MSG_TYPE_GET_QUOTE_RESPONSE = 3000,

        //debug
        MSG_TYPE_DEBUG = 4000,
        MSG_TYPE_STOP = 4001
    };



    enum class LoaderType{
        QUOTE = 0,
        KLINE = 1,
        TICKER = 2
    };

    enum SubType:int32_t{
        TICKER = 0,
        KLINE_1MIN = 1,
        KLINE_1D = 2,
        QUOTE = 3,

        ALL = 1000
    };


    enum Market:int32_t {
        TrdMarket_Unknown = 0, //Unknown market
        TrdMarket_HK = 1, //HK market (securities, options)
        TrdMarket_US = 2, //US market (securities, options)
        TrdMarket_CN = 3, //A-share market (only used in paper trading)
        TrdMarket_HKCC = 4, //HKCC market (stocks)
        TrdMarket_Futures = 5, //Futures market (global futures)
        TrdMarket_Futures_Simulate_HK = 10, //Hong Kong futures simulated market
        TrdMarket_Futures_Simulate_US = 11, //US futures simulated market
        TrdMarket_Futures_Simulate_SG = 12, //Singapore futures simulated market
        TrdMarket_Futures_Simulate_JP = 13, //Japan futures simulated market
        TrdMarket_HK_Fund = 113, //Hong Kong fund market
        TrdMarket_US_Fund = 123, //US fund market	
    };


    typedef pair<double,double> PositionInformation;

    class Position{
        private:
            PositionInformation pos_;
            string code_;
            string exg_;
        public:
            Position(const char* code, const char* exg, double volume, double price);
            const PositionInformation* getData() const;
            void changePosition(double volume, double price);
    };



    /// @brief abstract class for all data class
    class BaseData{
        public:
            BaseData(){};
            virtual ~BaseData(){};
            virtual string getString() const {return NULL;}
            virtual uint32_t getCount(){return 0;}
            virtual const BaseData* at(int32_t){return nullptr;};
    };




    /*
    Msg
    Class for all message object in the system, identified by msgtype_

    Public: 
        - destination_ : string indicating where the message goes to
        - source_ : string indicating where the message comes from
        - msgtype_ : MSG_TYPE (int32_t) inidcating which type of message it is.
        - data_ : rapidjson::Document type variable, containing data to be transmitted

        Msg() : default constructor

        Msg(const string& des, const string& src, MSG_TYPE type): constructor creatingt the message

        ~Msg() : default destructor

        virtual string serialize() : function used to convert Msg object into string
    */
     

    class Msg{
        public:
            string destination_;
            string source_;
            MSG_TYPE msgtype_;
            string data_;
            uint64_t timestamp_{0};
        
        Msg();

        Msg(const string& des, const string& src, MSG_TYPE type, const string& data, uint64_t timestamp = 0);
        Msg(const string&& des, const string&& src, MSG_TYPE type, const string&& data, uint64_t timestamp = 0);

        virtual ~Msg(){};

        virtual char* serialize();

        virtual void deserialize(const string& msgin);
        virtual void deserialize(const char* msgin);
    };


    class AccountInfo:public BaseData{
        public:
            AccountInfo(){};
            ~AccountInfo(){};

            double cash_ = 0.0;
            double totalAssets_ = 0.0;
            double power_ = 0.0;
            double securitiesAssets_ = 0.0;
            double fundAssets_ = 0.0;
            double bondAssets_ = 0.0;
    };


    /*
    Msgq_protocol: enum class type indiocating the protocol used for the message delivery

    enum class is used to avoid converting to int and compare with other enum/int
    */

   enum class MSGQ_PROTOCOL : uint8_t {
    PAIR = 0, REQ, REP, PUB, SUB, PUSH, PULL
   };


    /*
    Kline - K-line for stock transection. This system uses kline due to authentication limitation of FUTU api

    symbol_ : String representing the stock/option/future, followed by _S , _O and _F to identify
    time_ : when the kline occur
    hPrice : highest price 
    oPrice : open price
    lPrice : low price
    cPrice : close price
    lcPrice : last close price
    volume : transaction volume
    turnover : turnover in number
    turnoverRate : turnover in rate, in decimal percentage
    pe : price to earning ratio , what does it means in options and futures are not known
    changeRate : compared with lcPrice, in decimal percentage

    */

    class DLL_EXPORT_IMPORT Kline:public BaseData{
        public:
            Kline(){};
            ~Kline(){};

            string symbol_;
            string time_;
            double hPrice_ {0.0}; 
            double oPrice_ {0.0};
            double lPrice_ {0.0};
            double cPrice_ {0.0};
            double lcPrice_ {0.0};

            int64_t volume_ {0}; 

            double turnover_ {0.0};
            double turnoverRate_ {0.0};
            double pe_ {0.0};
            double changeRate_ {0.0};
            double timestamp_ {0.0};

    };


    /*
    
    Qoute
    Class for quote, used by stock, options and futures.
    Options and futures have special indicators, which will be set to -1 for stocks

    code_ : code representing the quote
    time_ : when the quote occur
    hPrice : highest price 
    oPrice : open price
    lPrice : low price
    cPrice : close price
    lcPrice : last close price
    sPread : price spread
    volume : transaction volume
    turnover : turnover in number
    turnoverRate : turnover in rate, in decimal percentage
    amplitude: in decimal percentage
   
    


    Special indicators for options
    sPrice : strike price
    conSize : contract size
    opInterest :  total number of open derivative contracts that haven't been settled
    impVolatility : implied volatility


    Special indicators for futures
    lsPrice : last settle price 
    position : holding amount
    pChange : daily position change


    
    */
    class DLL_EXPORT_IMPORT Quote:public BaseData{
        public:
            Quote(){
                std::memset(code_, 0, sizeof(code_));
                std::memset(time_, 0, sizeof(time_));
                std::memset(exg_, 0, sizeof(exg_));
                hPrice_ = 0.0;
                oPrice_ = 0.0;
                lPrice_ = 0.0;
                cPrice_ = 0.0;
                lcPrice_ = 0.0;
                pSpread_ = 0.0;
                volume_ = 0;
                turnover_ = 0.0;
                turnoverRate_ = 0.0;
                amplitude_ = 0.0;
                timestamp_ = 0.0;
                sPrice_ = 0.0;
                conSize_ = 0.0;
                opInterest_ = 0;
                impVolatility_ = 0.0;
                premium_ = 0.0;
                delta_ = 0.0;
                gamma_ = 0.0;
                vega_ = 0.0;
                theta_ = 0.0;
                rho_ = 0.0;
                lsprice_ = 0.0;
                position_ = 0;
                pChange_ = 0;
                updateTimestamp_ = 0;
            };
            ~Quote(){};
            Quote(const string& input){
                    vector<string> values;
                    stringstream ss(input);
                    string token;
                    while (getline(ss, token, ',')) {
                        values.push_back(token);
                    }

                    // Assign the parsed values to the respective variables
                    strcpy(code_,values[0].c_str());
                    strcpy(time_,values[1].c_str());
                    strcpy(exg_,values[2].c_str());
                    hPrice_ = stod(values[3]);
                    oPrice_ = stod(values[4]);
                    lPrice_ = stod(values[5]);
                    cPrice_ = stod(values[6]);
                    lcPrice_ = stod(values[7]);
                    pSpread_ = stod(values[8]);
                    volume_ = stod(values[9]);
                    turnover_ = stod(values[10]);
                    turnoverRate_ = stod(values[11]);
                    amplitude_ = stod(values[12]);
                    timestamp_ = stod(values[13]);
                    sPrice_ = stod(values[14]);
                    conSize_ = stod(values[15]);
                    opInterest_ = stod(values[16]);
                    impVolatility_ = stod(values[17]);
                    premium_ = stod(values[18]);
                    delta_ = stod(values[19]);
                    gamma_ = stod(values[20]);
                    vega_ = stod(values[21]);
                    rho_ = stod(values[22]);
                    lsprice_ = stod(values[23]);
                    position_ = stod(values[24]);
                    pChange_ = stod(values[25]);
                    updateTimestamp_ = stod(values[26]);
                }
            string getString() const{
                stringstream ss;
                ss<<code_<<','<<time_<<','<<exg_<<','<<hPrice_<<','<<oPrice_<<','
                <<lPrice_<<','<<cPrice_<<','<<lcPrice_<<','<<pSpread_<<','
                <<volume_<<','<<turnover_<<','<<turnoverRate_<<','<<amplitude_<<','
                <<timestamp_<<','<<sPrice_<<','<<conSize_<<','<<opInterest_<<','
                <<impVolatility_<<','<<premium_<<','<<delta_<<','<<gamma_<<','<<
                vega_<<','<<rho_<<','<<lsprice_<<','<<position_<<','<<pChange_<<','<<updateTimestamp_;
                return move(ss.str());
            }

            string getJson() const{
                rapidjson::Document d;
                d.SetObject();

                rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
                d.AddMember("code", rapidjson::StringRef(code_), allocator);
                d.AddMember("time", rapidjson::StringRef(time_), allocator);
                d.AddMember("exg", rapidjson::StringRef(exg_), allocator);
                d.AddMember("hPrice", hPrice_, allocator);
                d.AddMember("oPrice", oPrice_, allocator);
                d.AddMember("lPrice", lPrice_, allocator);
                d.AddMember("cPrice", cPrice_, allocator);
                d.AddMember("lcPrice", lcPrice_, allocator);
                d.AddMember("pSpread", pSpread_, allocator);
                d.AddMember("volume", volume_, allocator);
                d.AddMember("turnover", turnover_, allocator);
                d.AddMember("turnoverRate", turnoverRate_, allocator);
                d.AddMember("amplitude", amplitude_, allocator);
                d.AddMember("timestamp", static_cast<uint64_t>(timestamp_), allocator);
                d.AddMember("sPrice", sPrice_, allocator);
                d.AddMember("conSize", conSize_, allocator);
                d.AddMember("opInterest", opInterest_, allocator);
                d.AddMember("impVolatility", impVolatility_, allocator);
                d.AddMember("premium", premium_, allocator);
                d.AddMember("delta", delta_, allocator);
                d.AddMember("gamma", gamma_, allocator);
                d.AddMember("vega", vega_, allocator);
                d.AddMember("theta", theta_, allocator);
                d.AddMember("rho", rho_, allocator);
                d.AddMember("lsprice", lsprice_, allocator);
                d.AddMember("position", position_, allocator);
                d.AddMember("pChange", pChange_, allocator);
                d.AddMember("updateTimestamp", static_cast<uint64_t>(updateTimestamp_), allocator);

                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                d.Accept(writer);

                return move(buffer.GetString());

            }



            char code_[MAX_SYMBOL_SIZE];
            char time_[MAX_TIME_SIZE];
            char exg_[MAX_EXG_SIZE];
            double hPrice_ ; 
            double oPrice_ ;
            double lPrice_ ;
            double cPrice_;
            double lcPrice_;
            double pSpread_;



            int64_t volume_; 

            double turnover_;
            double turnoverRate_;
            double amplitude_;
            
            uint64_t timestamp_;

            //special indicators for options

            double sPrice_;
            double conSize_;
            int64_t opInterest_;
            double impVolatility_;
            double premium_;
            double delta_;
            double gamma_;
            double vega_;
            double theta_;
            double rho_;


            //special indicators for futures
            double lsprice_ ;
            int64_t position_ ;
            int64_t pChange_ ;


            uint64_t updateTimestamp_;
   };


    class QuoteSlice : public BaseData{
        private:
            char code_[MAX_SYMBOL_SIZE];
            typedef std::pair<Quote*, uint32_t> QuoteBlock;
            std::vector<QuoteBlock> block_;
            uint32_t count_;

        protected:
           

            inline int32_t translateIdx(int32_t idx) const{
                if (idx<0){
                    return max(0, (int32_t)count_+idx);
                }
                return idx;
            }

        public:
            QuoteSlice(){this->block_.clear();}

            static inline QuoteSlice* create (const char* code, Quote* quote = nullptr, uint32_t count = 0){
                QuoteSlice* slice = new QuoteSlice();
                strcpy(slice->code_, code);
                if(quote != nullptr){
                    slice->block_.emplace_back(QuoteBlock(quote, count));
                    slice->count_ = count;
                }
                return slice;
            }


            inline bool appendBlock(Quote* quote, uint32_t count)
            {
                if (quote == nullptr || count == 0)
                    return false;

                this->count_ += count;
                this->block_.emplace_back(QuoteBlock(quote, count));
                return true;
            }

            inline vector<QuoteBlock>* getBlock(){
                return &this->block_;
            }
            
            inline uint32_t getCount(){
                return this->count_;
            }

            inline const Quote* at(int32_t idx){
                if(count_==0){
                    return nullptr;
                }

                idx = translateIdx(idx);
                do{
                    for(auto& item: block_){
                        if ((uint32_t)idx >= item.second)
                            idx -= item.second;
                        else
                            return item.first+idx; 
                    }
                }while (false);
                return nullptr;
            }
    };

}

#endif