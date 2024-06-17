#include<Helper/logger.h>
using namespace std;
using namespace ts;
#include <thread>

void func_1(){
    std::shared_ptr<spdlog::logger> LOG = Logger::getInstance();

    while(true){
        LOG->info("this is test 1");
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void func_2(){
    std::shared_ptr<spdlog::logger> LOG = Logger::getInstance();

    while(true){
        LOG->info("this is test 2");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


int main(){

    std::thread t1(func_1);
    std::thread t2(func_2);

    t1.join();
    t2.join();

    return 0;
}