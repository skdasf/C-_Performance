// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>   // std::mutex
#include <chrono>

std::mutex mtx;           // mutex for critical section

void print_block(int n, char c) {
	// critical section (exclusive access to std::cout signaled by locking mtx):
	
	std::cout << "test 3s "<< std::this_thread::get_id() << "\n";//线程1 2 同时执行
	mtx.lock();//线程2 阻塞3s
	//for (int i = 0; i < n; ++i) { std::cout << c; }
	//std::cout << '\n';
	std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 3));//两者线程互斥
	std::cout << "wait for 3 seconds \n";
	mtx.unlock();//如果不解锁 线程就会一直互斥 即不会有线程执行该函数。或者说第二个线程会一直等待解锁
	std::cout << "test 6s\n" << std::this_thread::get_id() << "\n";//不会执行同时？
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 6));
    std::cout << "wait for 6 seconds"<< std::this_thread::get_id() << "\n" ;//前面线程比后面线程 快3s 前是9s 执行完成 后是12s执行完成 
    std::cout << '\n';
	//sum :即 阻塞线程不会执行后面没有lock 的对象，而是要等待锁线程unlock 释放锁时才会执行后面得代码

}

int mainsss()
{
	std::thread th1(print_block, 100, '*');
	std::thread th2(print_block, 100, '$');

	th1.join();
	th2.join();

	return 0;
}