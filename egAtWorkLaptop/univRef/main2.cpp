// clang-format off
#include <bits/stdc++.h>

//void g(int a) { printf(" in copy\n");}
void g(int& a) { printf(" in lvalue ref\n");}
void g(int&& a) { printf(" in rvalue ref\n");}

void g(const int& a) { printf(" in const lvalue ref\n");}
void g(const int&& a) { printf(" in const rvalue ref\n");}

//constexpr int&& myf(int a){
int&& myf(int a){
    return static_cast<int&&>(a);
}

struct MyS{
    int&& a;
};

//template <typename T>
//T&& myForward(T&& a){
//    return static_cast<T&&>(a);
//}

template <typename T, typename U = T&&>
//void myForward(T&& a){
void myForward(typename std::remove_reference<T>::type& a){
    //decltype(a)::asdf;
    T::asdf;

    g(static_cast<T&&>(a));
    //g(a); //always lvalue
    //g(static_cast<decltype(a)>(a));
}

template <typename T, typename U = T&&>
//void myForward(T&& a){
void myForward(typename std::remove_reference<T>::type&& a){
    //decltype(a)::asdf;
    T::asdf;

    g(static_cast<T&&>(a));
    //g(a); //always lvalue
    //g(static_cast<decltype(a)>(a));
}

template <typename Arg>
void h(Arg&& univRef){
    myForward<Arg>(univRef);
}

int main(){
    int a=3;
    //auto&& b = a;
    auto&& b = std::move(a);

    //int && rvalueRef = std::move(a);
    int && rvalueRef = [&](){return a;}();
    g(a);
    g(rvalueRef);
    //g(std::move(a));

    MyS mys{3};
    
    //g(std::forward<decltype(rvalueRef)>(rvalueRef));
    //g(myf(a));

    //get sht on :) 
    //i love C++
    g(mys.a);
    //g([&]() -> int&&{ return static_cast<int&&>(mys.a);}());
    g(std::forward<int&> (rvalueRef));
    g(std::forward<int&&> (rvalueRef));

        /*
    myForward<int&>(rvalueRef);//lvalue -> lvalue
    myForward<int&&>(std::move(rvalueRef));//rvalue -> rvalue

    myForward<int&>(3);//rvalue -> lvalue NOTE: this SHOULDN'T be allowed for std::forward ... cannot convert rvalue to lvalue
    myForward<int&&>(rvalueRef); //lvaue -> rvalue

    myForward<const int&>(rvalueRef);//lvalue -> lvalue //static_cast compiler error
    myForward<const int&&>(std::move(rvalueRef));//rvalue -> rvalue //static_cast compiler error

    //const int ci=2;
    //myForward<const int&>(ci);//lvalue -> lvalue //static_cast compiler error
    //myForward<const int&&>(std::move(ci));//rvalue -> rvalue //static_cast compiler error
    */

    h(rvalueRef);
    h(3);
    h<int&&> (3);
}
/*

template< class int&  >
constexpr int& && forward( std::remove_reference_t<int& >& t ) noexcept;
===>
template< class int&  >
constexpr int& forward( int& t ) noexcept;


template< class T >
constexpr T&& forward( std::remove_reference_t<T>&& t ) noexcept;
*/
