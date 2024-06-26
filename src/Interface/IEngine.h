#include <cstdint>
#include <atomic>
#include <Interface/datastructure.h>
#include <Helper/logger.h>
#include <Interface/IMessenger.h>

#ifndef TRADINGSYSTEM_SRC_INTERFACE_IENGINE_H
#define TRADINGSYSTEM_SRC_INTERFACE_IENGINE_H

#if defined(_WIN32) || defined(_WIN64)
#ifdef DLL_EXPORT
#define DLL_EXPORT_IMPORT  __declspec(dllexport)   // export DLL information
#else
#define DLL_EXPORT_IMPORT  __declspec(dllimport)   // import DLL information
#endif
#else
#define DLL_EXPORT_IMPORT
#endif



namespace ts
{
    



    /*
    Base engine for apis' from brokerages, a pure virtual class

    public:
        constructor and destructor

        void init(): function to initialized the engine
        void start(): start the works after engine has initialized
        void stop(): stop the engine
        void setTradeMode(): set the trading mode
        void lockTXN(): lock real transection
        void unlockTXN(): unlock transection
        bool connect(): not sure if needed
        
    protected:
        std::atomic<Estate> estate_: engine state
        std::atomic<ETmode> etrademode_: engine trade mode
        std::atomic<ETlock> etradelock_: engine lock status

        std::atomic make the variable to enable safe access in multi-threading software
        variables are read using .load(), write using .store()

        atomic helps eliminate the need of mutual exclusion
    */

    class IEngine{

        public:

            IEngine();
            virtual ~IEngine();

            virtual void init() = 0;
            virtual void start() = 0;
            virtual void stop()= 0; 
            virtual void setTradeMode()= 0;
            virtual void lockTXN()= 0;
            virtual void unlockTXN()= 0;
            virtual void subscribe(const char* code, int32_t subtype) = 0;
            //virtual bool connect() = 0;
        
        protected: 

            std::shared_ptr<ts::Logger> logger_;
            std::atomic<ts::Estate> estate_;
            std::atomic<ts::ETmode> etrademode_;
            std::atomic<ts::ETlock> etradelock_;
            std::unique_ptr<ts::IMessenger> messenger_;
    };

} // namespace ts

#endif
