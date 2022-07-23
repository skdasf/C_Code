
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
// windows ϵͳ����֮ ---- �������̣��̣߳�ͬ�����¼��ں˶���Event��
// Description
int main() {
    cout << i << endl;
  //  HANDLE hThread;
  /*  hThread = CreateThread(NULL, 0, FunProc, NULL, 0, NULL);
    DWORD dwRet = WaitForSingleObject(hThread, 1);
    if (dwRet == WAIT_OBJECT_0) {
        cout << "�������߳�ִ�н���" << endl;
    }
    if (dwRet == WAIT_TIMEOUT) {
        cout << "�ȴ���ʱ" << endl;
    }
    if (dwRet == WAIT_ABANDONED) {
        cout << "Abandoned" << endl;
    }
    CloseHandle(hThread);*/

    //// 1. �����¼��ں˾��  param1: ����İ�ȫ����һ��Ϊnull ,param2:�¼����ֶ����ã������Զ�����
    //// param3: ��ʼ�Ĵ���״̬ΪTRUE����FALSE�� Param4�������������¼��������ڽ��̼�Ĺ���
    //event = ::CreateEvent(nullptr,TRUE,FALSE,nullptr);
    //std::cout<<"create Done \n";
    //auto ret1 = GetLastError();
    //if (event != NULL) {
    //auto ret = ::WaitForSingleObject(event,(DWORD)500); // �ȴ�  ���eventΪFALSE���������̡߳� ���True����������Wait_OBJECT_0��
    //// ͬʱ֧���Զ������õȴ�ʱ�䡣���ΪINFINITE �߳̾ͻ�һֱ�ȴ���ȥ�� ���
    //std::cout << "Wait Done \n"; 

    //if (ret == WAIT_OBJECT_0) {
    //    std::cout<<"wait 0";
    //}
    //if (ret == WAIT_TIMEOUT) {
    //    std::cout << "wait Time out"; // �����趨ʱ��ͻ�Time out
    //}
    //::CloseHandle(event);
    //}

    // ������һ���߳���֪ͨ����һ���߳̽����� ��Rtsa�е���ͣ���ָ��Ĺ���
    HANDLE event;
    event = ::CreateEvent(nullptr, TRUE, FALSE, nullptr);
    std::function<void()> testfunc = print; // ������ִ�й����¼�����Ϊfalse��᲻��ֱ��wait--����

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
         // 2sֱ������
         //this_thread::sleep_for(std::chrono::seconds(2));
         ::SetEvent(event);  //(rtsa) ����
         this_thread::sleep_for(std::chrono::seconds(5)); // ÿ2s ��ӡһ��testFunc
         ::ResetEvent(event); //5s��ֹͣ   (rtsa)ֹͣ
         this_thread::sleep_for(std::chrono::seconds(10)); // ÿ2s ��ӡһ��testFunc
         ::SetEvent(event); // 10s�� �ٴδ�ӡ
         //this_thread::sleep_for(std::chrono::seconds(5));
         //::SetEvent(event); // ��event ����Ϊture;
    
    });
    thr_emit.join();
    thr_wait.join();
    ::CloseHandle(event);
    system("pause");
    return 0;
}
