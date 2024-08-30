
#include<Helper/logger.h>
#include <Interface/IMessenger.h>
using namespace std;
using namespace ts;
#include "boost/thread/thread.hpp"
#include <boost/chrono.hpp>
#include <memory>
#include <FUTU/FutuEngine.h>
#include <rapidjson/document.h>
#include <DataManager/DataManager.h>
#include <DataManager/DataWriter.h>
#include <DataManager/DataReader.h>
#include <functional>
#include <random>
#include <Strategy/TradeUtil.h>
#include <Strategy/StrategyEngine.h>
#include <Strategy/TestStrategy.h>

    class Tester{
    public:
        void func_1(){
            // if(!MsgqTSMessenger::msgq_server_){
            //     MsgqTSMessenger::msgq_server_  = std::make_unique<MsgqNNG>(MSGQ_PROTOCOL::PUB, PROXY_SERVER_URL);
            // }
            boost::this_thread::sleep_for(boost::chrono::seconds(10));
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun1");
            std::shared_ptr<Msg> msg = std::make_shared<Msg>();
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("fun1");
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
            ms->send(msg, 0);
            code = "HSImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);
            code = "MHImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  



            code = "ALBmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  

            code = "METmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  


            code = "HTImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  

            code = "HHImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  

            code = "MCHmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  
            code = "MTWmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  

            code = "MNDmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  

            code = "JDCmain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  
            
            code = "BLImain";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  

            code = "800000";
            d["code"].SetString(code.data(), code.size(), d.GetAllocator());
            Json2String(d, msg->data_);
            ms->send(msg, 0);  

        }




        void func_2(){
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun2");
            ts::MsgqTSMessenger rec2 (PROXY_SERVER_URL);
            LOG->info("dialer2 created");

            while(true){ 
                std::shared_ptr<Msg> msg2 = rec2.recv(0+0); // nonblock + ALLOC
                if(msg2 && msg2->destination_=="Main"){
                    LOG->info(fmt::format("function2 received {}",msg2->serialize()).c_str());
                }
            }
        }




        void func_3(){
            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun3");
            ts::FutuEngine eng;
            eng.start();
            while(eng.estate_.load()==CONNECTED){}
        }


        void func_4(){

            std::shared_ptr<Logger> LOG = make_shared<Logger>("fun4");
            // ts::MsgqTSMessenger rec (PROXY_SERVER_URL);
            // LOG->info("dialer3 created");

            // while(true){ 
            //     std::shared_ptr<Msg> msg = rec.recv(0+0); // nonblock + ALLOC
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
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("datawriter");


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
            std::uniform_int_distribution<int> dist(0, 20); // [0, 10) range
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("dw1");


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
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("dw2");


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
            while(eng.estate_.load() == CONNECTED);
        }

        void test_counter(){
            boost::this_thread::sleep_for(boost::chrono::seconds(300));
            
            shared_ptr<DataManager> de = DataManager::getInstance();
            shared_ptr<StrategyEngine> eng = StrategyEngine::getInstance();
            eng->stop();
            de->stop();

            std::shared_ptr<Msg> msg = std::make_shared<Msg>();
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("counter");
            msg->msgtype_ = MSG_TYPE_STOP;
            msg->destination_ = "FutuEngine";
            msg->source_ = "Tester";
            ms->send(msg, 0);
            de.reset();
        }

        void test_reader(bool* indicator){
            boost::this_thread::sleep_for(boost::chrono::minutes(10));
            std::shared_ptr<Msg> msg = std::make_shared<Msg>();
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("testreader");
            msg->msgtype_ = MSG_TYPE_GET_QUOTE_BLOCK;
            msg->source_ = "Tester";
            msg->destination_ = "DataManager";
            ARG arg;
            while(indicator){
                msg->data_ = "FUTU^HSImain^5^"+to_string(GetTimeStamp())+"^TesterReader";
                ms->send(msg, 0);
                boost::this_thread::sleep_for(boost::chrono::milliseconds(300));
            }
        }

        void test_getData(bool* indicator){
            std::shared_ptr<Logger> LOG = make_shared<Logger>("GetData");
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("getData");
            std::shared_ptr<Msg> msg;
            std::shared_ptr<Msg> dataMsg = make_shared<Msg>();
            dataMsg->destination_ = "WebApp";
            uint64_t last = 0;
            dataMsg->source_ = "Tester";
            dataMsg->msgtype_ = MSG_TYPE_DEBUG;
            while(*indicator){
                msg = ms->recv(0);
                if(msg && strcmp(msg->destination_.c_str(),"TesterReader")==0){
                    QuoteSlice* ptr = reinterpret_cast<QuoteSlice*>(std::strtoull(msg->data_.c_str(), nullptr, 16));
                    for(int i=0; i<ptr->getCount(); i++){
                        LOG->warn(to_string(ptr->at(i)->updateTimestamp_).c_str());
                        if(ptr->at(i)->updateTimestamp_ >= last){
                            last = ptr->at(i)->updateTimestamp_;
                            dataMsg->data_ = ptr->at(i)->getJson();
                            ms->send(dataMsg, 0);
                        }
                    }
                    delete ptr;
                }
            }
        }


        void test_Loader(bool* indicator){
            sleep(10);
            std::shared_ptr<Logger> LOG = make_shared<Logger>("Loader");
            shared_ptr<MsgqTSMessenger> ms = MsgqTSMessenger::getInstance("Loadertester");
            StrategyCtx ld("HSImain", "FUTU", 5, SubType::QUOTE,500);
            ld.start();
            std::shared_ptr<Msg> dataMsg = make_shared<Msg>();
            dataMsg->destination_ = "WebApp";
            dataMsg->source_ = "Tester";
            dataMsg->msgtype_ = MSG_TYPE_DEBUG;
            while(*indicator){
                if(ld.getCur()){
                    const ts::Quote* temp = static_cast<const ts::Quote*>(ld.getCur());
                    if(temp){
                        dataMsg->data_ = temp->getJson();
                        ms->send(dataMsg, 0);
                        //LOG->info(temp->getJson().c_str());   
                    }
                }
            }
            ld.stop();
        }

        void test_strategy(){
            shared_ptr<StrategyEngine> eng = StrategyEngine::getInstance();
            rapidjson::Document d;
            
            const char* arg =R"(
            {
                "Name" : "TestStrategy",
                "TargetCode":["HSImain"],
                "Exchange":"FUTU",
                "Type":3,
                "Position":
                    {
                       "HSImain":[0.0, 0.0]
                    }
                ,
                "Size":5
            })";

            d.Parse(arg);
            if(IStrategy::checkValidParam(d)){
                ts::TestStrategy* tp = new TestStrategy(d);
                eng->addStrategy(tp);
                eng->start();
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
            bool fg = true;
            
            boost::thread thread_run_FUTU(bind(&Tester::test_futu, this));
            //boost::thread thread_get_from_Futu(bind(&Tester::func_1, this));
            boost::thread thread_DataManager(bind(&Tester::test_DataManager, this));
            boost::thread thread_test_counter(bind(&Tester::test_counter, this));
            //boost::thread thread_Loader(bind(&Tester::test_Loader,this, placeholders::_1), &fg);
            //boost::thread thread_reader(bind(&Tester::test_reader,this, placeholders::_1), &fg);
            //boost::thread thread_getdata(bind(&Tester::test_getData,this, placeholders::_1), &fg);
            //thread_get_from_Futu.join();

            //thread_run_FUTU.join();
            
            boost::thread thread_test_Strategy(bind(&Tester::test_strategy, this));
            thread_test_counter.join();
            fg = false;
            sleep(5);
        }
    };



int main(){
    Tester test;
    boost::thread testthread(bind(&Tester::run,&test));
    testthread.join();
    sleep(20);    // MUST for proper destruction of boost::threadpool 
    spdlog::shutdown();
    return 0;
}

