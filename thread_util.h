#ifndef THREAD_UTIL_H
#define THREAD_UTIL_H

#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <atomic>

class JoinThreads{
public:
    JoinThreads(std::vector<std::thread>& threads);
    ~JoinThreads();
private:
    std::vector<std::thread>& threads_;
};

template<typename T>
class ThreadsafeQueue{
public:
    ThreadsafeQueue(){}
    void Push(T new_value){
        std::lock_guard<std::mutex>lock(mutex_);
        queue_.push(new_value);
        condvar_.notify_one();
    };
    bool TryPop(T& value){
        std::lock_guard<std::mutex>lock(mutex_);
        if(queue_.empty()){
            return false;
        }
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

private:
    mutable std::mutex mutex_;
    std::queue<T> queue_;
    std::condition_variable condvar_;
};

template<typename T>
class ThreadsafePriorityQueue{
public:
    ThreadsafePriorityQueue(){}
    void Push(T new_value){
        std::lock_guard<std::mutex>lock(mutex_);
        queue_.push(new_value);
        condvar_.notify_one();
    };

    bool Top(T& value){
        std::lock_guard<std::mutex>lock(mutex_);
        if(queue_.empty()){
            return false;
        }
        value = queue_.top();
        return true;
    };

    void Pop(){
        std::lock_guard<std::mutex>lock(mutex_);
        queue_.pop();
    };

private:
    mutable std::mutex mutex_;
    std::priority_queue<T, std::vector<T>, std::greater<T>> queue_;
    std::condition_variable condvar_;
};

class ThreadPool{
public:
    ThreadPool(int num_threads);
    ~ThreadPool();
    void Submit(std::function<void()> func);
    void WorkerThread();
private:
    std::atomic<bool> done_;
    ThreadsafeQueue<std::function<void()>>work_queue_;
    std::vector<std::thread> threads_;
    JoinThreads joiner_;
};

#endif // THREAD_UTIL_H

