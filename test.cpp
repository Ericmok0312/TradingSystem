#include<Helper/logger.h>
using namespace std;
using namespace ts;
int main(){

    std::shared_ptr<spdlog::logger> LOG = Logger::getInstance();

    LOG->info("this is test");

    return 0;
}