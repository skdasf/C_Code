/*
Q������ָ��Ľṹ�������� ���е�����ָ��ĳ�Ա�����Ƿ�Ҳ������
A: ���Զ�����  ˳��Ϊ ���еĳ�Ա�������ࡣ
��� ��һ���౻����Ϊ����ָ��ʱ������������е����г�Ա����ĵ�ַ����������ԱΪ����ָ��ʱ�����ᴥ��ֻ��ָ�������������
*/
#include <memory>
#include <iostream>
struct  B;
class A {	
				const std::unique_ptr<B>& bptr; // 
public:
				A(const std::unique_ptr<B> & par):bptr(par) {
				std::cout<< "construct A\n";
				};
				~A() {
				std::cout<<"destroy A\n";
				};
private:
};
struct  C ;
struct B {
				char b = '1';
				char c ='a';
				int a[4] ={1,2,3,4}; // ����ȫ�����e
				C* cptr; //delete�� �᳣פ�ڴ�
    const std::unique_ptr<C> &cuniquePtr;//delete�� ���᳣פ�ڴ�
				B(const std::unique_ptr<C> & cc):cuniquePtr(cc){};
				~B(){
					std::cout<<"destroy B";
					}
};

struct C {
				int a  =1 ;
				int b = 2;
				int c =3;
				~C(){
				std::cout<<"destroy C";
				}
};

int main()  {

				{   
								B* b = new B( std::make_unique<C>());
								delete b;
							//	auto test = std::make_unique<B>();
							//	test.reset();//���uniqueָ��
							//	auto ptrA = std::make_shared<A>(std::make_unique<B>());
				
				}


return 0;
}