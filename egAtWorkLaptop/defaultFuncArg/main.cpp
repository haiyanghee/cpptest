#include <bits/stdc++.h>

struct A{
    bool b=false;
    std::string s;
};

void f(const A& a = {}){
    std::cout<<"A.b = "<<a.b<<", A.s = "<<a.s<<", a.s.size = "<<a.s.size()<<"\n";
}

//compile with C++11 and it works as expected.. but it will copy it everytime ofcourse
//g++ -std=c++11 main.cpp

int main(){
    f();
    A a{};
    a.b=true;
    a.s="hi";
    f(a);
}
