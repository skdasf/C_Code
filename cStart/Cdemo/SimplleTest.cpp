#include <iostream>
#include <string>
#include <variant>
#include <variant>
//1 . 测试decltyp(::函数)
void decltype_func();
void test(){
    std::cout<< "test\n";
};
// 2. 测试variant C++17
std::variant<int, float> test111;

int main(){

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
   
    return 0;
}


