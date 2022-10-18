
#include "memory.hpp"
namespace MemoryPoolVer1 {

    Ratinal::Ratinal(int i):ran(i) {
            
    }

    void* Ratinal::operator new(size_t size)
    {
        if (freeList == nullptr) {
            Ratinal::expandTheFreeList(); // 如果列表为空 则扩展列表
        }
        FreeListNext head = freeList;
        freeList = head->next;
        return head; // 将链表node转成实例对象。 --- FreeListNext 转成 Rational对象---这里就是为什么Node结点必须最大
    }

     void Ratinal::operator delete(void* doomed, size_t size)
    {
        FreeListNext head = (NextOnFreeList*)(doomed); 
        head->next = freeList;  // ***指针放在左边，看做地址。指针变量放在有变看做变量***
        freeList = head;  // 将Rational 转成 FreeListNext
    }

    void Ratinal::newMemPool()
    {
        Ratinal::expandTheFreeList();
    }

    void Ratinal::deleteMemPool() {
        FreeListNext nextPtr = nullptr;
        for (nextPtr = freeList ; nextPtr!=nullptr; ) {
            auto nextP = nextPtr->next;
            freeList = freeList->next;
            delete nextPtr;
            nextPtr = nextP;
        }

     /*  if (freeList == nullptr) {
            return;
       }
       auto ptr = freeList;
       while (ptr) {
            auto nextPtr = ptr->next;
            free(ptr);
            ptr = nextPtr;
       }*/

    }
    void  Ratinal::expandTheFreeList()
   {
         auto size = (sizeof(Ratinal)) > (sizeof(FreeListNext)) ? sizeof(Ratinal): sizeof(NextOnFreeList);
         auto head = (void *)new char[size]; // 申请一个不仅比 链表node和类 大的内存。 
         FreeListNext runer = static_cast<FreeListNext> (head); // 将该内存强转为链表node
         freeList = runer;
         for (int i = 0; i < EXPANSION_SIZE ; i++) {
            auto meomery_block = (void*) new char[size];
            runer->next = static_cast<FreeListNext> (meomery_block);
            runer = runer->next; //尾插法生成 内存链表
         }
         runer->next = nullptr;
   }

}


namespace MemoryPoolVer2{
    template<typename T>
    MemoryPool<T>::MemoryPool(size_t size /*= EXPANSION_SIZE*/) 
    {
        expanTheFreeList(size);
    }

    template<typename T>
    MemoryPool<T>::~MemoryPool() 
    {
        MemoryPool<T>* nextPtr = nextPtr_;
        while (nextPtr != nullptr) {
            auto nextP = nextPtr->nextPtr_;//为什么能访问到 -- 该方法在类的内部实现，肯定能通过该类的指针访问到
            free(nextPtr);
            nextPtr = nextP;
        }
    }
    template<typename T>
    void MemoryPool<T>::expanTheFreeList(int howMany /*= EXPANSION_SIZE*/)
    {
        auto size = (sizeof(T) > sizeof(MemoryPool<T> *)) ? sizeof(T) : sizeof(MemoryPool<T> *);
        auto head = (void*)new char[size];
        auto runer = static_cast<MemoryPool<T>*>(head);
        nextPtr_ = runer;
        for (auto i = 0u ; i < howMany ; i++) {
            auto head = (void*)new char[size];
            runer->nextPtr_ = (MemoryPool<T>*)head;
            runer = (MemoryPool<T>*)head;
        }
        runer->nextPtr_ = nullptr;
    }

    template<typename T>
    void* MemoryPool<T>::alloc(size_t size) 
    {
        if (!nextPtr_) {
            expanTheFreeList();
        }
        MemoryPool<T> *Head = nextPtr_;
        nextPtr_ = Head->nextPtr_;
        return Head;
    }

    template<typename T>
    void MemoryPool<T>::free(void* someElement)
    {
        MemoryPool<T> *Head = (MemoryPool<T> *)(someElement);
        Head->nextPtr_ = nextPtr_;
        nextPtr_ = Head;
    }



     void* RatinalVer2::operator new(size_t size) {
        return memorypoolController->alloc(size);
    }

    void RatinalVer2::operator delete(void* demo, size_t size) {
        memorypoolController->free(demo);
    }

    void RatinalVer2::newMemPool() {
        memorypoolController = new MemoryPool<RatinalVer2>();
    }

    void RatinalVer2::deleteMemPool() {
        delete memorypoolController;
    }

}
