#include <iostream>
#include <memory>

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
};

//������ͬ����ʡ��...

int mainsmart() {
    //A a;
    std::shared_ptr<A> sp1(new A());
    std::shared_ptr<A> sp2 = sp1->getSelf(); 
   // std::shared_ptr<A> sp2 = a.getSelf();

    std::cout << "use count: " << sp2.use_count() << std::endl;

    return 0;
}