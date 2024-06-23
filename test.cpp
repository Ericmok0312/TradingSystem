#include<Helper/logger.h>
#include <Interface/IMessenger.h>
using namespace std;
using namespace ts;
#include <thread>
#include <memory>



void func_1(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    ts::MsgqTSMessenger rec1 (PROXY_SERVER_URL);
    LOG->info("dialer1 created");
    std::shared_ptr<Msg> msg1;
    while(true){ 
        msg1 = rec1.recv(NNG_FLAG_NONBLOCK+NNG_FLAG_ALLOC); // nonblock + ALLOC
        if(msg1){
            LOG->info(fmt::format("function1 received {}", msg1->serialize()).c_str());
        }
    }
}

void func_2(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    ts::MsgqTSMessenger rec2 (PROXY_SERVER_URL);
    LOG->info("dialer2 created");
    while(true){ 
        std::shared_ptr<Msg> msg2;
        msg2 = rec2.recv(NNG_FLAG_NONBLOCK+NNG_FLAG_ALLOC); // nonblock + ALLOC
        if(msg2){
            LOG->info(fmt::format("function2 received {}",msg2->serialize()).c_str());
        }
    }
}

void func_3(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    if(!MsgqTSMessenger::msgq_server_){
        MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
    }
    LOG->info("listenr created");
    while(true){
        int i=0;
        Msg msg ("server", "subfunc", MSG_TYPE::MSG_TYPE_DEBUG);
        LOG->info("called 1111");
        MsgqTSMessenger::msgq_server_->sendmsg(msg.serialize().c_str(), 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        i++;
    }
}

int main(){
    std::shared_ptr<Logger> LOG = Logger::getInstance();
    if(!MsgqTSMessenger::msgq_server_){
        MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
    }
    sleep(2);

    std::thread t1(func_1);
    std::thread t3(func_3);
    std::thread t2(func_2);
    t3.join();
    t1.join();
    t2.join();


    return 0;
}