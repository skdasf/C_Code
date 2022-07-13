#include <iostream>
#include <string>
#include <variant>
#include <thread>
#include <memory>
#include <functional>
//1 . 测试decltyp(::函数)
void decltype_func();
void test(){
    std::cout<< "test\n";
};
// 2. 测试variant C++17
std::variant<int, float> test111;
// 3. class 测试线程bind类成员方法。 同时不join 进行try catch  --- 不能抛出异常，除非主线程exit  而不是return
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

// 4.测试加载dll文件
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

    using type  = decltype(::decltype_func);// decltype 可以声明一个函数类型（类似于functional）
    type* sss; // 必须为函数指针。因为test函数这个名字就是一个指针。
    sss = test;
    sss();
    int a =10;
    decltype(a) cc;// decltype 的第二种用法。
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


