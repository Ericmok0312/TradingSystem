
#include<Helper/logger.h>
#include <Interface/IMessenger.h>
using namespace std;
using namespace ts;
#include <thread>
#include <memory>
#include <FUTU/FutuEngine.h>
#include <json/json.h>
#include <DataManager/DataManager.h>
#include <DataManager/DataWriter.h>
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

        static void test_dataWriter(){
            shared_ptr<DataManager> de = DataManager::getInstance();
            auto q = make_shared<Quote>();
            
            strcpy(q->code_, "02222");
            strcpy(q->exg_ ,"Futu");
            strcpy(q->time_, "2021-06-09 11:05:41");
            
            shared_ptr<BaseData> nq = dynamic_pointer_cast<BaseData>(q);
            //q.reset();

            de->datawritter_->WriteQuote(nq);
            de->datawritter_->logger_->info("Wrote data into lmdb");
            strcpy(q->time_, "2021-06-09 11:05:42");
            nq = dynamic_pointer_cast<BaseData>(q);
            de->datawritter_->WriteQuote(nq);
            de->datawritter_->logger_->info("Wrote data into lmdb");
            strcpy(q->time_, "2021-06-09 11:05:43");
            nq = dynamic_pointer_cast<BaseData>(q);
            de->datawritter_->WriteQuote(nq);
            strcpy(q->code_, "1222");
            strcpy(q->time_, "2021-06-09 11:05:43");
            nq = dynamic_pointer_cast<BaseData>(q);
            //de->datawritter_->WriteQuote(nq);
            de->datawritter_->logger_->info("Stored to csv");
            return;
        }


        static void run(){
            thread nthread(test_dataWriter);
            nthread.join();
        }
    };



int main(){
    Tester test;
    thread testthread(test.run);
    testthread.join();
    spdlog::shutdown();
    return 0;
}