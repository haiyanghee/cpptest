#include <iostream>
#include <memory>
#include <functional>

void g(std::unique_ptr<int> p){
    std::cout<<"in g(), p = "<<*p<<"\n";
}

void FF(std::function<void()> f){
    f();
    f();
}

template<typename T>
struct MyUniqurPtrSaver{
    MyUniqurPtrSaver(std::unique_ptr<T> i) : ptr(std::move(i)){}
    std::unique_ptr<T> ptr;
};

int main(){
    std::function<void()> myf;
    {
        //std::unique_ptr<int> p = std::make_unique<int>(69);
        std::unique_ptr<int> p(new int(69));
        std::cout<<"p addr = "<<(uintptr_t) &p<<"\n";
        /*
        myf = std::bind(
           [](std::unique_ptr<int>& pp){
               g(std::move(pp));
           }
         ,p
         );
        */

        /*
        //this segfaults (as expected..)
        myf = std::bind(
           [&](){
               g(std::move(p));
           }
         );
        */

        /*
        //myf = std::bind(
        auto l = std::bind(
           [](std::unique_ptr<int>& pp){
               //g(std::move(pp));
                *pp=1;
           }
         , std::move(p)
         );
        myf = l;
        */

        /*
        //myf = std::bind(
        std::function<void()> aa = std::bind(
           [](std::unique_ptr<int>& pp){
                std::cout<<"pp addr = "<<(uintptr_t) &pp<<"\n";
           }
           , std::ref(p)
         );
        */

        /*
        //myf = std::bind(
        std::function<void()> aa = std::bind(
           [](MyUniqurPtrSaver<int> s){
                //std::cout<<"pp addr = "<<(uintptr_t) &s<<"\n";
           }
           , MyUniqurPtrSaver<int>{std::move(p)}
         );
        */

        //NOTE: if use std::function, it has to be copied, so storing unique ptr is impossible
        //there's std::move_only_funciton in C++23...

        //if no store std::function (but just storing a lambda), you are forced to use C++14 generalized lambda capture.. since the value members of lambda must be copied or referenced, it cannot contain move-only types..
        //auto l =[p = std::move(p)]() mutable{
        //        //std::cout<<"pp addr = "<<(uintptr_t) &s<<"\n";
        //       g(std::move(p));
        //   } ;
        //myf = l;
    }
    FF(myf);
}
