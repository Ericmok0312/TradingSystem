#ifndef SRC_INTERFACE_IMESSENGER_H
#define SRC_INTERFACE_IMESSENGER_H

#include "Helper/logger.h"
#include "Interface/datastructure.h"
#include <mutex>
#include <memory>
#include <string>

using namespace std;

namespace ts{

/*

IMessenger
    Interface for MsgqEMessenger (Messenger used for the engine, except on trading strategy) and MsgqTSMessenger (Messenger used by trading strategy engine)

    protected:
        logger_ : shared_ptr to the logger

    public:
        name_ : string identifing the Messenger object

        IMessenger(): constructor
        virtual ~IMessenger(): destructor

        virtual void send(std::shared_ptr<ts::Msg>, int32_t mode = 0): pure virtual function for sending message, encapsulated the NNG functions
        virtual std::shared_ptr<Msg> recv(int32_t mode = 0) = 0: pure virtual function for receving message, encapsulated the NNG functions
        virtual void relay() : pure virtual function for relaying the message -> all message are sent using MsgqEMessenger and cetain message is relayed by MsgqEMessenger to msgqTSMessenger
                               by calling the static shared_ptr msgq_send_


*/
class IMessenger{
    protected:

        std::shared_ptr<spdlog::logger> logger_;

    public:
        string name_;
        IMessenger();
        virtual ~IMessenger();

        virtual void send(std::shared_ptr<ts::Msg>, int32_t mode = 0) = 0;
        virtual std::shared_ptr<Msg> recv(int32_t mode = 0) = 0;
        virtual void relay() = 0;

};


/*

IMsgq
    Interface for Msgq encapulating NNG functions

    protected:
        protocol_: MSGQ_PROTOCOL type, indicating the protocol used
        url : string indicating the location of this Msgq
        logger_ : pointer to the logger
    
    public:
        IMsgq(MSGQ_PROTOCOL protocol, string url): constructor
        virtual ~IMsgq(): destructor

        virtual void sendmsg(const string& str, int32_t immediate = 1) : pure virtual function for sending message (receiving string as input)
        virtual void sendmsg(const char* str, int32_t immediate = 1) : pure virtual function overloading for const char* input

        virtual string recmsg(int32_t blockingflags = 1) : pure virtual function used when message is received

*/

class IMsgq{

    protected:
        MSGQ_PROTOCOL protocol_;
        string url_;
        std::shared_ptr<spdlog::logger> logger_;

    public:
        IMsgq(MSGQ_PROTOCOL protocol, string url);
        virtual ~IMsgq();

        virtual void sendmsg(const string& str, int32_t immediate = 1) = 0;
        virtual void sendmsg(const char* str, int32_t immediate = 1) = 0;

        virtual string recmsg(int32_t blockingflags = 1) = 0;
};


/*
MsgqNNG
    Class inheriting IMsgq, encapsulating NNG functions

    private:
        socket_ : indicating whether socket is initialized correctly
        eid_ : indicating the endpoint id of the socket adding to
        endpoint_ : url of the endpoint
    
    public:
        MsgqNNG(MSGQ_PROTOCOL protocol, string url, bool binding = true)
            -constructor, receiving 3 inputs
                - protocol -> indicating protocol used by this object
                - url -> indicating the DESTINATION url
                - binding -> indicating whether the endpoint can be used by other applications

        ~MsgqNNG(): destructor, handling proper destruction of NNG socket

        virtual void sendmsg(const string& str, int32_t immediate = 1) override: function overriding pure virtual function
        virtual void sendmsg(const char* str, int32_t immediate = 1) override: : function overriding pure virtual function
        virtual string recmsg(int32_t blockingflags = 1) override: : function overriding pure virtual function

*/




class MsgqNNG : public IMsgq {
    private:
        int32_t sock_ = -1;
        int32_t eid_ = 0;
        string endpoint_;

    public:
        MsgqNNG(MSGQ_PROTOCOL protocol, string url, bool binding = true);
        ~MsgqNNG();

        
        virtual void sendmsg(const string& str, int32_t immediate = 1) override;
        virtual void sendmsg(const char* str, int32_t immediate = 1) override;
        virtual string recmsg(int32_t blockingflags = 1) override;
};


/*

MsgqEMessenger 
    Messenger class used in the system, msgq_server_ are set to static, the whole system will use the same msgq_server througout the system
    msgq_receiver is the unique IMsgq object registered within each engine, each engine has their own one.
    msgq_server is set up when the core engine is set up, all other peritheral engines will use this engine to push message to different destination msgq_receiver
    
    private:
        msgq_receiver_ : unique_ptr of the gateway for this particular messenger to receive message from the unique msgq_server_
    
    public:
        sendlock_ : static mutex ensuring thread-safe sending message
        msgq_server_ : static unique_ptr shared by the whole system, thread-safe sending is ensured with sendlock_

        explicit MsgqEMessenger(string url_recv): constructor, with url of this messenger as input
        virtual ~MsgqEMessenger() {}: default destructor

        
        static void Send(std::shared_ptr<Msg> pmsg, int32_t mode = 0): static send function for special uses, avoid to use, may delete later


        virtual void send(std::shared_ptr<Msg> pmsg, int32_t mode = 0): send function used by the messenger, sendlock_ will be locked before sending message
        virtual std::shared_ptr<Msg> recv(int32_t mode = 0) {return nullptr;}: only useful in MsgqTSMessenger.
        virtual void relay(): used in MsgqEMessenger to call MsgqTSMessenger for certain cases, calling the send function respectively
*/

class MsgqEMessenger : public IMessenger {
 private:
    std::unique_ptr<IMsgq> msgq_receiver_;

 public:
    explicit MsgqEMessenger(string url_recv);
    virtual ~MsgqEMessenger() {}

    static mutex sendlock_;
    static std::unique_ptr<IMsgq> msgq_server_;
    static void Send(std::shared_ptr<Msg> pmsg, int32_t mode = 0);


    virtual void send(std::shared_ptr<Msg> pmsg, int32_t mode = 0);
    virtual std::shared_ptr<Msg> recv(int32_t mode = 0) {return nullptr;}
    virtual void relay();
};



class MsgqTSMessenger : public IMessenger {
 private:
    std::unique_ptr<IMsgq> msgq_receiver_;

 public:
    explicit MsgqTSMessenger(string url_recv);
    virtual ~MsgqTSMessenger() {}

    static mutex sendlock_;
    static std::unique_ptr<IMsgq> msgq_server_;
    static void Send(std::shared_ptr<Msg> pmsg, int32_t mode = 0);


    virtual void send(std::shared_ptr<Msg> pmsg, int32_t mode = 0);
    virtual std::shared_ptr<Msg> recv(int32_t mode = 0);
    virtual void relay();
};


};


#endif