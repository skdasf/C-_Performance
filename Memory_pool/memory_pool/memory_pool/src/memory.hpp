#pragma once
// �汾1 
#include<stdlib.h>
struct NextOnFreeList;
typedef NextOnFreeList* FreeListNext;
//  ���ӿ��б������Ԫ��
struct NextOnFreeList {
    NextOnFreeList* next;
};

namespace MemoryPoolVer1{
class  Rational;
// ��Ҫ�ظ�new����
class Ratinal {
				public:
								Ratinal() = default;
								Ratinal(int i);
								~Ratinal() = default;
							 static void* operator new(size_t size);
								static void operator delete(void *doomed, size_t size);
								static void newMemPool();
								static void deleteMemPool();
								int getranValue() {
												return ran;
								};
				private:
								static FreeListNext freeList;
								static void expandTheFreeList();
								enum  {
												EXPANSION_SIZE = 32
								};
								int  ran = 0;
};
}

//  �汾2 ģ���� ---
namespace MemoryPoolVer2{
				template<typename T>
				class MemoryPool {
				public:
								MemoryPool(size_t size = EXPANSION_SIZE);
								~MemoryPool();
								inline void* alloc(size_t size);
								inline void free (void *someElement);
				private:
								MemoryPool<T> *nextPtr_;
								enum 
								{
								EXPANSION_SIZE = 32
								};
								void expanTheFreeList(int howMany = EXPANSION_SIZE);
				};
				// ͨ��Controller 
				class RatinalVer2 {
				public:
								RatinalVer2() =default;
								~RatinalVer2() =default;
								static void* operator new(size_t size) ;
								static void operator delete(void* demo, size_t size);
								static void newMemPool();
								static void deleteMemPool();
				private:
								static MemoryPool<RatinalVer2> *memorypoolController; 
				};
}
