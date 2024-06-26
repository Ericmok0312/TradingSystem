#include <DataManager/DataManager.h>
#include <Helper/ThreadPool.h>
#include <Helper/logger.h>
#include <Helper/util.h>
#include <Interface/IMessenger.h>
#include <Interface/datastructure.h>
#include <chrono>

using namespace std;

namespace ts{
    
    std::shared_ptr<ts::Logger> DataManager::logger_ = Logger::getInstance();
    std::unique_ptr<ts::IMessenger> DataManager::messenger_ = make_unique<MsgqTSMessenger>(PROXY_SERVER_URL);

    /// @brief Constructor, calling ThreadPool constructor
    DataManager::DataManager():ThreadPool(1, 4, 6){
        init();
    }


    /// @brief Default destructor, calling ThreadPool destructor automatically
    DataManager::~DataManager(){
    }
    
    void DataManager::init(){
        
        estate_.store(STOP);
    }

    void DataManager::start(){
        estate_.store(CONNECTED);

        while(estate_.load() != STOP){
            std::shared_ptr<Msg> msg;
            msg = messenger_->recv(NNG_FLAG_ALLOC+NNG_FLAG_NONBLOCK);

            if(msg && msg->destination_=="DataManager"){
                ThreadPool::AddTask(&processMsg, msg);
            }
        }
    }


    void DataManager::processMsg(std::shared_ptr<Msg> msg){
        std::chrono::microseconds ms = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
        logger_->info(fmt::format("function2 received {}, current UNIX timestamp: {}", msg->serialize(), to_string(ms.count())).c_str());
    }





}