#include <iostream>
#include <string>

void decltype_func();
void test(){
    std::cout<< "test\n";
}
int main(){

    using type  = decltype(::decltype_func);// decltype ��������һ���������ͣ�������functional��
    type* sss; // ����Ϊ����ָ�롣��Ϊtest����������־���һ��ָ�롣
    sss = test;
    sss();
    int a =10;
    decltype(a) cc;// decltype �ĵڶ����÷���
    cc= 10;
    std::cout<< "cc" << cc;
    return 0;
}


