#include <iostream>
#include <string>
#include <variant>
#include <variant>
//1 . ����decltyp(::����)
void decltype_func();
void test(){
    std::cout<< "test\n";
};
// 2. ����variant C++17
std::variant<int, float> test111;

int main(){

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
   
    return 0;
}


