#include "Strategy/DualThrust.h"
#include "Helper/util.h"

namespace ts{

    DualThrust::DualThrust(const rapidjson::Document& config):IStrategy(config){
    }

    void DualThrust::init(StrategyCtx* ctx){



        shared_ptr<Msg> msg2futu = make_shared<Msg>();
        msg2futu->destination_ = move("FutuEngine");
        msg2futu->msgtype_ = MSG_TYPE_GET_HISTORY_KLINE;
        msg2futu->source_ = name_;
        rapidjson::Document d;
        d.SetObject();
        d.AddMember("code", rapidjson::Value(code_, code_.size(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("subtype", rapidjson::Value(KLINE_1MIN), d.GetAllocator());
        string start = move(dateNDaysBefore(this->n));
        d.AddMember("start", rapidjson::Value(start, start.size(), d.GetAllocator()), d.GetAllocator());
        string end = move(dateNDaysBefore(1));
        d.AddMember("end", rapidjson::Value(end, end.size(), d.GetAllocator()), d.GetAllocator());
        Json2String(d, msg2futu->data_);


        shared_ptr<Msg> msg = make_shared<Msg>();
        msg->destination_ = move("DataManager");
        msg->source_-> = name_;
        msg->msgtype_ = MSG_TYPE_GET_KLINE_BLOCK_HIST;
        ARG arg(ctx->code_.c_str(), ctx->code_.c_str(), this->n, GetTimeStamp(), (this->name_+move("_init")).c_str(), KLINE_1MIN);
        msg->data_ = move(arg.seriralize());
        unique_ptr<BaseData> data = ctx->StratgeyGetOneTimeData(msg2futu, msg, arg.des.c_str());



    }

}