#ifndef SRC_DATAMANAGER_DATAMANAGER_H
#define SRC_DATAMANAGER_DATAMANAGER_H


#include <Helper/ThreadPool.h>
#include <Helper/logger.h>
#include <Helper/util.h>
#include <Interface/IMessenger.h>
#include <Interface/IEngine.h>
#include <Interface/datastructure.h>


namespace ts{



    class DataManager: public ThreadPool{
        public:
            DataManager();
            ~DataManager();

            void init();
            void start();
            static void processMsg(std::shared_ptr<Msg>);

        protected:
            static std::shared_ptr<ts::Logger> logger_;
            static std::unique_ptr<ts::IMessenger> messenger_;
            std::atomic<Estate> estate_; 

    };

}



#endif