#include <iostream>
#include "memory.hpp"
using namespace MemoryPoolVer1;
FreeListNext Ratinal::freeList = nullptr;
MemoryPoolVer2::MemoryPool<MemoryPoolVer2::RatinalVer2>* MemoryPoolVer2::RatinalVer2::memorypoolController = nullptr;
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