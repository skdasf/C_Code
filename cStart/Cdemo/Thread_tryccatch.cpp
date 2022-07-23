#include <thread>
#include <vector>
#include <exception>
#include <iostream>
#include <future>
using namespace  std;
vector<int> test2 = { 1,2,3,4 };
//1. 测试主线程的trycatch 和 线程try catch --一样的方式
//2. 有没有 没有throw 的异常捕获实现方式  -- 无
//3. 在一个线程中throw，在另外一个线程catch -- promise

void get_int(std::promise<int>& prom) {
    //int x;
    std::cout << "Please, enter an integer value: ";
    //std::cin.exceptions(std::ios::failbit);   // throw on failbit
   if (1) {
							try {
								 test2.at(10);  // 这种遍历方式提供了try catch
							}
							catch (const std::exception&) {
											prom.set_exception(std::current_exception());
							}
   
   }
}

void print_int(std::future<int>& fut) {
    try {
        int x = fut.get();
        std::cout << "value: " << x << '\n';
    }
    catch (std::exception& e) {
        std::cout << "[exception caught: " << e.what() << "]\n";
    }
}


int mainthreadtry(){
				vector<int> test1 = { 1,2,3,4 };
				int N = 4;
				try {
								test1.at(100);
				}
				catch (const std::exception& e) {
								std::cout<<"out of range\n" << e.what();
				}

				//在一个线程里面抛出异常在另外一个线程中 try 并且Catch到需要用到promise.
				try {
								auto fur = std::async([N,test1](void){
												if (N > test1.size() - 1) {
																throw std::runtime_error("out of range saync");
												} 
												test1[N];
       });
									  fur.wait();
				}
    catch (const std::exception& e) {
								std::cout << "out of range\n" << e.what();
    };
				// 3. 
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread th1(get_int, std::ref(prom));
    std::thread th2(print_int, std::ref(fut));

    th1.join();
    th2.join();
    return 0;
		
}