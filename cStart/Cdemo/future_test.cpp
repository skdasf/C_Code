#include <iostream>
#include <mutex>
#include <future>
#include <thread>
#include <memory>
#include <string>
#include <chrono>
#include <exception>
// 1. ����futre  promise  package_task


//2 shared_future ��һ��future Get����Զ����١�shared ����Get���
// 
// 

//3 std::async std::wait   --- asnyc ��������promise�����е��߳̽������˾��Զ�ִ�� promise_setValue�����Ǵ�launch::async��������������״̬��  launch::deferred������getʱ����״̬��������
// wait for ��������һ�����ʱ��t�����������tʱ��󣬲�����������waitfor���߳�,���ҷ��ػ���������futre��״̬��
//��״̬ȡ����promise ���setValue�������Tʱ��֮ǰsetValue ����ready���� 
//�������Tʱ��֮��setValue ����timeout���� 
//���߳�û�п�ʼ ����defferd�� 
void print_int(std::future<void> &fu , const std::string &str){
    std::cout << "start " << str << std::endl;
    try
    {
        fu.get(); // û��set_value ������
        std::cout << "������� " << str << std::endl;
    } catch(std::exception& e){
        std::cout<<"something wrong "<<e.what();
    }  
}

int print_int1(int x){
    std::cout<<"xxx :" <<x << std::endl;
    return x;
};

void pinrtrtsa(std::promise<void> &pro ,const std::string &str){
    std::cout << "start " << str << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"after 3s \n";
    pro.set_value();
    std::cout<<str;
}

int  package_test(int form, int to){
    for (int i = form; i != to; i--) {
        std::cout<<i<<"\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout<<"Finished!\n";
    return form - to;
}
int mainfututre(){
    // 1.
   // std::promise<void> prmis;
   // auto fu = prmis.get_future();
   // std::string msg = "something happened";
   // std::unique_ptr<std::thread> thr1(new std::thread(print_int,std::ref(fu) , msg));// ©дref
   // std::this_thread::sleep_for(std::chrono::seconds(2));
   //// prmis.set_value();
   // thr1->join();

  // //1.1 �������̣߳��������߳̿����������߳�
  //  std::promise<void> promis;
  //  auto fur = promis.get_future();
  //  std::string msg1 = "something happened";
  //  std::thread thr2(pinrtrtsa ,std::ref(promis),msg1);
  ////   fur.wait();// ����
  //  auto stat = fur.wait_for(std::chrono::seconds(3));
  //  if (stat == std::future_status::ready) {
  //      std::cout<<"ready";
  //  }
  //  if (stat == std::future_status::deferred) {
  //      std::cout << "deferred";
  //  }
  //  if (stat == std::future_status::timeout) {
  //      std::cout << "timeout";
  //  }
  //  thr2.join();
  //  //3.
  //  auto fure  =  std::async(print_int1,2); // ����future��ģ�� �Ǹ��ݺ����ķ������;�����
  //  auto res = fure.share(); // shared_future ԭ����fure��move����


  //  //3. wait 
  //  res.wait(); // �ȴ�async ִ����ɡ� �൱��asnyc ��future�����߳�ͬ������

  //  std::cout<<"res1 "<< res.get() << std::endl;
  //  std::cout<<"res "<< res.get() << std::endl;
  //  

  // 1. std::packaged_task
  std::packaged_task<int(int,int)> task1(package_test);
  auto ret = task1.get_future();

  std::thread tg(std::move(task1),10,0);
  auto vale  = ret.get();
  std::cout<<"value" << vale;
  tg.join();
    return 0;
}