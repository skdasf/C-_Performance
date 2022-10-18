#include <iostream>
#include "memory.hpp"
using namespace MemoryPoolVer1;
FreeListNext Ratinal::freeList = nullptr;
MemoryPoolVer2::MemoryPool<MemoryPoolVer2::RatinalVer2>* MemoryPoolVer2::RatinalVer2::memorypoolController = nullptr;  // 为什 需要全局声明类的static才能使用 -- 在类中访问静态成员变量需要在类的外部进行初始化
int main () {
  
    Ratinal *arry[1000];
    Ratinal::newMemPool();
    for (int i = 0 ; i<1000; i++) {
        arry[i] =new Ratinal(i);
    }


    for (int i = 0; i < 1000; i++) {
       auto test = arry[i];
       std::cout<<"\n "<<test->getranValue();
    }
    for (int i = 0; i < 1000; i++) {
        delete arry[i];
    }
    Ratinal::deleteMemPool();

    const int SIZE = 1000;
    MemoryPoolVer2::RatinalVer2::newMemPool();
    MemoryPoolVer2::RatinalVer2 *arry2[1000];
    for (auto i = 0 ; i< SIZE ; i++) {
        arry2[i] = new MemoryPoolVer2::RatinalVer2;
    }

    for (auto i = 0; i<SIZE ; i++) {
        delete arry2[i];
    }
    MemoryPoolVer2::RatinalVer2::deleteMemPool();
    std::cout<<"hello ";
    return 0;
}