/*
Q：智能指针的结构体析构后 其中的智能指针的成员变量是否也被析构
A: 会自动析构  顺序为 类中的成员变量。类。
因此 在一个类被声明为智能指针时，它会清空其中的所有成员对象的地址。因此如果成员为智能指针时，它会触发只能指针的析构操作。
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
				int a[4] ={1,2,3,4}; // 数组全部清空e
				C* cptr; //delete后 会常驻内存
    const std::unique_ptr<C> &cuniquePtr;//delete后 不会常驻内存
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
							//	test.reset();//清空unique指针
							//	auto ptrA = std::make_shared<A>(std::make_unique<B>());
				
				}


return 0;
}