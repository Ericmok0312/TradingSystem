#include <src/Helper/logger.h>
#include <sstream>



namespace ts
{


    std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;


    std::shared_ptr<spdlog::logger> Logger::getInstance(){
        if(logger_==nullptr){
            Logger{};
        }
        return logger_;
    }

    Logger::Logger(){

        logFile_ = "tslog.txt";
        std::stringstream fpath;
        fpath<<LOG_PATH<<logFile_;

        if(access(LOG_PATH, F_OK) != 0)
		{
			mkdir(LOG_PATH, S_IRWXU);  
		}

        std::vector<spdlog::sink_ptr> sinks;
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile_.c_str(), true);
        
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %T][%l]%v");
        
        auto console_sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %T][%l]%v");

        sinks.push_back(console_sink);
        sinks.push_back(file_sink);
        logger_ = std::make_shared<spdlog::logger>("tslogger", begin(sinks), end(sinks));

    }

    Logger::~Logger(){
        spdlog::drop("tslogger");
    }

 
}




;// namespace ts
