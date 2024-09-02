#include "Strategy/TestStrategy.h"
#include <rapidjson/document.h>
#include "boost/thread/thread.hpp"
namespace ts{

    TestStrategy::TestStrategy(const rapidjson::Document& config):IStrategy(config){
    }


    void TestStrategy::onSessionBegin(StrategyCtx* ctx){}

    void TestStrategy::onUpdateData(StrategyCtx* ctx){
        //cout<<"stg called"<<endl;

        std::shared_ptr<Msg> dataMsg = make_shared<Msg>();
        dataMsg->destination_ = "WebApp";
        dataMsg->source_ = "Tester";
        dataMsg->msgtype_ = MSG_TYPE_DEBUG;
        if(ctx->getCur()){
            const ts::Quote* temp = static_cast<const ts::Quote*>(ctx->getCur());
            dataMsg->data_ = temp->getJson();
            cout<<temp->getJson()<<endl;

            ctx->SendMessage(dataMsg);
           
            ctx->LoggingInfo(temp->getJson().c_str());
            }
    }

    void TestStrategy::init(ts::StrategyCtx* ctx){};

}
   
