
#include<Helper/logger.h>
#include <Interface/IMessenger.h>
using namespace std;
using namespace ts;
#include "boost/thread/thread.hpp"
#include <boost/chrono.hpp>
#include <memory>
#include <FUTU/FutuEngine.h>
#include <json/json.h>
#include <DataManager/DataManager.h>
#include <DataManager/DataWriter.h>
#include <DataManager/DataReader.h>
#include <functional>
#include <random>


    class Tester{
    public:
        void func_1(){
            if(!MsgqTSMessenger::msgq_server_){
                MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
            }
            sleep(10);
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun1");
            std::shared_ptr<Msg> msg = std::make_shared<Msg>();

            string code = "00700";
            int sub = 0;

            msg->destination_ = "FutuEngine";
            msg->source_ = "Main";
            msg->msgtype_ = MSG_TYPE_REGCALLBACK;
            rapidjson::Document d;
            d.SetObject();
            d.AddMember("code", rapidjson::Value(code.data(), code.size(), d.GetAllocator()), d.GetAllocator());
            d.AddMember("subtype", rapidjson::Value(sub), d.GetAllocator());

            Json2String(d, msg->data_);
            MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);
            code = "09999";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);
            code = "02319";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);    
            while(true){
            }
        }


        void func_11(){
            if(!MsgqTSMessenger::msgq_server_){
                MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
            }
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun11");
            std::shared_ptr<Msg> msg = std::make_shared<Msg>();
            Json::Value param;
            int id = 8865506;
            int market = 1;
            int mode = 0;

            rapidjson::Document d;
            d.SetObject();
            d.AddMember("id", rapidjson::Value(id), d.GetAllocator());
            d.AddMember("market", rapidjson::Value(market), d.GetAllocator());
            d.AddMember("mode", rapidjson::Value(mode), d.GetAllocator());

            msg->destination_ = "FutuEngine";
            msg->source_ = "Main";
            Json2String(d, msg->data_);
            msg->msgtype_ = MSG_TYPE_GET_ACCOUNTINFO;
            while(true){
            MsgqTSMessenger::msgq_server_->sendmsg(msg->serialize(), 0);
            sleep(3);
            }
        }

        void func_2(){
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun2");
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
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun3");
            ts::FutuEngine eng;
            std::chrono::microseconds ms = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
            LOG->info(fmt::format("futu created, current timestamp:{}", to_string(ms.count())).c_str());
            eng.start();
            
        }


        void func_4(){

            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun4");
            // ts::MsgqTSMessenger rec (PROXY_SERVER_URL);
            // LOG->info("dialer3 created");

            // while(true){ 
            //     std::shared_ptr<Msg> msg = rec.recv(NNG_FLAG_NONBLOCK+NNG_FLAG_ALLOC); // nonblock + ALLOC
            //     if(msg && msg->destination_=="DataManager"){
            //         LOG->info(fmt::format("DataManager received {}",msg->serialize()).c_str());
            //     }
            // }

            // DataManager dm;
            // LOG->info("dm created");
            // dm.start();


            
            return;
        }


        
        void test_dataWriter(){

            std::mt19937 rng(std::random_device{}()); // Mersenne Twister engine
            std::uniform_int_distribution<int> dist(0, 10); // [0, 10) range
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();


            //q.reset();
            int i = 0;
            while(i<100){
                auto q = make_shared<Quote>();
                strcpy(q->code_, "02222");
                strcpy(q->exg_ ,"Futu");
                strcpy(q->time_, "test");     
                q->timestamp_ = GetTimeStamp();
                q->cPrice_ = i;
                shared_ptr<Msg> msg = make_shared<Msg>("DataManager", "Tester", MSG_TYPE_STORE_QUOTE, q->getString());
                ms->send(msg, 0);
                //msg.reset();
                boost::this_thread::sleep_for(boost::chrono::milliseconds(dist(rng)));
                i++;
            }
            shared_ptr<DataManager> de = DataManager::getInstance();
            de->stop();
            de.reset();
            return;
        }

        void test_dataWriter1(){
            std::mt19937 rng(std::random_device{}()); // Mersenne Twister engine
            std::uniform_int_distribution<int> dist(0, 10); // [0, 10) range
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();


            //q.reset();
            int i = 0;
            while(i<100){
                auto q = make_shared<Quote>();
                strcpy(q->code_, "00507");
                strcpy(q->exg_ ,"Futu");
                strcpy(q->time_, "test");     
                q->timestamp_ = GetTimeStamp();
                q->cPrice_ = i;
                shared_ptr<Msg> msg = make_shared<Msg>("DataManager", "Tester", MSG_TYPE_STORE_QUOTE, q->getString());
                ms->send(msg, 0);
                //msg.reset();
                boost::this_thread::sleep_for(boost::chrono::milliseconds(dist(rng)));
                i++;
            }
            shared_ptr<DataManager> de = DataManager::getInstance();
            de->stop();
            de.reset();
            return;
        }

        void test_dataWriter2(){
            std::mt19937 rng(std::random_device{}()); // Mersenne Twister engine
            std::uniform_int_distribution<int> dist(0, 10); // [0, 10) range
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();


            //q.reset();
            int i = 0;
            while(i<100){
                auto q = make_shared<Quote>();
                strcpy(q->code_, "12333");
                strcpy(q->exg_ ,"Futu");
                strcpy(q->time_, "test");     
                q->timestamp_ = GetTimeStamp();
                q->cPrice_ = i;
                shared_ptr<Msg> msg = make_shared<Msg>("DataManager", "Tester", MSG_TYPE_STORE_QUOTE, q->getString());
                ms->send(msg, 0);
                //msg.reset();
                boost::this_thread::sleep_for(boost::chrono::milliseconds(dist(rng)));
                i++;
            }
            shared_ptr<DataManager> de = DataManager::getInstance();
            de->stop();
            de.reset();
            return;
        }

        void test_DataReader(){
            shared_ptr<DataManager> de = DataManager::getInstance();
            de->start();
            de.reset();
        }

        

        void run(){
            boost::thread thread1(bind(&Tester::test_dataWriter,this));
            boost::thread thread2(bind(&Tester::test_dataWriter1,this));
            boost::thread thread3(bind(&Tester::test_dataWriter2,this));
            boost::thread thread4(bind(&Tester::test_DataReader, this)); 
            thread1.join();
            thread2.join();
            thread3.join();
            thread4.join();
            
        }
    };



int main(){
    Tester test;
    boost::thread testthread(bind(&Tester::run,&test));
    testthread.join();
    sleep(6);    // MUST for proper destruction of boost::threadpool 
    spdlog::shutdown();
    return 0;
}

