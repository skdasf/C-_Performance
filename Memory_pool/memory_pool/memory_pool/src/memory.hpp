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
								static void operator delete(void *doomed, size_t size);  //new �� delete ���������ز���inline��ֻ��static
								static void newMemPool();
								static void deleteMemPool();
								int getranValue() {
												return ran;
								};
				private:
								static FreeListNext freeList; // ����1��ָ������б����һ������ ����2����Rational����ǿתΪfreeList����
								static void expandTheFreeList(); // �ڴ�صĹؼ�����
								enum  {
												EXPANSION_SIZE = 32
								};
								int  ran = 0;
};
}

//  �汾2 ģ���� ---
namespace MemoryPoolVer2{
				// ģ��������ڴ�ص�����,ͨ������T�����ڴ�صĴ�С���ﵽ���� --����ͨ���̳зǷ�ʽд��
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
								static void* operator new(size_t size) ;//{ return memorypoolController->alloc(size);}
								static void operator delete(void* demo, size_t size);//{ memorypoolController->free(demo);};
								static void newMemPool();//{ memorypoolController = new MemoryPool<RatinalVer2>();} // Ϊʲô��Ҫ����������ֱ��new ---
								//��Ϊcontroller �Ǿ�̬�����������ڹ��캯������ֱ������ռ�
								static void deleteMemPool();//{ delete memorypoolController;}  // Ϊʲôstatic ��ʵ�ֲ��ܷ��� h�ļ���  --
								// ��Ϊ�ڱ���ʱmain.cpp�У� h�ļ���copy��main��ȥ��������Ϊinclude����������͵����ˣ���̬����û�ж��塣
				private:
								static MemoryPool<RatinalVer2> *memorypoolController; // ��Ҫ������ⲿ���������Ͷ��� --Ϊʲô��Ҫstatic��
								//��Ϊnew  �� delet������staitc�������������staitc����new�в��ܷ��ʷǾ�̬��Ա����
				};
				// in all:
				// ���к��о�̬��Ա���� �;�̬��Ա����ʱ ����̬��Ա�����ĳ�ʼ��ͬһ����cpp�У������У�����̬��Ա������ʵ��Ҳ����cpp�С�
}
