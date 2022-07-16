#include <memory>
#include <iostream>
#include <string>
#define PRINT(N) \
				if(N) \
				{ \
				 N->isfunc();\
				} else { \
				std::cout<<"worng\n";      \
				};\
//1.测试类型转换 const static dynamic reinterpret
//2.测试经过dynamic_cast 转换后的地址跟源地址的情况---转换后的地址都不变，只是编译器对其中的内存重解释了
//3.智能指针的类型转换的情况 -- 只能share_ptr是

// sum: 指针类型转换 dynamic_cast。 dynamic_poniter_cast
// 基本类型转换（包括枚举） static_cast 
// 将const 转变成不是const const_cast
//unique_ptr  直接等于  类型1 ss= 类型2 std::move(变量)
enum class color { // enum class 防止多个枚举有定义了同一个枚举类型
    red  = 0, 
				black =1,
				blue =2
};

class dynamic_Base {
public:
				dynamic_Base() = default;
				virtual ~dynamic_Base() = default;
				virtual void isfunc() {
								std::cout<<"base\n";
				} ;
private:
};

class Child: public dynamic_Base {
public:
			
			Child() = default;
			~Child() = default;
			virtual void isfunc() override{
				std::cout<<"child\n";
			}
private:
};

class NObase {
public:
				NObase() = default;
				~NObase() = default;
    void isfunc() {
        std::cout << "base\n";
    };

private:

};



int main(){
				// 1.
				color test1 = color::black; 
				auto test1_cast = static_cast<int>(test1);
				auto test1_cast_cast = static_cast<color>(test1_cast);

				int test2[]={1,2,3,4};
				auto test2_cast = const_cast<int*>(test2);
				*test2_cast = 222;

			//	2.
				//std::unique_ptr<dynamic_Base> ptr;//不能强转
				//ptr = std::make_unique<Child>();
				//auto ptr_cast = dynamic_cast<Child*>(ptr); // NO
	 	//auto ptr_cast = std::dynamic_pointer_cast<Child>(ptr); // NO
			
   //2.
    auto ptr1 = new Child();
    auto ptr1_cast = dynamic_cast<NObase*>(ptr1); // 子类转父类
    PRINT(ptr1_cast)

    dynamic_Base* ptr_cast1 = ptr1; // 非智能智能指针
    PRINT(ptr_cast1)
		
			//3.
			std::shared_ptr<dynamic_Base> ptr; 
			ptr = std::make_shared<Child>();
			auto ptr_cast = std::dynamic_pointer_cast<Child>(ptr); //父类转子类 转换完地址跟基类相同
			PRINT(ptr_cast)

		 std::shared_ptr<Child> ptrc;
			ptrc = std::make_shared<Child>();
			auto ptrc_cast = std::dynamic_pointer_cast<dynamic_Base>(ptrc);
			PRINT(ptrc_cast)
	
			//std::shared_ptr<Child> sptr;
			//sptr = std::make_shared<Child>();
			//std::shared_ptr<dynamic_Base> = sptr; // No

			//3.1 unique_ptr 类型强转的问题
			std::unique_ptr<Child> uptr;
			uptr = 	std::make_unique<Child>();
			std::unique_ptr<dynamic_Base> u_ptr_cast = std::move(uptr);
			PRINT(u_ptr_cast)


    return 0;
}