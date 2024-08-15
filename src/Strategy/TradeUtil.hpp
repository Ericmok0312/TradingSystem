

#ifndef SRC_STRATEGY_TRADEUTIL_HPP
#define SRC_STRATEGY_TRADEUTIL_HPP
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

    string getTypeName(LoaderType type){
        switch(type){
            case LoaderType::QUOTE:
                return move("Quote");
                break;
            case LoaderType::KLINE:
                return move("Kline");
                break;
            case LoaderType::TICKER:
                return move("Ticker");
                break;
            default:
                return move("Unkown");
        }
    }

    template<typename T>
    void Loader<T>::regRequest(){
        while(*state_){
            shared_ptr<Msg> msg = make_shared<Msg>();
            msg->destination_ = move("DataManager");
            msg->source_ = this->name_;
            msg->msgtype_ = MSG_TYPE_GET_QUOTE_BLOCK;
            stringstream ss;
            ss<<exg_<<"^"<<code_<<"^"<<size_<<"^"<<to_string(GetTimeStamp())<<"^"<<name_;
            msg->data_ = move(ss.str());
            messenger_->send(msg, 0);
            boost::this_thread::sleep_for(boost::chrono::milliseconds(frequency_));
        }

    }
    template<typename T>
    void Loader<T>::recvProcess(){
        //messenger_->setSubscribe(name_.c_str());
        std::shared_ptr<Msg> msg;
        while(*state_){
            msg = messenger_->recv(0);
            if(msg && msg->destination_==name_){
                std::lock_guard<std::mutex> lg(mutexData_);
                delete data_;
                data_ = reinterpret_cast<T*>(std::strtoull(msg->data_.c_str(), nullptr, 16));
                }
            }
        }
    

    template<typename T>
    Loader<T>::Loader(const char* code, const char* exg, int size, LoaderType type, bool* state, int freq)
    :
    data_(nullptr),
    size_(size),
    code_(code), 
    exg_(exg), 
    name_("loader_"+move(getTypeName(type))+to_string(loadercount_.load())),
    last_data_(nullptr),
    frequency_(freq), 
    messenger_(MsgqTSMessenger::getInstance()), 
    type_(type), 
    state_(state),
    mutexData_(){
        run();
    }



    template<typename T>
    void Loader<T>::run(){
        boost::thread t1(bind(&Loader::recvProcess, this));
        boost::thread t2(bind(&Loader::regRequest, this));
    }

    template<typename T>
    std::atomic<int> Loader<T>::loadercount_{0};

    template<typename T>
    const BaseData* Loader<T>::getCur(){
        std::lock_guard<std::mutex> lg(mutexData_);
        if(data_ && data_->getCount() > 0){
        if(last_data_ != data_->at(data_->getCount()-1)){
            last_data_ = data_->at(data_->getCount()-1);
        }
        }
        return last_data_;
    }

    template<typename T>
    T* Loader<T>::getSlice(){
        std::lock_guard<std::mutex> lg(mutexData_);
        return data_;
    }
}

#endif