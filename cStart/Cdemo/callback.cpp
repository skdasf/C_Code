#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

/*
    A1: ��ϰ�ص�����ע��ص�����һ����ִ������һ�����еĺ�����
            ��B�г�Ա������ֵ���ӵ�10��ִ��A�еĺ�����
    Q1: �ڵ���B��ע��ص�������ֻ�ܴ���lambda�����������ܴ���A�Ķ���ʵ���еķǾ�̬��Ա��������Ϊ
        �ڶ����еķ�static��Ա�������Ǻ���thisָ��ģ����ֱ�����ò���func û��ָ��ʵ��Ķ������޷��ҵ�thisָ�뵼�µ���ʧ��

    A2�� �����ַ�ʽ��1.B������A��ʵ������  2.����B��ע��ص�����  
    Q2�� �Ǿ�̬��Ա������ֱ��ע�ᡣ

    A3�� rtsa ��engine�Ļص�ʵ�ַ�ʽ
    Q3��
*/
namespace callback{
class A;
class B;
//typedef function<void(const string&)> error;
//typedef function<void(const string&)> succ;
// rtsa �еĻص���ʽ
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
        // �����ڹ��캯��������A��ʵ��
       /* unique_ptr<A> ptra(new A());
        calbackB = &ptra->callback;*/
        //  calbackB = &a.callback;
        cout << "B construct \n";
    }
  //  B(A& a):a1(a){
  //  count  = 0;
  //  // �����ڹ��캯��������A��ʵ��
  // 
  //  calbackB = &ptra->callback;*/
  //  //  calbackB = &a.callback;
  //  cout<< "B construct \n";
  //  };
    ~B(){
    cout<< "B destruct \n";
    }
    // rtsa����B ����A�����еĳ�Ա���ԡ�
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
              // a1.handle_->hanle("sss"); // rtsa: ִ��a1��Ա�б��еĽṹ���صĻص�
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

   // test->regester([](const string &st){ cout<< st;}); // ʹ����������ע��ص�
    //test->regester(std::bind(callback::A::callback,testA));
    
    
    test->start();
   }
    return 0;
} 