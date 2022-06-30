#include "common.hpp"
using namespace std;

class Hello {
public:
    void say(string name) {
        cout << name << " say: hello world!" << endl;
    }
};

int main () {
    Hello h;
    auto func = boost::bind(&Hello::say, &h, "zhang san");
    func();
    //  1.local test
   // std::locale::global(std::locale("German"));
   // std::locale loc;
   // print<std::string>(loc.name(),"locale");
   // print('$',"localtest");
    //2. stirng  测试不通过
    std::locale::global(std::locale("German"));
    std::string s = "Boris Scholing";
    print(boost::algorithm::to_upper_copy(s), "algorithm1");
    print(boost::algorithm::to_upper_copy(s, std::locale("German")), "algorithm2");
    // 字符串删除 
    print(boost::algorithm::erase_first_copy(s, "i"),"erase");
    print(boost::algorithm::erase_nth_copy(s, "cho",0),"erase");// earse 指定的字符串
    print(boost::algorithm::erase_last_copy(s, "i"),"erase"); // 从后往前 earse 
    print(boost::algorithm::erase_all_copy(s, "i"),"erase"); // 移除所有的i
    print(boost::algorithm::erase_head_copy(s, 5),"erase");// 从前往后移除长度为5个的字符串
    print(boost::algorithm::erase_tail_copy(s, 8),"erase"); // 从后往前移除长度为8的字符串
    return 0;
}