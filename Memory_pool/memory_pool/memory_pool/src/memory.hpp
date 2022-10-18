#pragma once
// 版本1 
#include<stdlib.h>
struct NextOnFreeList;
typedef NextOnFreeList* FreeListNext;
//  连接空列表的相邻元素
struct NextOnFreeList {
    NextOnFreeList* next;
};

namespace MemoryPoolVer1{
class  Rational;
// 需要重复new的类
class Ratinal {
				public:
								Ratinal() = default;
								Ratinal(int i);
								~Ratinal() = default;
							 static void* operator new(size_t size);
								static void operator delete(void *doomed, size_t size);  //new 和 delete 操作符重载不能inline。只能static
								static void newMemPool();
								static void deleteMemPool();
								int getranValue() {
												return ran;
								};
				private:
								static FreeListNext freeList; // 作用1：指向空闲列表的下一个对象 作用2：将Rational对象强转为freeList对象
								static void expandTheFreeList(); // 内存池的关键函数
								enum  {
												EXPANSION_SIZE = 32
								};
								int  ran = 0;
};
}

//  版本2 模板类 ---
namespace MemoryPoolVer2{
				// 模板类控制内存池的申请,通过参数T控制内存池的大小。达到复用 --不能通过继承非方式写。
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
				// 通过Controller 
				class RatinalVer2 {
				public:
								RatinalVer2() =default;
								~RatinalVer2() =default;
								static void* operator new(size_t size) ;//{ return memorypoolController->alloc(size);}
								static void operator delete(void* demo, size_t size);//{ memorypoolController->free(demo);};
								static void newMemPool();//{ memorypoolController = new MemoryPool<RatinalVer2>();} // 为什么需要冷启动，不直接new ---
								//因为controller 是静态变量，不能在构造函数里面直接申请空间
								static void deleteMemPool();//{ delete memorypoolController;}  // 为什么static 的实现不能放在 h文件中  --
								// 因为在编译时main.cpp中， h文件会copy到main中去，但是因为include在最上面这就导致了，静态变量没有定义。
				private:
								static MemoryPool<RatinalVer2> *memorypoolController; // 需要在类的外部进行声明和定义 --为什么需要static。
								//因为new  和 delet必须是staitc函数，如果不是staitc不能new中不能访问非静态成员变量
				};
				// in all:
				// 类中含有静态成员变量 和静态成员函数时 ，静态成员变量的初始化同一放在cpp中（必须有）。静态成员函数的实现也放在cpp中。
}
