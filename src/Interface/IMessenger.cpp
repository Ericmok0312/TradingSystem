#include "Interface/IMessenger.h"
#include "Helper/logger.h"
#include "datastructure.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include <Helper/util.h>

#include "zmq.hpp"

using namespace zmq;
using namespace std;

namespace ts{
    
    
    // start of IMessenger

    /*
    - getting logger_ using Logger::getInstance();
    */
    IMessenger::IMessenger(const char* name){
        logger_ = make_shared<Logger>(name);
    }

    IMessenger::~IMessenger(){}; // default destructor


    // End of IMessenger


    // Start of IMsgq


    /*
    -set up url and protocol with parameters
    -set up logger using getInstance();
    */
    IMsgq::IMsgq(MSGQ_PROTOCOL protocol, const string& url){
        logger_ = make_shared<Logger>("IMsgq");
        protocol_ = protocol;
        url_ = url;
        context_ = Context::getInstance();
    }


    IMsgq::~IMsgq(){
        logger_->info("Destructing IMsgq");
    };    //default destructor


    //Context
    
    context_t* Context::ctx_;
    shared_ptr<Context> Context::instance_;
    mutex Context::getInstanceLock_;

    shared_ptr<Context> Context::getInstance(){
        lock_guard<mutex> lg(getInstanceLock_);
        if(!instance_){
            instance_ = make_shared<Context>();
            instance_->logger_ = make_shared<Logger>("Context");
        }
        return instance_;
    }

    context_t* Context::GetContext(){
        return ctx_;
    }

    Context::Context(){
        ctx_ = new context_t;
    }

    Context::~Context(){
        logger_->info("Context destructed");
        delete ctx_;
    }
    

    // End of IMsgq

    //Start of MsgqNNG

    socket_type getSockType(MSGQ_PROTOCOL protocol){
        switch (protocol) {
            case MSGQ_PROTOCOL::PUB:
                return zmq::socket_type::pub;
            case MSGQ_PROTOCOL::SUB:
                return zmq::socket_type::sub;
            case MSGQ_PROTOCOL::PUSH:
                return zmq::socket_type::push;
            case MSGQ_PROTOCOL::PULL:
                return zmq::socket_type::pull;
        }
        return zmq::socket_type::sub;
    }


    socket_t* MsgqNNG::getSocket(){
        return &(this->sock_);
    }

    MsgqNNG::MsgqNNG(MSGQ_PROTOCOL protocol,const string& url, bool binding):IMsgq(protocol, url), sock_(*context_->GetContext(), getSockType(protocol)){
        int svalid = 0;
        switch(protocol_){

            case MSGQ_PROTOCOL::PUB:
                sock_.bind(url);    
                break;

            case MSGQ_PROTOCOL::SUB:
                sock_.connect(url);
                sock_.set(zmq::sockopt::subscribe, "");      
                break;

            /*
            PUSH
                Similar to SUB
            */
            case MSGQ_PROTOCOL::PUSH:
                sock_.connect(url);   
                break;

            /*
            PULL
                Similar to PUB
            */
            case MSGQ_PROTOCOL::PULL:
                sock_.connect(url);   
                break;
        }
        if (svalid){
            logger_->error(fmt::format("NNG connect sock {} error, error {}", url_, std::to_string(svalid).c_str()).c_str());
        }
        assert(svalid==0);

    }

    /*
    Destructor of MsgqNNG
        Once socket is closed, all attached listeners / dialers are closed implicitly
    
    */

    MsgqNNG::~MsgqNNG(){
        sock_.close();
        logger_->info("Destructing MsgqNNG");
    }


    /*
    void MsgqNNG::sendmsg(const string& str, int32_t immediate)
    void MsgqNNG::sendmsg(const char* str, int32_t immediate)
        - overloading fucntions for send
        - immediate is the flag indicating that non-blocking mode is used
        - const string / const char* are casted to char* via const_cast
        NOTE: the buffer size is IMPORTANT, else will lead to error
    */
    void MsgqNNG::sendmsg(const string& str, int32_t immediate){
        sendmsg(str.c_str(), immediate);
    }

    void MsgqNNG::sendmsg(char* str, int32_t immediate){ // as is char*, temp string as input will not call this
        try{
            zmq::message_t msg(static_cast<void*>(str), strlen(str)+1, [](void* a, void* b){delete[] static_cast<char*>(a);}, nullptr);
            if(!sock_.send(move(msg), zmq::send_flags::none)){
                throw std::runtime_error("NNG send msg error");
            }
        }catch(const zmq::error_t& e) {
            logger_->warn(fmt::format("NNG send msg error: {}", e.what()).c_str());
        }
        }
          

    /*
    
    string MsgqNNG::recmsg(int32_t blockingflags)
        - function used when message is received
        - char* is created serving as buffer
        - size_t len is used to store the size of the message
        - temporary string msg is created from buf
        - nng_free need to be used to free the memory allocated to buf in nng_recv
        - Nonblocking mode is used

        - if no message, empty string is returned

    */

    char* MsgqNNG::recmsg(int32_t blockingflags){
        zmq::message_t msg;
        auto success = sock_.recv(msg, zmq::recv_flags::none);
        //
        if (msg.data()!=nullptr){
            char* nbuf = new char[strlen(static_cast<char*>(msg.data()))+1]; 
            strcpy(nbuf, static_cast<char*>(msg.data()));
            return nbuf;
        }
        else{
            return nullptr;
        }
    }


    //End of MsgqNNG


    //Start of MsgqRMessenger

    std::mutex MsgqRMessenger::sendlock_; //initialize static sendlock_

    std::unique_ptr<IMsgq> MsgqRMessenger::msgq_server_; // sender used, shared by all engine

