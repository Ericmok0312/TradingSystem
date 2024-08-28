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
#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON


using namespace std;

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
            Logger(const char* name);
            ~Logger();

            std::shared_ptr<spdlog::logger> spdlogger_;
            
            string name_;

            static shared_ptr<Logger> getInstance(const char* name);

            inline void info(const char* context){
                this->spdlogger_->info(context);
            }
            inline void warn(const char* context){
                this->spdlogger_->warn(context);
            }
            inline void error(const char* context){
               
                this->spdlogger_->error(context);
            }
            inline void debug(const char* context){

                SPDLOG_DEBUG(spdlogger_, context);
            }
            inline void trace(const char* context){

                SPDLOG_TRACE(spdlogger_, context);
            }
        private:
            static unordered_map<string, shared_ptr<Logger>> regTable_;
            static mutex regTable_lock;
    };

    

 


} // namespace ts


#endif