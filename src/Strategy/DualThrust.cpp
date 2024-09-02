#include "Strategy/DualThrust.h"
#include "Helper/util.h"

namespace ts{

    DualThrust::DualThrust(const rapidjson::Document& config):IStrategy(config){
        n = config["N"].GetInt();
        k1 = config["K1"].GetDouble();
        k2 = config["K2"].GetDouble();
    }

    DualThrust::~DualThrust(){}

    void DualThrust::init(StrategyCtx* ctx){

        shared_ptr<Msg> msg2futu = make_shared<Msg>();
        msg2futu->destination_ = move("FutuEngine");
        msg2futu->msgtype_ = MSG_TYPE_GET_HISTORY_KLINE;
        msg2futu->source_ = name_;
        rapidjson::Document d;
        d.SetObject();
        d.AddMember("code", rapidjson::Value(ctx->getCode(), strlen(ctx->getCode())+1, d.GetAllocator()), d.GetAllocator());
        d.AddMember("subtype", rapidjson::Value(KLINE_1MIN), d.GetAllocator());
        string start = move(dateNDaysBefore(this->n));
        d.AddMember("start", rapidjson::Value(start.c_str(), start.size(), d.GetAllocator()), d.GetAllocator());
        string end = move(dateNDaysBefore(1));
        d.AddMember("end", rapidjson::Value(end.c_str(), end.size(), d.GetAllocator()), d.GetAllocator());
        Json2String(d, msg2futu->data_);


        shared_ptr<Msg> msg = make_shared<Msg>();
        msg->destination_ = move("DataManager");
        msg->source_ = name_;
        msg->msgtype_ = MSG_TYPE_GET_KLINE_BLOCK_HIST;
        ARG arg(ctx->getExchange(), ctx->getCode(), this->n, GetTimeStamp(), (this->name_+move("_init")).c_str(), KLINE_1MIN, dateNDaysBefore(this->n).c_str(), dateNDaysBefore(0).c_str());
        msg->data_ = move(arg.seriralize());

        unique_ptr<BaseData> data = ctx->StratgeyGetOneTimeData(msg2futu, msg, arg.des.c_str());
        
        KlineSlice* temp = static_cast<KlineSlice*>(data.get());

        double HH = 0;
        double LL = std::numeric_limits<double>::max();
        double HC = 0;
        double LC = std::numeric_limits<double>::max();

        cout<<"Getting required data"<<endl;
        for (int i = 0; i < temp->getCount(); ++i) {
            if(temp->at(i)){
                HH = std::max(HH, temp->at(i)->hPrice_);
                LL = std::min(LL, temp->at(i)->lPrice_);
                HC = std::max(HC, temp->at(i)->cPrice_);
                LC = std::min(LC, temp->at(i)->cPrice_);
            }
            }
        range = max(HH-LC, HC-LL); 
        cout<<range<<endl;

    }

    void DualThrust::onSessionBegin(ts::StrategyCtx* ctx){};


    void DualThrust::onUpdateData(ts::StrategyCtx* ctx){
        std::shared_ptr<Msg> dataMsg = make_shared<Msg>();
        dataMsg->destination_ = "WebApp";
        dataMsg->source_ = "Tester";
        dataMsg->msgtype_ = MSG_TYPE_DEBUG;

        if(ctx->getCur()){
            const ts::Quote* temp = static_cast<const ts::Quote*>(ctx->getCur());
            double buy = temp->oPrice_ + k1 * range;
            double sell = temp->oPrice_ - k2 * range;

            rapidjson::Document d;
            d.SetObject();

            d.AddMember("BuyLine", rapidjson::Value(buy), d.GetAllocator());
            d.AddMember("SellLine", rapidjson::Value(sell), d.GetAllocator());
            d.AddMember("cPrice", rapidjson::Value(temp->cPrice_), d.GetAllocator());
            d.AddMember("updateTimestamp",  rapidjson::Value(temp->updateTimestamp_), d.GetAllocator());
            Json2String(d, dataMsg->data_);

            ctx->SendMessage(dataMsg);
            ctx->LoggingInfo(dataMsg->data_.c_str());

        }
    }




}