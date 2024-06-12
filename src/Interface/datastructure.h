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
            double hPrice {0.0}; 
            double oPrice {0.0};
            double lPrice {0.0};
            double cPrice {0.0};
            double lcPrice {0.0};

            int64_t volume {0}; 

            double turnover {0.0};
            double turnoverRate {0.0};
            double pe {0.0};
            double changeRate {0.0};
            double timestamp {0.0};

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
    contractSize : contract size
    openInterest :  total number of open derivative contracts that haven't been settled
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
            double hPrice {0.0}; 
            double oPrice {0.0};
            double lPrice {0.0};
            double cPrice {0.0};
            double lcPrice {0.0};
            double pSpread {0.0};


            int64_t volume {0}; 

            double turnover {0.0};
            double turnoverRate {0.0};
            double amplitude {0.0};
            
            double pe {0.0};
            double changeRate {0.0};
            double timestamp {0.0};

            //special indicators for options

            double sPrice {0.0};
            double contractSize {0.0};
            int32_t openInterest {0};
            double impVolatility {0.0};
            double premium {0.0};
            double delta {0.0};
            double gamma {0.0};
            double vega {0.0};
            double theta {0.0};
            double rho {0.0};


            //special indicators for futures
            double lsprice  {0.0};
            int32_t position {0};
            int32_t pChange {0};
   };
}

#endif