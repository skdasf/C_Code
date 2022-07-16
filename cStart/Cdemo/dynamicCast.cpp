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
//1.��������ת�� const static dynamic reinterpret
//2.���Ծ���dynamic_cast ת����ĵ�ַ��Դ��ַ�����---ת����ĵ�ַ�����䣬ֻ�Ǳ����������е��ڴ��ؽ�����
//3.����ָ�������ת������� -- ֻ��share_ptr��

// sum: ָ������ת�� dynamic_cast�� dynamic_poniter_cast
// ��������ת��������ö�٣� static_cast 
// ��const ת��ɲ���const const_cast
//unique_ptr  ֱ�ӵ���  ����1 ss= ����2 std::move(����)
enum class color { // enum class ��ֹ���ö���ж�����ͬһ��ö������
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
				//std::unique_ptr<dynamic_Base> ptr;//����ǿת
				//ptr = std::make_unique<Child>();
				//auto ptr_cast = dynamic_cast<Child*>(ptr); // NO
	 	//auto ptr_cast = std::dynamic_pointer_cast<Child>(ptr); // NO
			
   //2.
    auto ptr1 = new Child();
    auto ptr1_cast = dynamic_cast<NObase*>(ptr1); // ����ת����
    PRINT(ptr1_cast)

    dynamic_Base* ptr_cast1 = ptr1; // ����������ָ��
    PRINT(ptr_cast1)
		
			//3.
			std::shared_ptr<dynamic_Base> ptr; 
			ptr = std::make_shared<Child>();
			auto ptr_cast = std::dynamic_pointer_cast<Child>(ptr); //����ת���� ת�����ַ��������ͬ
			PRINT(ptr_cast)

		 std::shared_ptr<Child> ptrc;
			ptrc = std::make_shared<Child>();
			auto ptrc_cast = std::dynamic_pointer_cast<dynamic_Base>(ptrc);
			PRINT(ptrc_cast)
	
			//std::shared_ptr<Child> sptr;
			//sptr = std::make_shared<Child>();
			//std::shared_ptr<dynamic_Base> = sptr; // No

			//3.1 unique_ptr ����ǿת������
			std::unique_ptr<Child> uptr;
			uptr = 	std::make_unique<Child>();
			std::unique_ptr<dynamic_Base> u_ptr_cast = std::move(uptr);
			PRINT(u_ptr_cast)


    return 0;
}