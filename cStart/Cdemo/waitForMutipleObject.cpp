
#include "stdio.h"
#include "windows.h"
#include <iostream>
#include <thread>
#include <functional>
using namespace std;
void print() {
   static  int i =0;
   std::this_thread::sleep_for(std::chrono::seconds(1));
   std::cout<<++i <<"\n";

}
int i = 0;
DWORD WINAPI FunProc(LPVOID lpParameter);

DWORD WINAPI FunProc(LPVOID lpParameter) {
    for (; i < 10; i++) {
        if (!(i % 10))
            cout << endl;
        else
            cout << i << endl;
    }
    return 0;
}
// windows 系统调用之 ---- 创建进程（线程）同步的事件内核对象（Event）
// Description
int main() {
    cout << i << endl;
  //  HANDLE hThread;
  /*  hThread = CreateThread(NULL, 0, FunProc, NULL, 0, NULL);
    DWORD dwRet = WaitForSingleObject(hThread, 1);
    if (dwRet == WAIT_OBJECT_0) {
        cout << "创建的线程执行结束" << endl;
    }
    if (dwRet == WAIT_TIMEOUT) {
        cout << "等待超时" << endl;
    }
    if (dwRet == WAIT_ABANDONED) {
        cout << "Abandoned" << endl;
    }
    CloseHandle(hThread);*/

    //// 1. 创建事件内核句柄  param1: 对象的安全属性一般为null ,param2:事件是手动重置，还是自动重置
    //// param3: 初始的触发状态为TRUE还是FALSE。 Param4：创建有名的事件对象，用于进程间的共享
    //event = ::CreateEvent(nullptr,TRUE,FALSE,nullptr);
    //std::cout<<"create Done \n";
    //auto ret1 = GetLastError();
    //if (event != NULL) {
    //auto ret = ::WaitForSingleObject(event,(DWORD)500); // 等待  如果event为FALSE会阻塞该线程。 如果True会立即返回Wait_OBJECT_0。
    //// 同时支持自定义设置等待时间。如果为INFINITE 线程就会一直等待下去。 入伙
    //std::cout << "Wait Done \n"; 

    //if (ret == WAIT_OBJECT_0) {
    //    std::cout<<"wait 0";
    //}
    //if (ret == WAIT_TIMEOUT) {
    //    std::cout << "wait Time out"; // 超过设定时间就会Time out
    //}
    //::CloseHandle(event);
    //}

    // 测试在一个线程中通知另外一个线程结束。 和Rtsa中的暂停，恢复的过程
    HANDLE event;
    event = ::CreateEvent(nullptr, TRUE, FALSE, nullptr);
    std::function<void()> testfunc = print; // 测试在执行过程事件设置为false后会不会直接wait--不能

    auto thr_wait =std::thread([event,testfunc](){ 
        while (true) {
           // auto start_time = std::chrono::system_clock::now();
            //std::cout << "start wait \n";
         auto ret  = ::WaitForSingleObject(event,INFINITE);
         if (ret == WAIT_OBJECT_0) {
            //std::cout<<"end wait\n";
            //std::cout<<"after "<< std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-start_time).count() << "s \n";
         }
         testfunc();
       }
    });

    auto thr_emit = std::thread([event](){
         //std::cout<<"emit after 5s\n";
         // 2s直接启动
         //this_thread::sleep_for(std::chrono::seconds(2));
         ::SetEvent(event);  //(rtsa) 启动
         this_thread::sleep_for(std::chrono::seconds(5)); // 每2s 打印一次testFunc
         ::ResetEvent(event); //5s后停止   (rtsa)停止
         this_thread::sleep_for(std::chrono::seconds(10)); // 每2s 打印一次testFunc
         ::SetEvent(event); // 10s后 再次打印
         //this_thread::sleep_for(std::chrono::seconds(5));
         //::SetEvent(event); // 将event 设置为ture;
    
    });
    thr_emit.join();
    thr_wait.join();
    ::CloseHandle(event);
    system("pause");
    return 0;
}
