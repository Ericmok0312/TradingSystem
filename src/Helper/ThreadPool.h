#ifndef SRC_HELPER_THREADPOOL_H
#define SRC_HELPER_THREADPOOL_H

#include <queue>
#include <memory>
#include <thread>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <Interface/datastructure.h>
#include "boost/thread/thread.hpp"

using namespace std;


namespace ts{
    template<class TaskType, class InputType>
    class ThreadPool{
        public:

            static const int INITNUM {1};
            static const int MAXNUM {6};
            static const int IDLESEC {6};


            ThreadPool(int initNum = 1, int maxNum = 6, int idleSec = 6);
            ~ThreadPool();

            queue<std::pair<TaskType, InputType>> taskqueue_;
            vector<boost::thread*> threadpool_;

            std::mutex mutex_;
            std::atomic<int> busycount_;
            std::atomic<int> threadcount_;
            std::condition_variable cond_;
            int initNum_;
            int maxNum_;
            int idleSec_;
            bool stop_;


            void AddTask(TaskType task, InputType msg);

        public:
            void ThreadPool_Init();    
            void ThreadRoutine(int index);
            void PoolGrow();
            
    };


}



#endif