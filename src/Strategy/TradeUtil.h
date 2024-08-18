#ifndef SRC_STRATEGY_TRADEUTIL_H
#define SRC_STARTEGY_TRADEUTIL_H

#include "Interface/datastructure.h"
#include "Interface/IMessenger.h"
#include "atomic"
#include "mutex"

namespace ts{


    /*
    Loader class, encapsulate loading of data from DataReader
    Each startegy will generate loader for all data requried
    loader will assist strategy to retrieve required data

    Planned to support the following functions
    1. keeping track of historic data in form of quoteslice
    2. keeping track of current price or other data
    3. 

    */
    template<typename T>
    class Loader{
        private:
            T* data_; 
            int size_;
            string code_;
            string exg_;
            string name_;
            static std::atomic<int> loadercount_;
            shared_ptr<MsgqTSMessenger> messenger_;
            double lprice_;
            int frequency_;
            LoaderType type_;
            void regRequest();
            void recvProcess();
            std::mutex mutexData_;
            bool* state_;
            void run();

        public:
            Loader(const char* code, const char* exg, int size, LoaderType type, bool* state, int freq = 100);
            ~Loader();
            
            const BaseData* getCur();

            T* getSlice();


    };
}


#endif