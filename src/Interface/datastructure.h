#ifndef SRC_INTERFACE_DATASTRUCTURE_H
#define SRC_INTERFACE_DATASTRUCTURE_H

#include <json/json.h>
#include <string>
#include <iostream>
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

        MSG_TYPE_TICKER = 1500,

        //account information
        MSG_TYPE_ACCESSLIST = 1998,
        MSG_TYPE_ACCOUNTINFO = 1999,
        
        //operations on TS
        MSG_TYPE_SUBSCRIBE_MARKET_DATA = 2000,
        MSG_TYPE_GET_ACCOUNTINFO = 2001,
        MSG_TYPE_GET_ACCESSLIST = 2002,
        MSG_TYPE_REGCALLBACK = 2003,

        //debug
        MSG_TYPE_DEBUG = 4000

    };


    enum SubType:int32_t{
        TICKER = 0,
        KLINE_1MIN = 1,
        KLINE_1D = 2,



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

    /*
    Msg
    Class for all message object in the system, identified by msgtype_

    Public: 
        - destination_ : string indicating where the message goes to
        - source_ : string indicating where the message comes from
        - msgtype_ : MSG_TYPE (int32_t) inidcating which type of message it is.
        - data_ : Json::Value type variable, containing data to be transmitted

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
            Json::Value data_;
        
        Msg();

        Msg(const string& des, const string& src, MSG_TYPE type, Json::Value data);

        virtual ~Msg(){};

        virtual char* serialize();

        virtual void deserialize(const string& msgin);
        virtual void deserialize(const char* msgin);
    };


    class AccountInfo{
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

    class DLL_EXPORT_IMPORT Kline{
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

    symbol_ : String representing the stock/option/future, followed by _S , _O and _F to identify
    time_ : when the kline occur
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
    pe : price to earning ratio , what does it means in options and futures are not known
    changeRate : compared with lcPrice, in decimal percentage


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
    class DLL_EXPORT_IMPORT Quote{
        public:
            Quote(){};
            ~Quote(){};


            string symbol_;
            string time_;
            double hPrice_ {0.0}; 
            double oPrice_ {0.0};
            double lPrice_ {0.0};
            double cPrice_ {0.0};
            double lcPrice_ {0.0};
            double pSpread_ {0.0};


            int64_t volume_ {0}; 

            double turnover_ {0.0};
            double turnoverRate_ {0.0};
            double amplitude_ {0.0};
            
            double pe_ {0.0};
            double changeRate_ {0.0};
            double timestamp_ {0.0};

            //special indicators for options

            double sPrice_ {0.0};
            double conSize_ {0.0};
            int32_t opInterest_ {0};
            double impVolatility_ {0.0};
            double premium_ {0.0};
            double delta_ {0.0};
            double gamma_ {0.0};
            double vega_ {0.0};
            double theta_ {0.0};
            double rho_ {0.0};


            //special indicators for futures
            double lsprice_  {0.0};
            int32_t position_ {0};
            int32_t pChange_ {0};
   };
}

#endif