#include "Strategy/StrategyEngine.h"

namespace ts{
    

    StrategyEngine::StrategyEngine(){
        init();
    }

    StrategyEngine::~StrategyEngine(){
        logger_->info("Destructing StrategyEngine");
        stop();
    }

    void StrategyEngine::stop(){
        for(auto& pair : quoteMap_){
            pair.second.stop();
        }
        estate_.store(Estate::STOP);
    }


    void StrategyEngine::start(){
        estate_.store(Estate::CONNECTED);
        boost::thread(bind(&StrategyEngine::running, this));
    }

    void StrategyEngine::init(){
        estate_.store(Estate::STOP);
        logger_ = Logger::getInstance("StrategyEngine");
        messenger_ = MsgqTSMessenger::getInstance("StrategyEngine");
    }

    void StrategyEngine::running(){
        shared_ptr<Msg> msg;
        while(estate_.load() == CONNECTED){
            msg = messenger_->recv();
            if(msg!=nullptr){
                switch(msg->msgtype_){
                    case MSG_TYPE_SUBSCRIBE_MARKET_DATA:
                    {
                        
                    }
                }
            }
        }
    }


}