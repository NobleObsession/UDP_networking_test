#include "thread_util.h"

thread_local int local_thread_number = 0;

JoinThreads::JoinThreads(std::vector<std::thread>& threads):
    threads_(threads){}

JoinThreads::~JoinThreads(){
    for(size_t i=0; i<threads_.size(); ++i){
        if(threads_[i].joinable()){
           threads_[i].join();
        }
    }
};

ThreadPool::ThreadPool(int num_threads):done_(false), joiner_(threads_){
        for(int i = 0; i < num_threads; ++i){
            threads_.push_back(std::thread([this, i](){
                local_thread_number = i;
                WorkerThread();}));
        }
    };

ThreadPool::~ThreadPool(){
        done_ = false;
    };

void ThreadPool::Submit(std::function<void()> func){
        work_queue_.Push(func);
    };

void ThreadPool::WorkerThread(){
        while(!done_){
           std::function<void()> task;
           if(work_queue_.TryPop(task)){
               task();
           }else{
              std::this_thread::yield();
           }
        }
};
