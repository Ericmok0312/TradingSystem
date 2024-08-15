#ifndef SRC_INTERFACE_IMESSENGER_H
#define SRC_INTERFACE_IMESSENGER_H

#include "Helper/logger.h"
#include "Interface/datastructure.h"
#include <mutex>
#include <memory>
#include <string>
#include <zmq.hpp>

#define PROXY_SERVER_URL "tcp://localhost:8888"

using namespace std;
using namespace zmq;
namespace ts{

/*

IMessenger
    Interface for MsgqRMessenger (Messenger used for the engine, except on trading strategy) and MsgqTSMessenger (Messenger used by trading strategy engine)

    protected:
        logger_ : shared_ptr to the logger

    public:
        IMessenger(): constructor
        virtual ~IMessenger(): destructor

        virtual void send(std::shared_ptr<ts::Msg>, int32_t mode = 0): pure virtual function for sending message, encapsulated the NNG functions
        virtual std::shared_ptr<Msg> recv(int32_t mode = 0) = 0: pure virtual function for receving message, encapsulated the NNG functions
        virtual void relay() : pure virtual function for relaying the message -> all message are sent using MsgqRMessenger and cetain message is relayed by MsgqRMessenger to msgqTSMessenger
                               by calling the static shared_ptr msgq_send_


*/
class IMessenger{
    protected:
       
        std::shared_ptr<Logger> logger_;


    public:
        
        IMessenger(const char*);
        virtual ~IMessenger();
        
        virtual void send(std::shared_ptr<ts::Msg>, int32_t mode = 0){};
        virtual std::shared_ptr<Msg> recv(int32_t mode = 0) {return make_shared<Msg>();}
        virtual void relay() {};

};


/*

IMsgq
    Interface for Msgq encapulating NNG functions

    protected:
        protocol_: MSGQ_PROTOCOL type, indicating the protocol used
        url : string indicating the endpoint url
        logger_ : pointer to the logger
    
    public:
        IMsgq(MSGQ_PROTOCOL protocol, string url): constructor
        virtual ~IMsgq(): destructor

        virtual void sendmsg(const string& str, int32_t immediate = 1) : pure virtual function for sending message (receiving string as input)
        virtual void sendmsg(const char* str, int32_t immediate = 1) : pure virtual function overloading for const char* input

        virtual char* recmsg(int32_t blockingflags = 1) : pure virtual function used when message is received

*/

class Context{
        static context_t* ctx_;
        static shared_ptr<Context> instance_;
        shared_ptr<Logger> logger_;
        static mutex getInstanceLock_;
    public:

        context_t* GetContext();
        
        static shared_ptr<Context> getInstance();
        Context();
        ~Context();

};

class IMsgq{

    protected:
        MSGQ_PROTOCOL protocol_;
        string url_;
        std::shared_ptr<Logger> logger_;
        shared_ptr<Context> context_;
    public:
        IMsgq(MSGQ_PROTOCOL protocol, const string& url);
        virtual ~IMsgq();

        virtual void sendmsg(const string& str, int32_t immediate = 1) = 0;
        virtual void sendmsg(char* str, int32_t immediate = 1) = 0;

        virtual char* recmsg(int32_t blockingflags = 1) = 0;
};


/*
MsgqNNG
    Class inheriting IMsgq, encapsulating NNG functions

    private:
        socket_ : indicating whether socket is initialized correctly
        id_ : indicating the id of the listener/dialer

    
    public:
        MsgqNNG(MSGQ_PROTOCOL protocol, string url, bool binding = true)
            -constructor, receiving 3 inputs
                - protocol -> indicating protocol used by this object
                - url -> indicating the url where the listener listen at / dialer connect to 
                - binding -> indicating whether the endpoint can be used by other applications

        ~MsgqNNG(): destructor, handling proper destruction of NNG socket

        virtual void sendmsg(const string& str, int32_t immediate = 1) override: function overriding pure virtual function
        virtual void sendmsg(const char* str, int32_t immediate = 1) override: : function overriding pure virtual function
        virtual char recmsg(int32_t blockingflags = 1) override: : function overriding pure virtual function

*/




class MsgqNNG : public IMsgq {
    private:
        socket_t sock_;

    public:
        

        MsgqNNG(MSGQ_PROTOCOL protocol, const string& url, bool binding = true);
        ~MsgqNNG();

        socket_t* getSocket();
        
        virtual void sendmsg(const string& str, int32_t flag) override;
        virtual void sendmsg(char* str, int32_t flag) override;
        virtual char* recmsg(int32_t flag) override;
};


/*

MsgqRMessenger 
    Messenger class used in the system, msgq_server_ are set to static, the whole system will use the same msgq_server througout the system
    msgq_receiver is the unique IMsgq object registered within each engine, each engine has their own one.
    msgq_server is set up when the core engine is set up, all other peritheral engines will use this engine to push message to different destination msgq_receiver
    
    private:
        msgq_receiver_ : unique_ptr of the gateway for this particular messenger to receive message from the unique msgq_server_
    
    public:
        sendlock_ : static mutex ensuring thread-safe sending message
        msgq_server_ : static unique_ptr shared by the whole system, thread-safe sending is ensured with sendlock_

        explicit MsgqRMessenger(string url_recv): constructor, with url of this messenger as input
        virtual ~MsgqRMessenger() {}: default destructor

        
        static void Send(std::shared_ptr<Msg> pmsg, int32_t mode = 0): static send function for special uses, avoid to use, may delete later


        virtual void send(std::shared_ptr<Msg> pmsg, int32_t mode = 0): send function used by the messenger, sendlock_ will be locked before sending message
        virtual std::shared_ptr<Msg> recv(int32_t mode = 0) {return nullptr;}: only useful in MsgqTSMessenger.
        virtual void relay(): used in MsgqRMessenger to call MsgqTSMessenger for certain cases, calling the send function respectively
*/

class MsgqRMessenger : public IMessenger {
 private:
    std::unique_ptr<IMsgq> msgq_receiver_;

 public:

    static mutex sendlock_;
    static std::unique_ptr<IMsgq> msgq_server_;

    explicit MsgqRMessenger(const string& url_recv);
    virtual ~MsgqRMessenger();


    static void Send(std::shared_ptr<Msg> pmsg, int flag);


    virtual void send(std::shared_ptr<Msg> pmsg, int flag);
    virtual std::shared_ptr<Msg> recv(int flag);
    virtual void relay();
};



class MsgqTSMessenger : public IMessenger {
 private:
    std::unique_ptr<IMsgq> msgq_receiver_;

 public:
    void setSubscribe(const char* topic);
    static mutex sendlock_;
    static std::unique_ptr<IMsgq> msgq_server_;
    static std::mutex instancelock_;
    
    explicit MsgqTSMessenger(const string& url_recv);
    virtual ~MsgqTSMessenger();
    
    static shared_ptr<MsgqTSMessenger> instance_;

    static shared_ptr<MsgqTSMessenger> getInstance();
    static void Send(std::shared_ptr<Msg> pmsg, int flag);
    virtual void send(std::shared_ptr<Msg> pmsg, int flag);
    virtual std::shared_ptr<Msg> recv(int flag);
    virtual void relay();
};


};


#endif