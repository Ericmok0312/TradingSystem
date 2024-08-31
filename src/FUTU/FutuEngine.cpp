#include <FUTU/FutuEngine.h>
#include <Helper/util.h>
#include "boost/thread/thread.hpp"
using namespace std;

namespace ts{



    std::mutex FutuEngine::getIns_mutex;
    std::shared_ptr<FutuEngine> FutuEngine::instance_ = nullptr;

    /// @brief Default Constructor, calling init()
    FutuEngine::FutuEngine(){
        init();
    }

    /// @brief Destructor, e ster  and release futuQotApi_ and futuTrdApi_ as requried
    FutuEngine::~FutuEngine(){
        std::lock_guard<mutex> lk(getIns_mutex);
        logger_->info("Destructing FutuEngine");
        //instance_.reset();
        if(futuQotApi_ != nullptr){
            futuQotApi_->UnregisterQotSpi();
            futuQotApi_->UnregisterConnSpi();
            FTAPI::ReleaseQotApi(futuQotApi_);
            futuQotApi_ = nullptr; // prevent double deletion
        }
        if(futuTrdApi_ != nullptr){
            futuTrdApi_->UnregisterTrdSpi();
            futuTrdApi_->UnregisterConnSpi();
            FTAPI::ReleaseTrdApi(futuTrdApi_);
            futuTrdApi_ = nullptr;
        }
        FTAPI::UnInit();
        sleep(2);
    }




    std::shared_ptr<FutuEngine> FutuEngine::getInstance(){
        std::lock_guard<std::mutex> lock(getIns_mutex); 
        if(!instance_){
            instance_ = make_shared<FutuEngine>();
        }
        return instance_;
    }


    /// @brief used to initialize FutuEngine (futuQotApi_ and futuTrdApi_), called in constructor
    void FutuEngine::init(){
        futuQotApi_ = FTAPI::CreateQotApi();
        futuQotApi_->RegisterQotSpi(this);
        futuQotApi_->RegisterConnSpi(this);

        futuTrdApi_ = FTAPI::CreateTrdApi();
        futuTrdApi_->RegisterConnSpi(this);
        futuTrdApi_->RegisterTrdSpi(this);

        logger_ = Logger::getInstance("FutuEngine");
        messenger_ = std::make_unique<MsgqTSMessenger>(PROXY_SERVER_URL);
        estate_.store(STOP);

        FTAPI::Init();
    }

    /*
     void start()

     - initialize the connection to the port
     - repeat receive message, check if message destionation is FutuEngine
     - call appropriate function accordingly
    
    */
   

    void FutuEngine::start(){
        estate_.store(CONNECTED);
        futuQotApi_->InitConnect("127.0.0.1", 11111, false);
        futuTrdApi_->InitConnect("127.0.0.1", 11111, false);
        logger_->info("Futu engine start");
        boost::thread thread(bind(&FutuEngine::running, this));
    }

    void FutuEngine::running(){
        std::shared_ptr<Msg> msg;
        while(estate_.load() == CONNECTED){
            msg = messenger_->recv(0); // nonblock + ALLOC
            if(!msg || msg->destination_!="FutuEngine"){
                continue;
            }
            else{
                rapidjson::Document root;
                String2Json(msg->data_, root);
                switch(msg->msgtype_){
                    case MSG_TYPE_GET_ACCOUNTINFO:
                        this->getFund(root["id"].GetInt(),root["market"].GetInt(), root["mode"].GetInt());
                        break;
                    case MSG_TYPE_SUBSCRIBE_MARKET_DATA:
                        this->subscribe(root["code"].GetString(), root["subtype"].GetInt());
                        break;
                    case MSG_TYPE_GET_ACCESSLIST:
                        this->getAccessList();
                        break;
                    case MSG_TYPE_REGCALLBACK:
                        this->regCallBack(root["code"].GetString(),  root["subtype"].GetInt());
                        break;
                    case MSG_TYPE_GET_HISTORY_KLINE:
                        this->getHistoryKline(root["code"].GetString(), root["subtype"].GetInt(), root["start"].GetString(), root["end"].GetString());
                        break;
                    case MSG_TYPE_DEBUG:
                        break;
                    case MSG_TYPE_STOP:
                        this->stop();
                        break;
                    default:
                        logger_->info(msg->serialize());
                }
            }
        }
    }

