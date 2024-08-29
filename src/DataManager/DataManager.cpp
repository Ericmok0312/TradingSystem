#include <DataManager/DataManager.h>
#include <Helper/ThreadPool.hpp>
#include <Helper/logger.h>
#include <Helper/util.h>
#include <Interface/IMessenger.h>
#include <Interface/datastructure.h>
#include <DataManager/FutuParser.h>
#include <DataManager/DataReader.h>
#include <DataManager/DataWriter.h>
#include <boost/chrono.hpp>
using namespace std;

namespace ts{
    
    std::unique_ptr<ts::Logger> DataManager::logger_ = nullptr;
    std::unique_ptr<ts::IMessenger> DataManager::messenger_ = nullptr;
    std::mutex DataManager::getIns_mutex;
    std::shared_ptr<DataManager> DataManager::instance_ = nullptr;


    /// @brief Constructor, calling ThreadPool constructor
    DataManager::DataManager():ThreadPool(0, 10, 6){
        init();
    }


    /// @brief Default destructor, calling ThreadPool destructor automatically
    DataManager::~DataManager(){
        logger_->info("called datamanager destructor");
        instance_.reset();
    }
    
    void DataManager::init(){
        datawritter_ = DataWriter::getInstance();
        datawritter_->addRegTable(&RegTable_, &RegTableMutex_);
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
        boost::thread temp(boost::bind(&DataManager::running, this));
    }

    void DataManager::running(){
        while(estate_.load() == CONNECTED){
            std::shared_ptr<Msg> msg;
            msg = messenger_->recv(0);
            if(msg && msg->destination_=="DataManager"){
                this->AddTask(std::bind(&DataManager::processMsg, this, placeholders::_1), msg);
            }
        }
    }

    void DataManager::stop(){
        estate_.store(STOP);
    }


    void DataManager::processMsg(std::shared_ptr<Msg> msg){
        //uint64_t init_t = GetTimeStamp();
        vector<shared_ptr<BaseData>> list;
        switch(msg->msgtype_){
            case MSG_TYPE_STORE_QUOTE:
                if(strcmp(msg->source_.c_str(), "FutuEngine")==0){
                    FutuQot2TsQot(msg->data_, list);
                    for (int i=0; i<list.size();++i){
                        datawritter_->AddTask(bind(&DataWriter::WriteQuote, datawritter_, placeholders::_1), list[i]); // add task to DataWriter ThreadPool
                    }
                }
                else if(strcmp(msg->source_.c_str() , "Tester")==0){
                    shared_ptr<BaseData> temp = static_pointer_cast<BaseData>(make_shared<Quote>(msg->data_));
                    datawritter_->AddTask(bind(&DataWriter::WriteQuote, datawritter_, placeholders::_1), temp); // add task to DataWriter ThreadPool
                }
                break;
            
            
            case MSG_TYPE_ACCESSLIST:
            case MSG_TYPE_ACCOUNTINFO:
            case MSG_TYPE_STORE_TICKER:
            case MSG_TYPE_STORE_KLINE_1M:
            break;
            case MSG_TYPE_GET_QUOTE:{

            }   
            break;
            case MSG_TYPE_GET_QUOTE_BLOCK:{
                vector<string> param;
                split(msg->data_.c_str(), ARGV_SEP, param);
                shared_ptr<ts::ARG> arguments = make_shared<ts::ARG>();
                arguments->callback = bind(&DataManager::sendData, this, placeholders::_1, placeholders::_2);
                strcpy(arguments->exg, param[0].c_str());
                strcpy(arguments->code, param[1].c_str());
                arguments->count = static_cast<uint32_t>(stoul(param[2]));
                arguments->etime = static_cast<uint64_t>(stoull(param[3]));
                arguments->des = move(param[4]);
                lock_guard<mutex> lg(RegTableMutex_);
                RegTable_.insert(make_pair(param[0]+move("/")+param[1], make_tuple(bind(&DataManager::AddDataReaderTask, this, placeholders::_1, placeholders::_2), bind(&DataReader::readCurQuoteSlicefromLMDB, datareader_, placeholders::_1), arguments)));
                cout<<param[0]+move("/")+param[1]<<endl;
            }
            break;
        }
        
        // if (IS_BENCHMARK)
        //     logger_->info(fmt::format("DataManager latency final: {}", to_string(GetTimeStamp()-init_t)).c_str());
    }

    void DataManager::AddDataReaderTask(std::function<void(std::shared_ptr<ARG>)> callback, std::shared_ptr<ARG> arg){
        cout<<arg->des<<endl;
        datareader_->AddTask(callback, arg);
    }

    void DataManager::sendData(string&& address, string&& des){
        cout<<"callback called"<<endl;
        cout<<"destinatino: "<<des<<endl;
        shared_ptr<Msg> msg = make_shared<Msg>(move(des), "DataManager", MSG_TYPE_GET_QUOTE_RESPONSE, move(address));
        messenger_->send(msg, 0);
    }


}