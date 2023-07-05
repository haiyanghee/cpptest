#include <memory>
#include <iostream>
template<typename T>
struct A{
    explicit A(int a){
        std::cout<<"created defalt \n";
        T::NODEFAULTTT;
    }
    void f(){}
};

//template<typename T>
//struct A<T[]>{
//    explicit A(){
//        std::cout<<"created defalt \n";
//    }
//    void f(){}
//};

template<typename T, size_t N>
struct A<T[N]>{
    explicit A(int a){
        std::cout<<"created with N = "<<N<<"\n";
        T::asdf;
    }
    void f(){
        //T::asdf;
    }
};

template<typename T>
struct A<T[2147483648]>{
    explicit A(int a){
        std::cout<<"created with T[2147483648] = \n";
        T::succeed1;
    }
    void f(){
        //T::asdf;
    }
};

template<typename T>
struct A<T[1125899906842624]>{
    explicit A(){
        std::cout<<"created with T[1125899906842624] = \n";
        //T::succeed2;
    }
    void f(){
        //T::asdf;
    }
};


template<typename T, size_t N>
void testArr(T (&)[N]){
    //T::noo;
}

//int haha[1125899906842624]; //static array is not lazy either
int main()
{
    /*
    auto p1 = unique_void(new int(959));
    //auto p2 = unique_void(new double(595.5));
    //auto p3 = unique_void(new std::string("Hello World"));
    auto p4 = unique_void(new int [69]);

        f<int>();
    */
//A<int[]>a ;
//a.f();

//A<int [(size_t)1000000000000]>b(3);
//A<int [(size_t)1000000000000]>b{3};


A<int [1125899906842624]>b; //2^50
A<int [(size_t)1125899906842624]>bb;

/*
//int ta[(size_t)1000000000];//ok
//int ta[(size_t)2147483647];//2*63 -1 ok
int ta[(size_t)2147483648];//2*63  NOT ok

testArr(ta);
A<decltype(ta)>c{3};
    c.f();

    */

//b.f();
}  
