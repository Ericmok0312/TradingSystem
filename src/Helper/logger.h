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


#define LOG_FATAL(sqLogger, content) LOG4CPLUS_FATAL(sqLogger->getLogger(), content)
#define LOG_ERROR(sqLogger, content) LOG4CPLUS_ERROR(sqLogger->getLogger(), content)
#define LOG_INFO(sqLogger, content) LOG4CPLUS_INFO(sqLogger->getLogger(), content)
#define LOG_DEBUG(sqLogger, content) LOG4CPLUS_DEBUG(sqLogger->getLogger(), content)



namespace ts
{
    /*
        Logger class

        public:
            Logger: constructor
            ~Logger: destructor
            log, error, warn : corresponding logging function
            getInstance: used for getting the same, firstly instantiated Logger object
            logger_: a static shared pointer to spdlogger created
            logFile_: file name of log file

        NOTE: This Logger class make use of spdlog for safe logging in multithread system. 

        spdlog is used instead of writing my own one for focusing on other more important part.
   
    */
    class Logger{
        public:
            Logger();
            ~Logger();

            static std::shared_ptr<spdlog::logger> spdlogger_;
            
            static std::shared_ptr<Logger> logger_;

            static std::mutex mutex_;

            static std::shared_ptr<Logger> getInstance();

            inline void info(const char* context){
                std::lock_guard<std::mutex> lock(mutex_);
                spdlogger_->info(context);
            }
            inline void warn(const char* context){
                std::lock_guard<std::mutex> lock(mutex_);
                spdlogger_->warn(context);
            }
            inline void error(const char* context){
                std::lock_guard<std::mutex> lock(mutex_);
                spdlogger_->error(context);
            }
            inline void debug(const char* context){
                std::lock_guard<std::mutex> lock(mutex_);
                spdlogger_->debug(context);
            }

    };

    

 


} // namespace ts


#endif