    /*
    Constructor
        - initialize msgq_receiver
        - msgq_sender are intialized by core engine later
    */
    MsgqRMessenger::MsgqRMessenger(const string& url_recv):IMessenger("MsgqTSMessenger"){
        msgq_receiver_ = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PULL, url_recv);
    }


    /*
    Default destructor
    */
    MsgqRMessenger::~MsgqRMessenger(){
        logger_->info("Destructing MsgqRMessenger");
    }


    /*
    static void Send(std::shared_ptr<Msg> pmsg, int32_t mode = 0);
        - static function used to send message out
        - NOTE: mode : 1 -> zero-copy mode  2->Non-blocking mode
        - sendlock_ is locked for thread-safety
        - msgq_server->sendmsg is calledd
    */

    void MsgqRMessenger::Send(std::shared_ptr<Msg> pmsg, int flag){
        char* msg = pmsg->serialize();
        lock_guard<std::mutex> lock(MsgqRMessenger::sendlock_);
        MsgqRMessenger::msgq_server_->sendmsg(msg, flag);
    }

    /*
    non-static void send(std::shared_ptr<Msg> pmsg, int32_t mode = 0);
        - static function used to send message out
        - NOTE: mode : 1 -> zero-copy mode  2->Non-blocking mode
        - sendlock_ is locked for thread-safety
        - msgq_server->sendmsg is calledd
    */
    void MsgqRMessenger::send(std::shared_ptr<Msg> pmsg, int flag){
        char* msg = pmsg->serialize();
        lock_guard<std::mutex> lock(MsgqRMessenger::sendlock_);
        MsgqRMessenger::msgq_server_->sendmsg(msg, flag);
    }

    /*
    std::shared_ptr<Msg> MsgqRMessenger::recv(int32_t mode)
        - recv function of MsgqRMessenger should NOT be called, as this will be done by rely
        -NOTE: need to find why two different messenger are used
    */
    std::shared_ptr<Msg> MsgqRMessenger::recv(int flag){return nullptr;}


    void MsgqRMessenger::relay(){
        string msgpull = msgq_receiver_->recmsg(0);
        if(msgpull.empty()){
            return;
        }

        if(msgpull[0] == RELAY_DESTINATION){
            lock_guard<std::mutex> lock (MsgqTSMessenger::sendlock_);
            MsgqTSMessenger::msgq_server_ -> sendmsg(msgpull);
        }
        else{
            lock_guard<std::mutex> lock (MsgqRMessenger::sendlock_);
            MsgqRMessenger::msgq_server_ -> sendmsg(msgpull);
        }

    }

    //End of MsgqRMessenger

    //Start of MsgqTSMessenger
    std::mutex MsgqTSMessenger::sendlock_; //initialize sendlock_

    std::unique_ptr<IMsgq> MsgqTSMessenger::msgq_server_ = nullptr; //initialize msgq_server_

    shared_ptr<MsgqTSMessenger> MsgqTSMessenger::instance_ = nullptr;

    std::mutex MsgqTSMessenger::instancelock_;

    //Construcotor of MsgqTSMessenger
    MsgqTSMessenger::MsgqTSMessenger(const string& url_recv):IMessenger("MsgqTSMessenger"){
        std::lock_guard<mutex> lg(instancelock_);
        if(!msgq_server_){
                msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
        }
        msgq_receiver_ = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::SUB, url_recv);
    }

    //Default destructor
    MsgqTSMessenger::~MsgqTSMessenger(){
        logger_->info("Destructing MsgqTSessenger");
        instance_.reset();
    }


    //Send function similar to MsgqRMessenger
    void MsgqTSMessenger::Send(std::shared_ptr<Msg> pmsg, int flag){
        char* msg = pmsg->serialize();
        lock_guard<std::mutex> lock(MsgqTSMessenger::sendlock_);
        MsgqTSMessenger::msgq_server_->sendmsg(msg, flag);
    }
    //send function similar to MsgqRMessenger
    void MsgqTSMessenger::send(std::shared_ptr<Msg> pmsg, int flag){
        char* msg = pmsg->serialize();
        lock_guard<std::mutex> lock(MsgqTSMessenger::sendlock_);
        MsgqTSMessenger::msgq_server_->sendmsg(msg, flag);
    }

    /*
    
    shared_ptr<Msg> MsgqTSMessenger::recv(int flag)
    - Function for capturing message transmitted in NNG
    - As all messages shares the same structure, no need to generate different message based on msgtype_
    
    */

    std::shared_ptr<Msg> MsgqTSMessenger::recv(int flag){
        char* msgin = msgq_receiver_->recmsg(flag);
        if (!msgin) return nullptr;
        try{
            std::shared_ptr<Msg> msgheader = std::make_shared<Msg>();
            msgheader->deserialize(msgin);
            delete[] msgin; // msgin is allocated in serialization and not deleted
            return msgheader;
        }
        catch(std::exception& e){
            logger_->error(fmt::format("{} [Original msg]: {}",e.what(),msgin).c_str());
        }
        return nullptr;
    }


    shared_ptr<MsgqTSMessenger> MsgqTSMessenger::getInstance(){
        if(!instance_){
            instance_ = make_shared<MsgqTSMessenger>(PROXY_SERVER_URL);
        }
        return instance_;
    }
    void MsgqTSMessenger::relay(){}; // relay function will not be called in MsgqTSMessenger
    
    
    void MsgqTSMessenger::setSubscribe(const char * topic){
        socket_t* sk = static_cast<MsgqNNG*>(this->msgq_receiver_.get())->getSocket();
        sk->set(zmq::sockopt::subscribe, topic);
    }
    
    
    
    
    
    //End of MsgqTSMessenger

    //
}