#include "Interface/IMessenger.h"
#include "Helper/logger.h"
#include <string>
using namespace std;

namespace ts{
    
    
    // start of IMessenger

    /*
    - getting logger_ using Logger::getInstance();
    */
    IMessenger::IMessenger(){
        logger_ = Logger::getInstance();
    }

    IMessenger::~IMessenger(){}; // default destructor


    // End of IMessenger


    // Start of IMsgq


    /*
    -set up url and protocol with parameters
    -set up logger using getInstance();
    */
    IMsgq::IMsgq(MSGQ_PROTOCOL protocol, string url){

        protocol_ = protocol;
        url_ = url;
        logger_ = Logger::getInstance();

    }


    IMsgq::~IMsgq(){};    //default destructor


    // End of IMsgq












}