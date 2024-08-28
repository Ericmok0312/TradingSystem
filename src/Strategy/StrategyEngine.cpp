#include "Strategy/StrategyEngine.h"

namespace ts{
    

    StrategyEngine::StrategyEngine(){
        init();
    }

    StrategyEngine::~StrategyEngine(){
        logger_->info("Destructing StrategyEngine");
        stop();
        for(auto it = quoteMap_.begin(); it!=quoteMap_.end(); ++it){
            delete it->second;
        }

        for(auto it=strategyMap_.begin(); it!=strategyMap_.end();++it){
            delete it->second;
        }
    }

    void StrategyEngine::stop(){
        for(auto& pair : quoteMap_){
            pair.second->stop();
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
                    case MSG_TYPE_NEW_STRATEGY:
                    {
                        
                    }
                }
            }
        }
    }


    void StrategyEngine::addStrategy(IStrategy* stg){
        string tempexg = stg->getExg();
        if(strategyMap_.find(stg->getName())!=strategyMap_.end()){
            logger_->info("Duplicate Strategy");
            return;
        }
        strategyMap_[stg->getExg()] = stg;
        vector<string>& targetCode = stg->getTargetCode();
        
        for(auto it = targetCode.begin(); it!=targetCode.end(); ++it){
            auto temp = quoteMap_.find(tempexg+move("/")+*it);
            if(temp == quoteMap_.end()){
                quoteMap_[tempexg+move("/")+*it] = new StrategyCtx(it->c_str(), tempexg.c_str(), stg->getSize(), stg->getType());
                quoteMap_[tempexg+move("/")+*it]->addStrategy(stg);
                quoteMap_[tempexg+move("/")+*it]->start();
            }
            else{
                temp->second->addStrategy(stg);
            }
        }
        logger_->info(fmt::format("Added New Strategy: {}", stg->getName()).c_str());
    }


}