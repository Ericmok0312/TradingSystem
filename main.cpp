
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
            // if(!MsgqTSMessenger::msgq_server_){
            //     MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
            // }
            sleep(10);
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun1");
            std::shared_ptr<Msg> msg = std::make_shared<Msg>();
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();
            LOG->info("Futu Called");

            string code = "TCHmain";
            int sub = 3;

            msg->destination_ = "FutuEngine";
            msg->source_ = "Main";
            msg->msgtype_ = MSG_TYPE_REGCALLBACK;
            rapidjson::Document d;
            d.SetObject();
            d.AddMember("code", rapidjson::Value(code.data(), code.size(), d.GetAllocator()), d.GetAllocator());
            d.AddMember("subtype", rapidjson::Value(sub), d.GetAllocator());

            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);
            code = "HSImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);
            code = "MHImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  



            code = "ALBmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  

            code = "METmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  


            code = "HTImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  

            code = "HHImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  

            code = "MCHmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  
            code = "MTWmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  

            code = "MNDmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  

            code = "JDCmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  
            
            code = "BLImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, NNG_FLAG_ALLOC);  



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
            while(i<1000){
                auto q = make_shared<Quote>();
                strcpy(q->code_, "02222");
                strcpy(q->exg_ ,"Futu");
                strcpy(q->time_, "test");     
                q->timestamp_ = GetTimeStamp();
                q->cPrice_ = i;
                shared_ptr<Msg> msg = make_shared<Msg>("DataManager", "Tester", MSG_TYPE_STORE_QUOTE, q->getString());
                ms->send(msg, NNG_FLAG_ALLOC);
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
            std::uniform_int_distribution<int> dist(0, 20); // [0, 10) range
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();


            //q.reset();
            int i = 0;
            while(i<1000){
                auto q = make_shared<Quote>();
                strcpy(q->code_, "00507");
                strcpy(q->exg_ ,"Futu");
                strcpy(q->time_, "test");     
                q->timestamp_ = GetTimeStamp();
                q->cPrice_ = i;
                shared_ptr<Msg> msg = make_shared<Msg>("DataManager", "Tester", MSG_TYPE_STORE_QUOTE, q->getString());
                ms->send(msg, NNG_FLAG_ALLOC);
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
            while(i<1000){
                auto q = make_shared<Quote>();
                strcpy(q->code_, "12333");
                strcpy(q->exg_ ,"Futu");
                strcpy(q->time_, "test");     
                q->timestamp_ = GetTimeStamp();
                q->cPrice_ = i;
                shared_ptr<Msg> msg = make_shared<Msg>("DataManager", "Tester", MSG_TYPE_STORE_QUOTE, q->getString());
                ms->send(msg, NNG_FLAG_ALLOC);
                //msg.reset();
                boost::this_thread::sleep_for(boost::chrono::milliseconds(dist(rng)));
                i++;
            }
            shared_ptr<DataManager> de = DataManager::getInstance();
            de->stop();
            de.reset();
            return;
        }

        void test_DataManager(){
            shared_ptr<DataManager> de = DataManager::getInstance();
            de->start();
            de.reset();
            de = nullptr;
        }

        void test_futu(){
            //boost::this_thread::sleep_for(boost::chrono::minutes(5));
            FutuEngine eng;
            eng.start();
        }

        void test_counter(){
            boost::this_thread::sleep_for(boost::chrono::minutes(10));
            
            shared_ptr<DataManager> de = DataManager::getInstance();

            de->stop();

            std::shared_ptr<Msg> msg = std::make_shared<Msg>();
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();
            msg->msgtype_ = MSG_TYPE_STOP;
            msg->destination_ = "FutuEngine";
            msg->source_ = "Tester";
            ms->send(msg, NNG_FLAG_ALLOC);
            de.reset();
        }

        void test_reader(bool* indicator){
            std::shared_ptr<Msg> msg = std::make_shared<Msg>();
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();
            msg->msgtype_ = MSG_TYPE_GET_QUOTE_BLOCK;
            msg->source_ = "Tester";
            msg->destination_ = "DataManager";
            ARG arg;
            msg->data_ = "FUTU^HSImain^100^"+to_string(GetTimeStamp())+"^TesterReader";
            while(indicator){
                msg->timestamp_ = GetTimeStamp();
                ms->send(msg, NNG_FLAG_ALLOC);
                boost::this_thread::sleep_for(boost::chrono::seconds(1));
            }
        }

        void test_getData(bool* indicator){
            std::shared_ptr<Logger> LOG = make_shared<Logger>("GetData");
            LOG->info("Calling getData");
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance();
            std::shared_ptr<Msg> msg;
            std::shared_ptr<Msg> dataMsg = make_shared<Msg>();
            dataMsg->destination_ = "WebApp";
            dataMsg->source_ = "Tester";
            dataMsg->msgtype_ = MSG_TYPE_DEBUG;
            while(indicator){
                msg = ms->recv(NNG_FLAG_ALLOC);
                if(msg && strcmp(msg->destination_.c_str(),"TesterReader")==0){
                    QuoteSlice* ptr = reinterpret_cast<QuoteSlice*>(std::strtoull(msg->data_.c_str(), nullptr, 16));
                    for(int i=0; i<ptr->getCount(); i++){
                        dataMsg->data_ = ptr->at(i)->getJson();
                        LOG->info(dataMsg->data_.c_str());
                        ms->send(dataMsg, NNG_FLAG_ALLOC);
                    }
                    delete ptr;
                }
            }
        }
        

        void run(){
            
            // boost::thread thread1(bind(&Tester::test_dataWriter,this));
            // boost::thread thread2(bind(&Tester::test_dataWriter1,this));
            // boost::thread thread3(bind(&Tester::test_dataWriter2,this));
            // boost::thread thread4(bind(&Tester::test_DataReader, this)); 
            // thread1.join();
            // thread2.join();
            // thread3.join();
            // thread4.join();
            boost::thread thread_run_FUTU(bind(&Tester::test_futu, this));
            boost::thread thread_get_from_Futu(bind(&Tester::func_1, this));
            boost::thread thread_DataManager(bind(&Tester::test_DataManager, this));
            boost::thread thread_test_counter(bind(&Tester::test_counter, this));
            bool fg = true;
            boost::thread thread_reader(bind(&Tester::test_reader,this, placeholders::_1), &fg);
            boost::thread thread_getdata(bind(&Tester::test_getData,this, placeholders::_1), &fg);
            //thread_get_from_Futu.join();

            //thread_run_FUTU.join();
   
            thread_test_counter.join();
            fg = false;
 
            
        }
    };



int main(){
    Tester test;
    boost::thread testthread(bind(&Tester::run,&test));
    testthread.join();
    sleep(10);    // MUST for proper destruction of boost::threadpool 
    spdlog::shutdown();
    return 0;
}

