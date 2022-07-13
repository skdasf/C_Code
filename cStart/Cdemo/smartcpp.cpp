#include <iostream>
#include <memory>
//1. 测试Get sharedPtrthis。
class A : public std::enable_shared_from_this<A> {
public:
    A() {
        std::cout << "A constructor" << std::endl;
    }

    ~A() {
        std::cout << "A destructor" << std::endl;
    }
    // 返回share_ptr自身的对象
    std::shared_ptr<A> getSelf() {
        return shared_from_this(); // 栈对象会在这里被析构掉。
    }
    A* getSelf11() {
        return this; // 栈对象会在这里被析构掉。
    }
};
//其他相同代码省略...

// 2. 测试只能指针的自动析构,主要是Lambda中的参数。 Lambda 中的参数必须是只能指针的模板类型


int main() {
    // 1.测试enable_shared_from_this的引用计数
   {
    //A a;
    std::shared_ptr<A> sp1(new A());
    std::shared_ptr<A> sp2 = sp1->getSelf(); 
   // std::shared_ptr<A> sp3 (sp1->getSelf11());
   // std::shared_ptr<A> sp2 = a.getSelf();
    std::cout << "use count: " << sp2.use_count() << std::endl;
   // std::cout<<"sp3" << sp3.use_count() << std::endl; // 1 不会增加引用计数
   }
   // 2 
   std::shared_ptr<A> sp122(new A() ,[](A* v){ std::cout << "test2  "; delete v;});
    

    return 0;
}