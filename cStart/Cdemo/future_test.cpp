#include <iostream>
#include <mutex>
#include <future>
#include <thread>
#include <memory>
#include <string>
#include <chrono>
#include <exception>
// 1. 测试futre  promise  package_task


//2 shared_future 在一个future Get后就自动销毁。shared 可以Get多次
// 
// 

//3 std::async std::wait   --- asnyc 就类似于promise。其中的线程结束完了就自动执行 promise_setValue。但是存launch::async（函数结束返回状态）  launch::deferred（调用get时返回状态）的特性
// wait for 可以设置一个相对时间t，如果经过了t时间后，不会阻塞调用waitfor的线程,并且返回会立即返回futre的状态。
//（状态取决于promise 多久setValue。如果在T时刻之前setValue 返回ready。） 
//（如果在T时刻之后setValue 返回timeout。） 
//（线程没有开始 返回defferd） 
void print_int(std::future<void> &fu , const std::string &str){
    std::cout << "start " << str << std::endl;
    try
    {
        fu.get(); // 没有set_value 会阻塞
        std::cout << "阻塞完成 " << str << std::endl;
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
   // std::unique_ptr<std::thread> thr1(new std::thread(print_int,std::ref(fu) , msg));// 漏写ref
   // std::this_thread::sleep_for(std::chrono::seconds(2));
   //// prmis.set_value();
   // thr1->join();

  // //1.1 阻塞主线程，在其他线程控制阻塞主线程
  //  std::promise<void> promis;
  //  auto fur = promis.get_future();
  //  std::string msg1 = "something happened";
  //  std::thread thr2(pinrtrtsa ,std::ref(promis),msg1);
  ////   fur.wait();// 阻塞
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
  //  auto fure  =  std::async(print_int1,2); // 根据future的模板 是根据函数的返回类型决定的
  //  auto res = fure.share(); // shared_future 原本的fure被move掉了


  //  //3. wait 
  //  res.wait(); // 等待async 执行完成。 相当于asnyc （future）的线程同步机制

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