    void FutuEngine::stop(){
        estate_.store(STOP);
    }


    void FutuEngine::subscribe(const char* code, int32_t subtype){
        Qot_Sub::Request req;
        Qot_Sub::C2S *c2s = req.mutable_c2s();
        auto secList = c2s->mutable_securitylist();
        Qot_Common::Security *sec = secList->Add();

        sec->set_code(code);
        sec->set_market(Qot_Common::QotMarket::QotMarket_HK_Security);

    
        vector<Qot_Common::SubType> enSubTypes = { Qot_Common::SubType_Basic, Qot_Common::SubType_OrderBook,
                Qot_Common::SubType_Broker,  Qot_Common::SubType_KL_Day, Qot_Common::SubType_RT, Qot_Common::SubType_Ticker};

        switch(static_cast<SubType>(subtype)){
            case TICKER:
                c2s->add_subtypelist(Qot_Common::SubType::SubType_Ticker);
                break;
            case KLINE_1MIN:
                c2s->add_subtypelist(Qot_Common::SubType::SubType_KL_1Min);
                break;
            case KLINE_1D:
                c2s->add_subtypelist(Qot_Common::SubType::SubType_KL_Day);
                break;
            case QUOTE:
                c2s->add_subtypelist(Qot_Common::SubType::SubType_Basic);    
                break;     
            case ALL:
                for(int i=0; i<enSubTypes.size(); i++)
                c2s->add_subtypelist(enSubTypes[i]);
                break;
        }
		c2s->set_isregorunregpush(true);
		c2s->set_issuborunsub(true);

        uint32_t serial = futuQotApi_->Sub(req);
        logger_->info(fmt::format("Subscribing: {} for SubType: {} Serial No. {}",code,to_string(subtype),to_string(serial)).c_str());
    }


    void FutuEngine::OnReply_Sub(Futu::u32_t nSerialNo, const Qot_Sub::Response &stRsp){
        if(stRsp.rettype()!= Common::RetType::RetType_Succeed){
            logger_->warn(fmt::format("Subscribe Failed. Serial: {}", nSerialNo).c_str());
        }
        else{
            logger_->info(fmt::format("Subscribe Succeed. Serial: {}", nSerialNo).c_str());
        }
    }


 
    /// @brief Register callbacks for corresponding subtype, calling subscribe to do the work
    /// @param code 
    /// @param subtype 
    void FutuEngine::regCallBack(const char* code, int32_t subtype){
        logger_->info(fmt::format("regCallBack called with code: {}, subtype: {}",code,subtype).c_str());
        subscribe(code, subtype);
    }


    void FutuEngine::OnPush_UpdateTicker(const Qot_UpdateTicker::Response &stRsp){
        std::shared_ptr<Msg> msg = std::make_shared<Msg>("DataManager", "FutuEngine", MSG_TYPE_STORE_TICKER, "");
        ProtoBufToString(stRsp, msg->data_);
        messenger_->send(msg, 0);
    }


    void FutuEngine::OnPush_UpdateBasicQot(const Qot_UpdateBasicQot::Response &stRsp){
        uint64_t init = GetTimeStamp();
        std::shared_ptr<Msg> msg = std::make_shared<Msg>("DataManager", "FutuEngine", MSG_TYPE_STORE_QUOTE, "");
        ProtoBufToString(stRsp, msg->data_);
        msg->timestamp_ = init;
        messenger_->send(msg, 0);
    }

