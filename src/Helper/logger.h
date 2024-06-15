#ifndef TRADING_SYSTEM_SRC_HELPER_LOGGER_H
#define TRADING_SYSTEM_SRC_HELPER_LOGGER_H

#include <fstream>
#include <mutex>
#include <memory>
#include <stdio.h>
#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"

#define LOG_PATH "./logfiles"


namespace ts
{
    /*
        Logger class

        public:
            Logger: constructor
            ~Logger: destructor
            log, error, warn : corresponding logging function
            getInstance: used for getting the same, firstly instantiated Logger object
            init: used to initialize Logger
    
   
    */
    class Logger{
        public:
            Logger();
            ~Logger();

            std::string logFile_;
            static std::shared_ptr<spdlog::logger> logger_;
            
            static std::shared_ptr<spdlog::logger> getInstance();

            inline void info(const char* context){
                logger_->info(context);
            }
            inline void warn(const char* context){
                logger_->warn(context);
            }
            inline void debug(const char* context){
                logger_->debug(context);
            }

    };

    

 


} // namespace ts


#endif