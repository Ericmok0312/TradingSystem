#include "Interface/IMessenger.h"
#include "Helper/logger.h"
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

    MsgqNNG::MsgqNNG(MSGQ_PROTOCOL protocol, string url, bool binding = true):IMsgq(protocol, url){
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

                svalid += nng_pub0_open(&sock_);
                svalid += nng_listener_create(&Lid_, sock_, url_.c_str());
                svalid += nng_listener_set_size(Lid_, NNG_OPT_SENDBUF, 8192);
                svalid += nng_listener_start(Lid_,-1);


            /*
            SUB:
                Create a sub socket with nng_pub0_open
                Create a dialer with nng_dialer_create
                Setting the timeout (100ms) for the dialer
                Start the dialer, -1 is dummy input
            */  
            case MSGQ_PROTOCOL::SUB :

                svalid += nng_sub0_open(&sock_);
                svalid += nng_dialer_create(&Did_, sock_, url_.c_str());
                svalid += nng_dialer_set_ms(Did_, NNG_OPT_RECVTIMEO, nng_duration(100));
                svalid += nng_dialer_start(Did_,-1);


            /*
            PUSH
                Similar to SUB
            */
            case MSGQ_PROTOCOL::PUSH :

                svalid += nng_push0_open(&sock_);
                svalid += nng_dialer_create(&Did_, sock_, url_.c_str());
                svalid += nng_dialer_set_ms(Did_, NNG_OPT_RECVTIMEO, nng_duration(100));
                svalid += nng_dialer_start(Did_,-1);
            /*
            PULL
                Similar to PUB
            */
            case MSGQ_PROTOCOL::PULL :

                svalid += nng_pull0_open(&sock_);
                svalid += nng_listener_create(&Lid_, sock_, url_.c_str());
                svalid += nng_listener_set_size(Lid_, NNG_OPT_SENDBUF, 8192);
                svalid += nng_listener_start(Lid_,-1);

        }
        if (svalid ){
            logger_->error(fmt::format("NNG connect sock {} error", url_).c_str());
        }
        assert(svalid);

    }

    /*
    Destructor of MsgqNNG
        Once socket is closed, all attached listeners / dialers are closed implicitly
    
    */

    MsgqNNG::~MsgqNNG(){
        nng_close(sock_);
    }



}