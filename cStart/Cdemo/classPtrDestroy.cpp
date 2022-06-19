/*
Q：	智能指针的结构体析构后 其中的智能指针的成员变量是否也被析构--会
A:		会自动析构  顺序为 类中的成员变量。类。
				因此 在一个类被声明为智能指针时，
				它会清空其中的所有成员对象的地址。
				因此如果成员为智能指针时，它会触发只能指针的析构操作。

Q1： unique_ptr 为成员变量时，类型为const &  或者 const时初始化的问题-- 只能使用参数列表初始化
A1： 根据const的特性，无法在构造函数中，parm = std::make_unique<C>();这样的写法。因此只能在构造函数的参数列表进行赋值
EX1: 对于类的成员变量，调用构造函数时，会先去构造成员变量（变量只含基本变量。指针，对象都在其他地方初始化,
				 其中对象的初始化之前会检查参数列表中是否有该对象满足的构造函数），再执行其中的函数
				 因此对于const &声明的变量，在构造函数的初始化列表中把声明和赋值合成了一个步骤。
							
Q2：构造函数的参数列表 是怎样的赋值过程--对象和指针初始化与赋值不同
A2：因为对象和指针的声明和初始化 跟 普通变量的初始化不一样因此会产生这个问题。
				对于对象和指针的 初始化和声明 都是放在到了构造函数或者参数列表中。

Q3: delete 一个结构体指针 -- 普通指针会常驻 智能指针不会常驻 
A3: 说明智能指针跟普通指针确实不一样。也反应了一个现象： const 修饰智能指针时，
				只是对该智能指针的初始化进行限制，但是可以通过该智能指针去修改对应的数据。
				（即不能出现 const std::unique_ptr<C>& cuniquePtr = 左值）

sum :   1. 对于const 的指针或者对象，或者不含默认构造函数的对象。都放在参数列表进行初始化。
								2.  一个结构体中的普通指针在该结构体被delete（析构）时，该普通指针的内存依然存在。但是如果是只能指针就不会存在
        3. const 修饰智能指针时，只是对函数的参数传递进行了约束，但是可以通过该智能指针去修改对应的数据。
*/
#include <memory>
#include <iostream>
struct C1 {
				int c1;
				C1(int a){};

};

struct C {
public:
    int a = 1;
    int b = 2;
    int c = 3;
				C(){
				std::cout<<"construct C";
				}
    ~C() {
        std::cout << "destroy C";
    }
};


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
				char b;
				const int c1_int = 1;
				char c ='a';
				C  sss;
		 // C1 c111; // 首先检查参数列表中是否含有满足C1的拷贝构造函数，如果没有直接报错  
				int a[4] ={1,2,3,4}; // 数组全部清空e
			 const	C* cptr; //delete后 会常驻内存   2. 这种用const修饰的指针时不能被修改的，智能指针可以
    const std::unique_ptr<C>& cuniquePtr   = std::make_unique<C>() ;//delete后 不会常驻内存   引用
				B(const std::unique_ptr<C>& c1):cuniquePtr(c1){// 1. 调用构造函数时，会先去构造成员变量（只有赋值操作（=）成员变量，而不会构造声明的对象），再执行其中的函数

					//	 c111  =  C1(1);
							cuniquePtr->c = 1;  // 是可以修改指向的内存的
							//c1= 2;//
						//	cuniquePtr = std::make_unique<C>();   1. cuniquePtr 是非const 的变量才能在构造函数中赋值。对于const只能在参数列表中初始化。
				};
				~B(){
					std::cout<<"destroy B";
					}

					void test(){
					cuniquePtr->c;  // C 的定义写在前面
					}
};


int main()  {

    {
      auto ptr =  std::make_unique<C>();// 对于const 
						B* b = new B(ptr);
								//delete b;
							//	auto test = std::make_unique<B>();
							//	test.reset();//清空unique指针
							//	auto ptrA = std::make_shared<A>(std::make_unique<B>());
				
				}


return 0;
}