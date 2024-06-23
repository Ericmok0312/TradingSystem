#include <FutuEngine.h>
#include <util.h>
#include <json/json.h>
using namespace std;

namespace ts{


    FutuEngine::FutuEngine(){
        init();
    }

    FutuEngine::~FutuEngine(){
        if(futuQotApi_){
            futuQotApi_->UnregisterQotSpi();
            futuQotApi_->UnregisterConnSpi();
            FTAPI::ReleaseQotApi(futuQotApi_);
        }
        if(futuTrdApi_){
            futuTrdApi_->UnregisterTrdSpi();
            futuTrdApi_->UnregisterConnSpi();
            FTAPI::ReleaseQotApi(futuQotApi_);
        }
    }


    /*
    void init()
    - function to initialize futuQotApi_ and futuTrdApi_
    - initialze logger and messenger as well
    
    */
    void FutuEngine::init(){
        futuQotApi_ = FTAPI::CreateQotApi();
        futuQotApi_->RegisterQotSpi(this);
        futuQotApi_->RegisterConnSpi(this);

        futuTrdApi_ = FTAPI::CreateTrdApi();
        futuTrdApi_->RegisterConnSpi(this);
        futuTrdApi_->RegisterTrdSpi(this);

        logger_ = Logger::getInstance();
        messenger_ = std::make_unique<MsgqTSMessenger>(PROXY_SERVER_URL);
    }


    void FutuEngine::start(){
        futuQotApi_->InitConnect("127.0.0.1", 11111, false);
        futuTrdApi_->InitConnect("127.0.0.1", 11111, false);
    }


    void FutuEngine::subscribe(const string& code, SubType subtype){
        Qot_Sub::Request req;
        Qot_Sub::C2S *c2s = req.mutable_c2s();
        auto secList = c2s->mutable_securitylist();
        Qot_Common::Security *sec = secList->Add();

        sec->set_code(code);
        sec->set_market(Qot_Common::QotMarket::QotMarket_HK_Security);
        
        switch(subtype){
            case KLINE_1MIN:
                c2s->add_subtypelist(Qot_Common::SubType::SubType_KL_1Min);
                break;
            case KLINE_1D:
                c2s->add_subtypelist(Qot_Common::SubType::SubType_KL_Day);
                break;                
        }
		c2s->set_isregorunregpush(true);
		c2s->set_issuborunsub(true);

        int32_t serial = futuQotApi_->Sub(req);
        logger_->info(fmt::format("Subscribing: {} for SubType: {} Serial No. {}",code,subtype,serial).c_str());
    }


    void FutuEngine::OnReply_Sub(Futu::u32_t nSerialNo, const Qot_Sub::Response &stRsp){
        if(stRsp.rettype()!= Common::RetType::RetType_Succeed){
            logger_->warn(fmt::format("Subscribe Failed. Serial: {}", nSerialNo).c_str());
        }
        else{
            logger_->info(fmt::format("Subscribe Succeed. Serial: {}", nSerialNo).c_str());
        }
    }

    void FutuEngine::getFund(Market market, ETmode mode){

        Trd_GetFunds::Request req;
		Trd_GetFunds::C2S *c2s = req.mutable_c2s();
		Trd_Common::TrdHeader *header = c2s->mutable_header();
		header->set_accid(33218935);
		header->set_trdenv(mode);
		header->set_trdmarket(market);

        int serial = futuTrdApi_->GetFunds(req);
        logger_->info(fmt::format("Get fund of id: {}  In market: {} For mode: {}", 33218935, market, mode).c_str());

    }


    void FutuEngine::OnReply_GetFunds(Futu::u32_t nSerialNo, const Trd_GetFunds::Response &stRs){

        logger_->info(fmt::format("Get funds serial: {}  returned", nSerialNo).c_str());

        Json::Value res;

        ProtoBufToJson(stRs, res);

        std::shared_ptr<AccountInfoMsg> msg = std::make_shared<AccountInfoMsg>("EngineExecution", "FutuEngine");

        msg->data_.bondAssets_= res["s2c"]["funds"]["bondAssets"].asDouble();
        msg->data_.cash_ = res["s2c"]["funds"]["cash"].asDouble();
        msg->data_.fundAssets_ = res["s2c"]["funds"]["fundAssets"].asDouble();
        msg->data_.power_ = res["s2c"]["funds"]["power"].asDouble();
        msg->data_.securitiesAssets_= res["s2c"]["funds"]["securitiesAssets"].asDouble();
        msg->data_.totalAssets_ = res["s2c"]["funds"]["totalAssets"].asDouble();

        messenger_->send(msg, 0);

    }
    
}