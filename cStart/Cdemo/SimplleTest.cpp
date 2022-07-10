#include <iostream>
#include <string>

void decltype_func();
void test(){
    std::cout<< "test\n";
}
int main(){

    using type  = decltype(::decltype_func);// decltype 可以声明一个函数类型（类似于functional）
    type* sss; // 必须为函数指针。因为test函数这个名字就是一个指针。
    sss = test;
    sss();
    int a =10;
    decltype(a) cc;// decltype 的第二种用法。
    cc= 10;
    std::cout<< "cc" << cc;
    return 0;
}


