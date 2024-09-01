
#include "Strategy/TradeUtil.h"
#include "Interface/datastructure.h"
#include "atomic"
#include "memory"
#include "sstream"
#include "Helper/util.h"
#include "boost/thread/thread.hpp"
#include <boost/chrono.hpp>
#include <mutex>

using namespace std;

namespace ts{


    void StrategyCtx::regRequest(){
        
        shared_ptr<Msg> msg = make_shared<Msg>();
        msg->destination_ = move("DataManager");
        msg->source_ = this->name_;
        msg->msgtype_ = MSG_TYPE_GET_QUOTE_BLOCK;
        
        stringstream ss;
        shared_ptr<ARG> arg = make_shared<ARG>(exg_.c_str(), code_.c_str(), size_, GetTimeStamp(),name_.c_str(), QUOTE);
        msg->data_ = move(arg->seriralize());
        messenger_->send(msg, 0);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(frequency_));
        
        //registrating sub in corresponding broker, by default FUTU
        std::shared_ptr<Msg> regmsg = std::make_shared<Msg>();
        if(exg_ == "FUTU"){
            regmsg->destination_ = "FutuEngine";
        }
        else{
            regmsg->destination_ = "FutuEngine";
        }
        regmsg->source_ = name_;
        regmsg->msgtype_ = MSG_TYPE_REGCALLBACK;

        rapidjson::Document d;
        d.SetObject();
        d.AddMember("code", rapidjson::Value(code_.data(), code_.size(), d.GetAllocator()), d.GetAllocator());
        d.AddMember("subtype", rapidjson::Value(type_), d.GetAllocator());
        Json2String(d, regmsg->data_);
        messenger_->send(regmsg, 0);

    }

    void StrategyCtx::OnDataUpdate(){
        //messenger_->setSubscribe(name_.c_str());
        std::shared_ptr<Msg> msg;

        while(estate_.load() != STOP){

            msg = messenger_->recv(0);
            
            if(msg && msg->destination_ == name_){

                std::lock_guard<std::mutex> lg(mutexData_);
                delete data_;
                data_ = reinterpret_cast<BaseData*>(std::strtoull(msg->data_.c_str(), nullptr, 16));
                for(auto it = StrategyMap_.begin(); it!=StrategyMap_.end(); ++it){
                    it->second->onUpdateData(this);
                }
                }
            }
        }
    

    StrategyCtx::StrategyCtx(const char* code, const char* exg, int size, SubType type, int freq)
    :
    position_(code, exg, 0, 0),
    data_(nullptr),
    size_(size),
    code_(code), 
    exg_(exg), 
    name_("StrategyCtx_"+to_string(StrategyCtxcount_.load())),
    frequency_(freq), 
    messenger_(MsgqTSMessenger::getInstance(name_.c_str())), 
    logger_(Logger::getInstance(name_.c_str())),
    lprice_(0.0),
    type_(type),
    mutexData_(){
        init();
    }

    StrategyCtx::~StrategyCtx(){
        delete data_;
        data_ = nullptr;
    }


    void StrategyCtx::init(){
        StrategyCtxcount_.fetch_add(1);
        estate_.store(Estate::STOP);
    }


    void StrategyCtx::stop(){
        estate_.store(Estate::STOP);
    }

    void StrategyCtx::start(){
        estate_.store(CONNECTED);
        boost::thread t1(bind(&StrategyCtx::OnDataUpdate, this));
        boost::thread t2(bind(&StrategyCtx::regRequest, this));
    }


    std::atomic<int> StrategyCtx::StrategyCtxcount_{0};


    const BaseData* StrategyCtx::getCur(){
        //std::lock_guard<std::mutex> lg(mutexData_);

        QuoteSlice* temp = static_cast<QuoteSlice*>(data_);
        if(temp && temp->getCount() > 0){
            if(temp->at(temp->at(temp->getCount()-1)->cPrice_ != lprice_)){
                lprice_ = temp->at(temp->getCount()-1)->cPrice_;  
    
                return temp->at(temp->getCount()-1);
            }

        return nullptr;

    }}

    BaseData* StrategyCtx::getSlice(){
        std::lock_guard<std::mutex> lg(mutexData_);
        return data_;
    }


    void StrategyCtx::addStrategy(IStrategy* stg){
        lock_guard<mutex> lg(strategyMutex_);
        if(StrategyMap_.find(stg->getName())!=StrategyMap_.end()){
            logger_->info(fmt::format("Duplicate Strategy Name : {}", stg->getName()).c_str());
            return ; // assume name of strategy is unique
        }
        else{
            StrategyMap_.insert({stg->getName(), stg});
            logger_->info(fmt::format("Adding Strategy {} to {}", stg->getName(), name_).c_str());
        }
        return;
    }

    void StrategyCtx::SendMessage(shared_ptr<Msg> msg){
        messenger_->send(msg, 0);
    }

    void StrategyCtx::LoggingInfo(const char* info){
        logger_->info(info);
    }

    unique_ptr<BaseData> StrategyCtx::StratgeyGetOneTimeData(shared_ptr<Msg> msg2futu,shared_ptr<Msg> msg, const char* returnName){

        messenger_->send(msg2futu, 0); //for strategy that requires history data/ one-time data

        messenger_->send(msg,0);
        shared_ptr<Msg> returnmsg;
        while(true){
            returnmsg = messenger_->recv(0);
            if(returnmsg->destination_ == returnName){
                return move(unique_ptr<BaseData>(reinterpret_cast<BaseData*>(std::strtoull(msg->data_.c_str(), nullptr, 16))));
            }
        }

    }




}


