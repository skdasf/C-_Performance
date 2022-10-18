// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>   // std::mutex
#include <chrono>

std::mutex mtx;           // mutex for critical section

void print_block(int n, char c) {
	// critical section (exclusive access to std::cout signaled by locking mtx):
	
	std::cout << "test 3s "<< std::this_thread::get_id() << "\n";
	mtx.lock();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 3));
	std::cout << "wait for 3 seconds \n";
	mtx.unlock();
	std::cout << "test 6s\n" << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 6));
    std::cout << "wait for 6 seconds"<< std::this_thread::get_id() << "\n" ;
    std::cout << '\n';


}

int mainsss()
{
	std::thread th1(print_block, 100, '*');
	std::thread th2(print_block, 100, '$');

	th1.join();
	th2.join();

	return 0;
}