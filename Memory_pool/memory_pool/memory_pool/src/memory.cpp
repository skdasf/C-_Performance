
#include "memory.hpp"
namespace MemoryPoolVer1 {

    Ratinal::Ratinal(int i):ran(i) {
            
    }

    void* Ratinal::operator new(size_t size)
    {
        if (freeList == nullptr) {
            Ratinal::expandTheFreeList();
        }
        FreeListNext head = freeList;
        freeList = head->next;
        return head;
    }

     void Ratinal::operator delete(void* doomed, size_t size)
    {
        FreeListNext head = (NextOnFreeList*)(doomed); 
        head->next = freeList;
        freeList = head;
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
         auto head = (void *)new char[size];
         FreeListNext runer = static_cast<FreeListNext> (head);
         freeList = runer;
         for (int i = 0; i < EXPANSION_SIZE ; i++) {
            auto meomery_block = (void*) new char[size];
            runer->next = static_cast<FreeListNext> (meomery_block);
            runer = runer->next;
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
            auto nextP = nextPtr->nextPtr_;
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
