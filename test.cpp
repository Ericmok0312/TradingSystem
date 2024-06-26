#include<Helper/logger.h>
#include <Interface/IMessenger.h>
using namespace std;
using namespace ts;
#include <thread>
#include <memory>
#include <FUTU/FutuEngine.h>
#include <json/json.h>
#include <DataManager/DataManager.h>

void func_1(){
    if(!MsgqTSMessenger::msgq_server_){
        MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
    }
    sleep(10);
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    std::shared_ptr<Msg> msg = std::make_shared<Msg>();
    Json::Value param;
    param["code"] = "00700";
    param["subtype"] = 0;
    msg->data_ = param;
    msg->destination_ = "FutuEngine";
    msg->source_ = "Main";
    msg->msgtype_ = MSG_TYPE_REGCALLBACK;
    MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);
    msg->data_["code"] = "09999";
    MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);
    msg->data_["code"] = "02319";
    MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);    
    while(true){
    }
}


void func_11(){
    if(!MsgqTSMessenger::msgq_server_){
        MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
    }
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    std::shared_ptr<Msg> msg = std::make_shared<Msg>();
    Json::Value param;
    param["id"] = "8865506";
    param["market"] = "1";
    param["mode"] = "0";
    msg->data_ = param;
    msg->destination_ = "FutuEngine";
    msg->source_ = "Main";
    msg->msgtype_ = MSG_TYPE_GET_ACCOUNTINFO;
    while(true){
    MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);
    sleep(3);
    }
}

void func_2(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    ts::MsgqTSMessenger rec2 (PROXY_SERVER_URL);
    LOG->info("dialer2 created");
 
    while(true){ 
        std::shared_ptr<Msg> msg2 = rec2.recv(NNG_FLAG_NONBLOCK+NNG_FLAG_ALLOC); // nonblock + ALLOC
        if(msg2 && msg2->destination_=="Main"){
            LOG->info(fmt::format("function2 received {}",msg2->serialize()).c_str());
        }
    }
}




void func_3(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    FutuEngine eng;
    std::chrono::microseconds ms = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
    LOG->info(fmt::format("futu created, current timestamp:{}", to_string(ms.count())).c_str());
    eng.start();
    
}


void func_4(){

    std::shared_ptr<Logger> LOG = Logger::getInstance();
    // ts::MsgqTSMessenger rec (PROXY_SERVER_URL);
    // LOG->info("dialer3 created");
 
    // while(true){ 
    //     std::shared_ptr<Msg> msg = rec.recv(NNG_FLAG_NONBLOCK+NNG_FLAG_ALLOC); // nonblock + ALLOC
    //     if(msg && msg->destination_=="DataManager"){
    //         LOG->info(fmt::format("DataManager received {}",msg->serialize()).c_str());
    //     }
    // }

    DataManager dm;
    LOG->info("dm created");
    dm.start();

}


int main(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    if(!MsgqTSMessenger::msgq_server_){
        MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
    }
    sleep(2);

  
    std::thread t1(func_11);
    std::thread t2(func_2);
    std::thread t3(func_3);
    std::thread t4(func_4);


    std::thread sb(func_1);
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    sb.join();


    return 0;
}