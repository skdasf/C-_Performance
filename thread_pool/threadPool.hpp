#pragma once
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <queue>
#include <memory>
using namespace std;

const int MAX_THRADNUM = 1000;

template<typename T>
class ThreadPool {
    typedef condition_variable ContinueThead;
    typedef mutex  Mutex;
    typedef queue<shared_ptr<T>> Container;
    typedef unique_lock<Mutex> AutoLock;
public:
    explicit ThreadPool(int num);
    ThreadPool(const ThreadPool&)= delete;
    void appendTask(shared_ptr<T> task);
    ~ThreadPool();

private:
    static void worker(void *arg);
    void  run();
private:
    int currentThreadNum;
    vector<thread> thread_container;
    Container taskQueue;
    ContinueThead continue_thread;
    Mutex mutex_;
    bool stop;
};

template<typename T>
void ThreadPool<T>::run() {
    while (!stop) {
        shared_ptr<T> re;
        {
            AutoLock lc(mutex_);
            continue_thread.wait(lc, [this]() {return !this->taskQueue.empty(); });
            if (this->taskQueue.empty()) {
                return;
            }
            re = this->taskQueue.front();
            this->taskQueue.pop();
           // cout << "task size" << this->taskQueue.size() << endl;
            if (re != nullptr) {
                re->process();
            }
        }
    }
}

template<typename T>
void ThreadPool<T>::worker(void* arg) {
    ThreadPool *pool = (ThreadPool*)arg;
    pool->run();
}

template<typename T>
void ThreadPool<T>::appendTask(shared_ptr<T> task) {
   { AutoLock lc(mutex_);
    taskQueue.push(task);}
    continue_thread.notify_one();
   // cout<<"task size" << taskQueue.size()<<endl;
}

template<typename T>
ThreadPool<T>::~ThreadPool() {
    stop = true;
    continue_thread.notify_all();
    for (auto &iter:thread_container){
        if (iter.joinable()) {
            iter.join();
        }
    }

}

template<typename T>
ThreadPool<T>::ThreadPool(int num):currentThreadNum(num),stop(false) 
{
    if (currentThreadNum >= MAX_THRADNUM || currentThreadNum <= 0) {
            throw exception();
    }
    for (auto i = 0; i<currentThreadNum; ++i ){
       thread_container.emplace_back(ThreadPool::worker,this);
    }
};



