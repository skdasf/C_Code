#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

/*
    A1: 练习回调，与注册回调。用一个类执行另外一个类中的函数。
            当B中成员变量的值增加到10后，执行A中的函数。
    Q1: 在调用B的注册回调函数，只能传递lambda函数，而不能传递A的对象实例中的非静态成员方法。因为
        在对象中的非static成员方法，是含有this指针的，如果直接利用参数func 没有指定实体的对象，是无法找到this指针导致调用失败

    A2： 用两种方式，1.B中生成A的实例对象。  2.调用B的注册回调函数  
    Q2： 非静态成员都不能直接注册。

    A3： rtsa 中engine的回调实现方式
    Q3：
*/
namespace callback{
class A;
class B;
//typedef function<void(const string&)> error;
//typedef function<void(const string&)> succ;
// rtsa 中的回调方式
struct handle {
    using succ1= function<void(const string&)>;
    succ1 hanle;

};


using succ = function<void(const string&)>;
// engine
class A {
public:
				 //A() = default;
    std::unique_ptr<handle> handle_;
				~A() = default;
     A(){ 
     };

    void callback(const string& st) {
        cout<<" I am Class A" << st;
    }
    void  setHandle(const handle& parm){ 
       handle_ = std::make_unique<handle>(parm);
    }
private:
};
// command
class B {
public:
    int count;
    succ calbackB;
  
    //
    //A& a1;
    B(){
        count = 0;
        // 测试在构造函数中生成A的实例
       /* unique_ptr<A> ptra(new A());
        calbackB = &ptra->callback;*/
        //  calbackB = &a.callback;
        cout << "B construct \n";
    }
  //  B(A& a):a1(a){
  //  count  = 0;
  //  // 测试在构造函数中生成A的实例
  // 
  //  calbackB = &ptra->callback;*/
  //  //  calbackB = &a.callback;
  //  cout<< "B construct \n";
  //  };
    ~B(){
    cout<< "B destruct \n";
    }
    // rtsa：用B 定义A对象中的成员属性。
 /*   void sethanle(){
        handle s;
        s.hanle = [](const string& st) {
            cout << "rtsa  " << st;
        };
       a1.setHandle(s); 
    }*/

    void regester(succ func){
        calbackB = func;
    };
    void start(){
        while (true) {
            std::this_thread::sleep_for(chrono::seconds(1));
            count++;
            if (count == 10) {
                calbackB("count = 10");
              // a1.handle_->hanle("sss"); // rtsa: 执行a1成员列表中的结构体重的回调
                break;
            }
        }
      
    }
};

}

int main(){
   {
    callback::A ass;
    unique_ptr<callback::A> testA(new callback::A());

    unique_ptr<callback::B> test(new callback::B());

    //test->regester(std::bind(&callback::A::callback, &ass,std::placeholders::_1));  // right
    //test->regester(std::bind(&callback::A::callback,&*testA,std::placeholders::_1));  // right  but  strange
    // unique_ptr<callback::B> test(new callback::B(ass));
    //test->sethanle();

   // test->regester([](const string &st){ cout<< st;}); // 使用匿名函数注册回调
    //test->regester(std::bind(callback::A::callback,testA));
    
    
    test->start();
   }
    return 0;
} 