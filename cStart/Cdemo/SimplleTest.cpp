#include <iostream>
#include <string>
#include <variant>
#include <thread>
#include <memory>
#include <functional>
//1 . ����decltyp(::����)
void decltype_func();
void test(){
    std::cout<< "test\n";
};
// 2. ����variant C++17
std::variant<int, float> test111;
// 3. class �����߳�bind���Ա������ ͬʱ��join ����try catch  --- �����׳��쳣���������߳�exit  ������return
class ThreadTest {
public:
    ThreadTest();
    ~ThreadTest();
    void test(int a, const std::string& str);

private:

};

ThreadTest::ThreadTest() {
}

ThreadTest::~ThreadTest() {
}

// 4.���Լ���dll�ļ�
void dlltest(const std::string &str);


void ThreadTest::test(int a, const std::string& str) {
    try {
        std::cout << "\n";
        std::cout << "int " << a << "\n";
        std::cout << "string" << str << "\n";
    }
    catch (const std::exception& e) {
        std::cout<< "excep" << e.what();
    }
}

int mainSimpleTest(){

    using type  = decltype(::decltype_func);// decltype ��������һ���������ͣ�������functional��
    type* sss; // ����Ϊ����ָ�롣��Ϊtest����������־���һ��ָ�롣
    sss = test;
    sss();
    int a =10;
    decltype(a) cc;// decltype �ĵڶ����÷���
    cc= 10;
    std::cout<< "cc" << cc;
    // 2.test

    test111 = 2;
    test111 = 1.0f;
 
    try {
        auto& res = std::get<int>(test111);
    }
    catch (const std::exception& e) {
        std::cout<<"ss" << e.what();
    }

   // 3. test
    ThreadTest t;
    auto  func =  std::bind(&ThreadTest::test, &t, std::placeholders::_1, std::placeholders::_2);
    std::unique_ptr<std::thread>  thr;
    try {
        thr = std::make_unique<std::thread>(func, 1, "2"); // bind
    } catch (const std::exception& e) {
            std::cout << "excep" << e.what();
    }
   //exit(1);
    thr->join();
    // 4. test
   dlltest("this is test");
   return 0;
}


