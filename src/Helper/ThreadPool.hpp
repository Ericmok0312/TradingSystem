
#ifndef SRC_HELPER_THREADPOOL_HPP
#define SRC_HELPER_THREADPOOL_HPP
#include <Helper/ThreadPool.h>

namespace ts
{
    



    /// @brief Constructor of ThreadPool, initialize variables and call ThreadPool_Init
    /// @param initNum, better set to be 0, otherwise will lead to problem in destruction 
    /// @param maxNum 
    /// @param idleSec 
    template<typename TaskType, typename InputType>
    ThreadPool<TaskType, InputType>::ThreadPool(int initNum, int maxNum, int idleSec):
    initNum_(initNum),
    maxNum_(maxNum),
    idleSec_(idleSec),
    stop_(false),
    busycount_(0),
    threadcount_(0)
    {
        ThreadPool_Init();
    }


    /// @brief Initiialization of ThreadPool
    template<typename TaskType, typename InputType>
    void ThreadPool<TaskType, InputType>::ThreadPool_Init(){
        if (idleSec_ <= 0){
            idleSec_ = ThreadPool::IDLESEC; // adjusting idleSec_ into valid range
        } 
        threadpool_.reserve(maxNum_); // Setting vector container size to maxNum

        for(int i = 0; i < maxNum_; ++i){
            if(i< initNum_)
                threadpool_.push_back(new std::thread(&ThreadPool::ThreadRoutine, this, i)); //Creating threads
            else
                threadpool_.push_back(nullptr);
        }

        threadcount_.store(initNum_); // store initNum_

    }
    template<typename TaskType, typename InputType>
    ThreadPool<TaskType,InputType>::~ThreadPool(){
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
        cond_.notify_all(); // all waiting thread are unblocked
        for(int i=0; i<maxNum_; i++){
            thread* thread = threadpool_[i];
            if (thread && thread->joinable()){ //check if thread is valid
                thread->join(); // make sure the thread is finished
                delete thread;
            }
        }


    }
    
    template<typename TaskType, typename InputType>
    void ThreadPool<TaskType,InputType>::AddTask(TaskType task, InputType data){
        std::lock_guard<std::mutex> lock(mutex_);
        taskqueue_.emplace(task, data);

        cond_.notify_all();
        PoolGrow();
    }

    template<typename TaskType, typename InputType>
    void ThreadPool<TaskType,InputType>::PoolGrow(){
        int tc = threadcount_.load();
        if(tc == busycount_.load() && tc< maxNum_){ // all threads are occupied
            for(int i=0; i<maxNum_; i++){
                if(threadpool_[i] == nullptr){ // find a slot with nullptr
                    threadpool_[i] = new std::thread(&ThreadPool::ThreadRoutine, this, i);
                    threadcount_++;
                    break;
                }
            }
        }
    }

    template<typename TaskType, typename InputType>
    void ThreadPool<TaskType,InputType>::ThreadRoutine(int index){
        while(true){
            std::pair<TaskType, InputType> task (nullptr, nullptr); //create a null container for task
            std::cv_status waitStatus = std::cv_status::no_timeout;
            std::unique_lock<std::mutex> lock (mutex_);
            while(taskqueue_.empty() && waitStatus != std::cv_status::timeout && !stop_){
                waitStatus = cond_.wait_for(lock, std::chrono::seconds(idleSec_));
            }


            if(!taskqueue_.empty()){
                task = taskqueue_.front(); //Getting tasks
                taskqueue_.pop();
            }
            else if(stop_){
                break;
            }
            else if(waitStatus == std::cv_status::timeout){
                if(threadcount_ > initNum_){
                    threadpool_[index]->detach(); // make thread detach from routine
                    delete threadpool_[index]; //delete the thread
                    threadpool_[index] = nullptr;
                    --threadcount_;
                    break;
                }
            }

            if(task.first != nullptr){
                ++busycount_;
                task.first(task.second); // run the task
                --busycount_;
            }
        }
    }

} // namespace ts




#endif



