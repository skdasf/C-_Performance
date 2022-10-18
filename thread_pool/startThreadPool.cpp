#include "threadPool.hpp"


class Task_t{

public:
 void process(){
    cout<< "run .."<<endl; 
 }
};


int main(){
  ThreadPool<Task_t> pool(6);
   shared_ptr<Task_t>  tt;
  while (true) {
   // auto task = make_shared<Task_t>();
    //pool.appendTask(task);
    tt = make_shared<Task_t>();
    pool.appendTask(tt);
  }

   return 0;
}