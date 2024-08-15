#ifndef SRC_STRATEGY_TRADEUTIL_H
#define SRC_STARTEGY_TRADEUTIL_H

#include "datastructure.h"

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
    class Loader{
        private:
            BaseData* data_; 
            int size_;
            string code_;
            string exg_;
            string name_;
            static atomic<int> loadercount_{0};
        public:
            Loader(const char* code, const char* exg, int size){
                
            }

    }
}







#endif