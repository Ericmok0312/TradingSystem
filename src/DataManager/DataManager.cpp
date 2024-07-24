#include <DataManager/DataManager.h>
#include <Helper/ThreadPool.hpp>
#include <Helper/logger.h>
#include <Helper/util.h>
#include <Interface/IMessenger.h>
#include <Interface/datastructure.h>
#include <chrono>
#include <DataManager/FutuParser.h>
#include <DataManager/DataReader.h>
#include <DataManager/DataWriter.h>
using namespace std;

namespace ts{
    
    std::unique_ptr<ts::Logger> DataManager::logger_ = nullptr;
    std::unique_ptr<ts::IMessenger> DataManager::messenger_ = nullptr;
    std::mutex DataManager::getIns_mutex;
    std::shared_ptr<DataManager> DataManager::instance_ = nullptr;


    /// @brief Constructor, calling ThreadPool constructor
    DataManager::DataManager():ThreadPool(0, 4, 6){
        init();
    }


    /// @brief Default destructor, calling ThreadPool destructor automatically
    DataManager::~DataManager(){
        logger_->info("called datamanager destructor");
        instance_.reset();
    }
    
    void DataManager::init(){
        datawritter_ = DataWriter::getInstance();
        messenger_ = make_unique<MsgqTSMessenger>(PROXY_SERVER_URL);
        logger_ = make_unique<Logger>("DataManager");
        datareader_ = DataReader::getInstance();
        estate_.store(STOP);
    }


    std::shared_ptr<DataManager> DataManager::getInstance(){
        std::lock_guard<std::mutex> lock(getIns_mutex); 
        if(!instance_){
            instance_ = make_shared<DataManager>();
        }
        return instance_;
    }

    void DataManager::start(){
        estate_.store(CONNECTED);

        while(estate_.load() != STOP){
            std::shared_ptr<Msg> msg;
            msg = messenger_->recv(NNG_FLAG_ALLOC+NNG_FLAG_NONBLOCK);

            if(msg && msg->destination_=="DataManager"){
                this->AddTask(std::bind(&DataManager::processMsg, this, placeholders::_1), msg);
            }
        }
    }


    void DataManager::processMsg(std::shared_ptr<Msg> msg){
        vector<shared_ptr<BaseData>> list;
        switch(msg->msgtype_){
            case MSG_TYPE_QUOTE:{
                if(msg->source_ == "FutuEngine"){
                    FutuQot2TsQot(msg->data_,list);
                    for (int i=0; i<list.size();++i){
                        datawritter_->AddTask(bind(&DataWriter::WriteQuote, datawritter_, placeholders::_1), list[i]); // add task to DataWriter ThreadPool
                    }
                }
                break;
            }
            case MSG_TYPE_ACCESSLIST:
            case MSG_TYPE_ACCOUNTINFO:
            case MSG_TYPE_TICKER:
            case MSG_TYPE_KLINE_1M:
            break;
        }




        std::chrono::microseconds ms = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
        logger_->info(fmt::format("function2 received {}, current UNIX timestamp: {}", msg->serialize(), to_string(ms.count())).c_str());
    }


    void DataManager::storeDataCSV(){
        
    }


}