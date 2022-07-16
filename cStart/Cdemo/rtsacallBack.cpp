#include <functional>
#include <memory>
#include <iostream>
#include <future>
#include <string>

typedef std::function<void(int ,const std::string& msg)> loghander;

class engin;
class workitem;

// work item
class workitem {

public:
    workitem() = default;
    void start();
    ~workitem() = default;

private:

};
void workitem::start() {
    int i = 10;
    for (auto j = 0; j < i; j++) {
        std::cout << "j :" << j << std::endl;
    }
}
// engine 
class engin {
				loghander log_;
    struct impl;
public:
				engin(const loghander &hand):log_(hand),impl_(std::make_unique<impl>(hand)){
        log_(2,"engin construct");
			 }
    void startItem() {
        impl_->start();
    };
    
				~engin() = default;
private:
    std::unique_ptr<impl> impl_;
    struct impl {
        loghander log_;
        std::unique_ptr<workitem> itemPtr;
        impl(const loghander& log) : log_(log),itemPtr(std::make_unique<workitem>()){
        }
        void start(){
            if (itemPtr!=nullptr) {
                log_(1,"some hanppen");
                itemPtr->start();
            }
        }
    };

};



int main(){
    loghander handle = [](int num,const std::string &str){
        std::cout<<"num" << num <<std::endl;
        std::cout<<"str" <<str << std::endl;
    }; // 在外定义，构造注册
    std::unique_ptr<engin> engin1;
    engin1 = std::make_unique<engin>(handle);

    engin1->startItem();

    std::promise<void> p;
    auto fu = p.get_future();
    fu.wait();

    std::cout<<"阻塞";
    return 0;
}