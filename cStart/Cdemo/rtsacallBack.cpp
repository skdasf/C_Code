#include <functional>
#include <memory>
#include <iostream>
#include <future>
#include <string>
#include <vector>

typedef std::function<void(int ,const std::string& msg)> loghander;

using error_callback_t = std::function<void(const std::string&)>;

struct error_t {
    using error_callback_t = void(__stdcall*)(void*, const char*);

    void* impl_;
    error_callback_t error_info_;
};

//1. Rtsa 中的log
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
//2. 关于void*

void print(void* pra){
    auto ch = (char*) pra;
    auto in = (int*) pra;
    std::cout<<"in " <<*in <<std::endl;
    std::cout<<"ch " <<*ch <<std::endl;

}


int main(){
    // 1.test
    loghander handle = [](int num,const std::string &str){
        std::cout<<"num" << num <<std::endl;
        std::cout<<"str" <<str << std::endl;
    }; // 在外定义，构造注册
    std::unique_ptr<engin> engin1;
    engin1 = std::make_unique<engin>(handle);
    engin1->startItem();
    // 2. test
    //std:vector<int> ddd = {1,2,3,4};
    std::vector<int> ss = {1545,2,3};
    print(ss.data());

    


    std::promise<void> p;
    auto fu = p.get_future();
    fu.wait();

    std::cout<<"阻塞";
    return 0;
}