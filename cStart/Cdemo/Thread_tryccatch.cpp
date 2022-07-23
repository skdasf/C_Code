#include <thread>
#include <vector>
#include <exception>
#include <iostream>
#include <future>
using namespace  std;
vector<int> test2 = { 1,2,3,4 };
//1. �������̵߳�trycatch �� �߳�try catch --һ���ķ�ʽ
//2. ��û�� û��throw ���쳣����ʵ�ַ�ʽ  -- ��
//3. ��һ���߳���throw��������һ���߳�catch -- promise

void get_int(std::promise<int>& prom) {
    //int x;
    std::cout << "Please, enter an integer value: ";
    //std::cin.exceptions(std::ios::failbit);   // throw on failbit
   if (1) {
							try {
								 test2.at(10);  // ���ֱ�����ʽ�ṩ��try catch
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

				//��һ���߳������׳��쳣������һ���߳��� try ����Catch����Ҫ�õ�promise.
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