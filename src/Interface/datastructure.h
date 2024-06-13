#ifndef SRC_INTERFACE_DATASTRUCTURE_H
#define SRC_INTERFACE_DATASTRUCTURE_H

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
    /*
        Engine state
        For futu, the connection is done on its OpenD software, no need to handle other situations 

        DISCONNECTED = not connected to the futu's OpenD
        CONNECTED = connected to OpenD
        STOP = Engine stop
    */

    enum Estate :int32_t{
        DISCONNECTED = 0,
        CONNECTED ,
        STOP 
    };
    /*
        Engine trading mode
        HISTORY = using history data from data base to simulate trade, used for testing
        SIMULATION = using FUTU's simulation mode for trading on real market
        REAL = trading in the real market
    */
    enum ETmode :int32_t{
        HISTORY = 0,
        SIMULATION,
        REAL
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