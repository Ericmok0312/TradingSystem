#include<Helper/logger.h>
#include <Interface/IMessenger.h>
using namespace std;
using namespace ts;
#include <thread>
#include <memory>
#include <FUTU/FutuEngine.h>
#include <json/json.h>


void func_1(){
    if(!MsgqTSMessenger::msgq_server_){
        MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
    }
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    std::shared_ptr<Msg> msg;
    LOG->info("sender created");
    Json::Value param;
    param["id"] = "8865506";
    param["Market"] = "1";
    param["mode"] = "0";
    Json::StreamWriterBuilder writer;
    std::string s_param = Json::writeString(writer, param);
    while(true){
        msg = make_shared<EngineOperationMsg>("FutuEngine", "Main", MSG_TYPE_GET_ACCOUNTINFO, param);
        MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize().c_str(), 0);
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
    LOG->info("futu created");
    eng.start();
    
}


int main(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    if(!MsgqTSMessenger::msgq_server_){
        MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
    }
    sleep(2);


    std::thread t1(func_1);
    std::thread t2(func_2);
    std::thread t3(func_3);

    t1.join();
    t2.join();
    t3.join();



    return 0;
}