#include <iostream>
#include <memory>
//1. ����Get sharedPtrthis��
class A : public std::enable_shared_from_this<A> {
public:
    A() {
        std::cout << "A constructor" << std::endl;
    }

    ~A() {
        std::cout << "A destructor" << std::endl;
    }
    // ����share_ptr����Ķ���
    std::shared_ptr<A> getSelf() {
        return shared_from_this(); // ջ����������ﱻ��������
    }
    A* getSelf11() {
        return this; // ջ����������ﱻ��������
    }
};
//������ͬ����ʡ��...

// 2. ����ֻ��ָ����Զ�����,��Ҫ��Lambda�еĲ����� Lambda �еĲ���������ֻ��ָ���ģ������


int main() {
    // 1.����enable_shared_from_this�����ü���
   {
    //A a;
    std::shared_ptr<A> sp1(new A());
    std::shared_ptr<A> sp2 = sp1->getSelf(); 
   // std::shared_ptr<A> sp3 (sp1->getSelf11());
   // std::shared_ptr<A> sp2 = a.getSelf();
    std::cout << "use count: " << sp2.use_count() << std::endl;
   // std::cout<<"sp3" << sp3.use_count() << std::endl; // 1 �����������ü���
   }
   // 2 
   std::shared_ptr<A> sp122(new A() ,[](A* v){ std::cout << "test2  "; delete v;});
    

    return 0;
}