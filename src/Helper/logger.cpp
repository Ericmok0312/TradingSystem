#include <Helper/logger.h>
#include <sstream>
#include <chrono>
#include <iomanip>


namespace ts
{
    /*
    
    Logger::logger_ : initialized into  nullptr, for checking whether the spdlogger is created in getInstance.
    
    */

    std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

    /*
    
    mutex_ : a mutex for getInstance(), avoiding any threading problem
    
    */

    std::mutex Logger::mutex_;
    /*
    Logger::getInstance() : static function for getting logger_ in other parts of the system

        If logger_ is nullptr, call the Logger constructor
        returns logger_

        mutex_ is used to avoid threading problem
    */
   

    std::shared_ptr<spdlog::logger> Logger::getInstance(){
        std::lock_guard<std::mutex> lock(mutex_);
        if(logger_==nullptr){
            Logger{};
        }
        return logger_;
    }


    /*
    
    Logger()

        -Constructor for Logger, called only once in whole system.

        -using chrono::system_clock::to_time_t and chrono::system_clock::now() to get currect time
        -using put_time to format current time and added to predefined log path and prefix for log files
        -checking if ./logfiles exists, create one if not
        -using sinks in spdlog to create a multi-task logger and then set logger_ to corresponding pointer 
    
    */

    Logger::Logger(){

        std::time_t temp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::ostringstream fpath;
        fpath << "./logfiles/log";
        fpath << std::put_time(std::localtime(&temp), "_%Y_%m_%d") << ".txt";
        
        if(access("./logfiles", F_OK) != 0) {
            mkdir("./logfiles", S_IRWXU);
        }
        std::vector<spdlog::sink_ptr> sinks;
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fpath.str(), false);
        
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %T][%l]%v");
        
        auto console_sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %T][%l]%v");

        sinks.push_back(console_sink);
        sinks.push_back(file_sink);
        logger_ = std::make_shared<spdlog::logger>("tslogger", begin(sinks), end(sinks));

    }


    /*
    ~Logger()
        - destructor, called automatically when exe is terminated
        - drop the logger from spdlog for proper destruction
    */

    Logger::~Logger(){
        spdlog::drop("tslogger");
    }

 
}




;// namespace ts
