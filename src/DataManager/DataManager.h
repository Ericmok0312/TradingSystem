#ifndef SRC_DATAMANAGER_DATAMANAGER_H
#define SRC_DATAMANAGER_DATAMANAGER_H


#include <Helper/ThreadPool.h>
#include <Helper/logger.h>
#include <Helper/util.h>
#include <Interface/IMessenger.h>
#include <Interface/IEngine.h>
#include <Interface/datastructure.h>
#include <DataManager/DataWriter.h>
#include <DataManager/DataReader.h>
#include <functional>
namespace ts{

    //Need to implement caches for reading data

    class DataManager: public IEngine, public ThreadPool<std::function<void(shared_ptr<Msg>)>, std::shared_ptr<Msg>>{
        private:
            CallBackTabletype RegTable_;
            mutex RegTableMutex_;
        public:
            DataManager();
            ~DataManager();

            void init() override;
            void start() override;
            void stop() override;
            void running() override;


            void processMsg(std::shared_ptr<Msg>);
            static std::shared_ptr<DataManager> getInstance();
            void sendData(string&& address, string&& des);

            void AddDataReaderTask(std::function<void(std::shared_ptr<ARG>)> callback, std::shared_ptr<ARG> arg);
            
            std::shared_ptr<DataWriter> datawritter_;
            static std::shared_ptr<DataManager> instance_;
            std::shared_ptr<DataReader> datareader_;
            static std::unique_ptr<ts::Logger> logger_;

        protected:
            static std::unique_ptr<ts::IMessenger> messenger_;
            static std::mutex getIns_mutex;

    };



}



#endif