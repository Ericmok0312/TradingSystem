#ifndef SRC_HELPER_THREADPOOL_H
#define SRC_HELPER_THREADPOOL_H

#include <queue>
#include <memory>
#include <thread>
#include <functional>
#include <mutex>
#include <atomic>
#include <json/json.h>
#include <condition_variable>
#include <Interface/datastructure.h>

using namespace std;


namespace ts{

    class ThreadPool{
        public:
            using TaskType = void(*)(std::shared_ptr<Msg>);

            static const int INITNUM;
            static const int MAXNUM;
            static const int IDLESEC;


            ThreadPool(int initNum = 1, int maxNum = 6, int idleSec = 6);
            ~ThreadPool();

            queue<std::pair<TaskType, std::shared_ptr<Msg>>> taskqueue_;
            vector<thread*> threadpool_;

            std::mutex mutex_;
            std::atomic<int> busycount_;
            std::atomic<int> threadcount_;
            std::condition_variable cond_;
            int initNum_;
            int maxNum_;
            int idleSec_;
            bool stop_;


            void AddTask(TaskType task, std::shared_ptr<Msg> msg);

        public:
            void ThreadPool_Init();    
            void ThreadRoutine(int index);
            void PoolGrow();
            
    };
}



#endif