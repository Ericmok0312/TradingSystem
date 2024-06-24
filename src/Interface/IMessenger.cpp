#include "Interface/IMessenger.h"
#include "Helper/logger.h"
#include "datastructure.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include "nng/protocol/pubsub0/pub.h"
#include "nng/protocol/pubsub0/sub.h"
#include "nng/protocol/pipeline0/pull.h"
#include "nng/protocol/pipeline0/push.h"
using namespace std;

namespace ts{
    
    
    // start of IMessenger

    /*
    - getting logger_ using Logger::getInstance();
    */
    IMessenger::IMessenger(){
        logger_ = Logger::getInstance();
    }

    IMessenger::~IMessenger(){}; // default destructor


    // End of IMessenger


    // Start of IMsgq


    /*
    -set up url and protocol with parameters
    -set up logger using getInstance();
    */
    IMsgq::IMsgq(MSGQ_PROTOCOL protocol, string url){

        protocol_ = protocol;
        url_ = url;
        logger_ = Logger::getInstance();

    }


    IMsgq::~IMsgq(){};    //default destructor


    // End of IMsgq

    //Start of MsgqNNG

    MsgqNNG::MsgqNNG(MSGQ_PROTOCOL protocol, string url, bool binding):IMsgq(protocol, url){
        int svalid = 0;
        switch(protocol_){
            /*
            PUB:
                Create a pub socket with nng_pub0_open
                Create a listener with nng_listener_create
                Setting the buffer size for the listener, 8192 MESSAGES
                Start the listener, -1 is dummy input
            */  
            case MSGQ_PROTOCOL::PUB :
                svalid = nng_pub0_open(&sock_);
                svalid = nng_listener_create(&Lid_, sock_, url_.c_str());   
                svalid = nng_socket_set_size(sock_, NNG_OPT_SENDBUF, size_t(8192));
                svalid = nng_listener_start(Lid_,0);
                break;

            /*
            SUB:
                Create a sub socket with nng_pub0_open
                Create a dialer with nng_dialer_create
                Setting the timeout (100ms) for the socket (not dialer, will lead to error)
                Setting receive buffer for the socket
                NOTE: setting subscribe for the socket (This is important)
                Start the dialer, -1 is dummy input
            */  
            case MSGQ_PROTOCOL::SUB :

                svalid += nng_sub0_open(&sock_);
                svalid += nng_dialer_create(&Did_, sock_, url_.c_str());
                svalid += nng_socket_set(sock_, NNG_OPT_SUB_SUBSCRIBE, "", 0);
                svalid += nng_socket_set_ms(sock_, NNG_OPT_RECVTIMEO, nng_duration(100));
                svalid += nng_dialer_start(Did_,-1);
                break;

            /*
            PUSH
                Similar to SUB
            */
            case MSGQ_PROTOCOL::PUSH :
                svalid += nng_sub0_open(&sock_);
                svalid += nng_dialer_create(&Did_, sock_, url_.c_str());
                svalid += nng_socket_set_ms(sock_, NNG_OPT_RECVTIMEO, nng_duration(100));
                svalid += nng_dialer_start(Did_,-1);
                break;

            /*
            PULL
                Similar to PUB
            */
            case MSGQ_PROTOCOL::PULL :
                svalid = nng_pub0_open(&sock_);
                svalid = nng_listener_create(&Lid_, sock_, url_.c_str());   
                svalid = nng_socket_set_size(sock_, NNG_OPT_SENDBUF, size_t(8192));
                svalid = nng_listener_start(Lid_,0);
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
        nng_close(sock_);
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
        int success = nng_send(sock_, const_cast<char*>(str.data()), str.size()+1, immediate);
        if (success){
            logger_ ->error(fmt::format("NNG {} send msg error, return: {}", sock_.id, success).c_str());
        }
    }

    void MsgqNNG::sendmsg(const char* str, int32_t immediate){
        int success = nng_send(sock_, const_cast<char*>(str), strlen(str)+1, immediate);
        if (success){
            logger_ ->error(fmt::format("NNG {} send msg error, return: {}", sock_.id, success).c_str());
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

    string MsgqNNG::recmsg(int32_t blockingflags){
        void* buf = nullptr;
        size_t len;
        int success = nng_recv(sock_, &buf, &len, blockingflags);

        if (success==0 && buf){
            string msg(static_cast<char*>(buf));
            nng_free(buf, len);
            return msg;
        }
        else{
            return string{};
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
    MsgqRMessenger::MsgqRMessenger(string url_recv){
        msgq_receiver_ = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PULL, url_recv);
    }


    /*
    Default destructor
    */
    MsgqRMessenger::~MsgqRMessenger(){}


    /*
    static void Send(std::shared_ptr<Msg> pmsg, int32_t mode = 0);
        - static function used to send message out
        - NOTE: mode : 1 -> zero-copy mode  2->Non-blocking mode
        - sendlock_ is locked for thread-safety
        - msgq_server->sendmsg is calledd
    */

    void MsgqRMessenger::Send(std::shared_ptr<Msg> pmsg, int flag){
        string msg = pmsg->serialize();
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
        string msg = pmsg->serialize();
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
        string msgpull = msgq_receiver_->recmsg(NNG_FLAG_ALLOC);
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

    std::unique_ptr<IMsgq> MsgqTSMessenger::msgq_server_; //initialize msgq_server_

    //Construcotor of MsgqTSMessenger
    MsgqTSMessenger::MsgqTSMessenger(string url_recv){
        msgq_receiver_ = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::SUB, url_recv);
    }

    //Default destructor
    MsgqTSMessenger::~MsgqTSMessenger(){}


    //Send function similar to MsgqRMessenger
    void MsgqTSMessenger::Send(std::shared_ptr<Msg> pmsg, int flag){
        string msg = pmsg->serialize();
        lock_guard<std::mutex> lock(MsgqTSMessenger::sendlock_);
        MsgqTSMessenger::msgq_server_->sendmsg(msg, flag);
    }
    //send function similar to MsgqRMessenger
    void MsgqTSMessenger::send(std::shared_ptr<Msg> pmsg, int flag){
        string msg = pmsg->serialize();
        lock_guard<std::mutex> lock(MsgqTSMessenger::sendlock_);
        MsgqTSMessenger::msgq_server_->sendmsg(msg, flag);
    }

    std::shared_ptr<Msg> MsgqTSMessenger::recv(int flag){
        string msgin = msgq_receiver_->recmsg(flag);
        if (msgin.empty()) return nullptr;
        try{
            string des;
            string src;
            string type;
            stringstream stream_msgin(msgin);
            getline(stream_msgin, des, SERIALIZATION_SEP);
            getline(stream_msgin, src, SERIALIZATION_SEP);
            getline(stream_msgin, type, SERIALIZATION_SEP);
            MSG_TYPE msgtype = MSG_TYPE(stoi(type));

            std::shared_ptr<Msg> msgheader;

            switch (msgtype){
                case MSG_TYPE_SUBSCRIBE_MARKET_DATA:
                    msgheader = std::make_shared<SubscribeMsg>(des, src);
                    break;
                case MSG_TYPE_DEBUG:
                    msgheader = std::make_shared<Msg>(des, src,MSG_TYPE_DEBUG);
                    break;
                case MSG_TYPE_ACCOUNTINFO:
                    msgheader = std::make_shared<AccountInfoMsg>(des, src);
                    msgheader->deserialize(msgin);
                    break;
                case MSG_TYPE_GET_ACCOUNTINFO:
                    msgheader = std::make_shared<EngineOperationMsg>(des, src, msgtype);
                    msgheader->deserialize(msgin);
                    break;
            }
            return msgheader;
        }
        catch(std::exception& e){
            logger_->error(fmt::format("{} [Original msg]: {}",e.what(),msgin).c_str());
        }
    }



    void MsgqTSMessenger::relay(){}; // relay function will not be called in MsgqTSMessenger
    //End of MsgqTSMessenger

    //
}