    /// @brief  Function for getting fund in Futu account, with given id, market and mode (all need to be retrieved using getAccessList)
    /// @param id 
    /// @param market 
    /// @param mode 
    void FutuEngine::getFund(int id, int32_t market, int32_t mode){
        
        Trd_GetFunds::Request req;
        Trd_GetFunds:: C2S * c2s = req.mutable_c2s();
        Trd_Common::TrdHeader *header = c2s->mutable_header();
		header->set_accid(id);
		header->set_trdenv(mode);
		header->set_trdmarket(market);

        uint32_t serial = futuTrdApi_->GetFunds(req);
        logger_->info(fmt::format("getFund called, with id: {}, market: {}, mode: {}. Return serial: {}",id, market, mode, serial).c_str());

    }


    void FutuEngine::OnReply_GetFunds(Futu::u32_t nSerialNo, const Trd_GetFunds::Response &stRs){
        logger_->info(fmt::format("OnReply_GetFunds, serial: {}", nSerialNo).c_str());
        std::shared_ptr<Msg> msg = std::make_shared<Msg>("DataManager", "FutuEngine", MSG_TYPE_ACCOUNTINFO, "");
        ProtoBufToString(stRs, msg->data_);
        messenger_->send(msg, 0);
    }
    
    void FutuEngine::getAccessList(){
        Trd_GetAccList::Request req;
        Trd_GetAccList::C2S* c2s = req.mutable_c2s();
        c2s->set_userid(0);
        c2s->set_needgeneralsecaccount(true);
        uint32_t serial = futuTrdApi_->GetAccList(req);
        logger_->info(fmt::format("getAccessList called. Returned serial: {}", serial).c_str());

    }

    void FutuEngine::OnReply_GetAccList(Futu::u32_t nSerialNo, const Trd_GetAccList::Response &stRsp){

        logger_->info(fmt::format("Get access serial: {}  returned", nSerialNo).c_str());
        std::shared_ptr<Msg> msg  = std::make_shared<Msg>("DataManager", "FutuEngine",  MSG_TYPE_ACCESSLIST,"");
        ProtoBufToString(stRsp, msg->data_);
        messenger_->send(msg);
    }


    void FutuEngine::getHistoryKline(const char* code, int32_t subtype, const char* start, const char* end){
        Qot_RequestHistoryKL::Request req;
        Qot_RequestHistoryKL::C2S* c2s = req.mutable_c2s();
        c2s->set_rehabtype(1);
        switch (static_cast<SubType>(subtype)){
            case KLINE_1D:
                c2s->set_kltype(Qot_Common::KLType::KLType_Day);
                break;
            case KLINE_1MIN:
                c2s->set_kltype(Qot_Common::KLType::KLType_1Min);
                break;
            default:
                c2s->set_kltype(Qot_Common::KLType::KLType_1Min);
                break;
        }

        Qot_Common::Security *sec = c2s->mutable_security();
        sec->set_code(code);
        sec->set_market(Qot_Common::QotMarket::QotMarket_HK_Security);
        c2s->set_begintime(start);
		c2s->set_endtime(end);
        uint32_t m_RequestHistoryKLSerialNo = futuQotApi_->RequestHistoryKL(req);
        klineSerialMap_[m_RequestHistoryKLSerialNo] = static_cast<SubType>(subtype);
        logger_->info(fmt::format("getHistoryKline called, code : {}, Start Date : {}, End Date : {}, Serial Number : {}.", code, start, end, m_RequestHistoryKLSerialNo).c_str());
    }

    void FutuEngine::OnReply_RequestHistoryKL(Futu::u32_t nSerialNo, const Qot_RequestHistoryKL::Response &stRsp){
        uint64_t init = GetTimeStamp();
        std::shared_ptr<Msg> msg;
        switch(klineSerialMap_.find(nSerialNo)->second){
            case KLINE_1D:
                msg = std::make_shared<Msg>("DataManager", "FutuEngine", MSG_TYPE_STORE_KLINE_1D, "");
                break;
            case KLINE_1MIN:
                msg = std::make_shared<Msg>("DataManager", "FutuEngine", MSG_TYPE_STORE_KLINE_1Min, "");
        }
         
        ProtoBufToString(stRsp, msg->data_);
        messenger_->send(msg, 0);
    }


}
