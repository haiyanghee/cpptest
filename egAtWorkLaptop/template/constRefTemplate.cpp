#include "stdio.h"
#include <iostream>

/*
template <typename T> void test_func(const T &a){
    (*a)++; 
}

int main() {
    // 1st case
    int i = 1;
    test_func(&i); 

    //const int* a = &i;
    int* const a = &i;
    (*a)++; 

    printf("i changed to %d\n", i);
    
    // 2nd case
    const int* cPtr = &i; 
    test_func(cPtr); 
}
*/


template <class T>
void func(const T&&) {
  std::cout<<"in const rvalue... "<<__PRETTY_FUNCTION__<<"\n";
}

template <class T>
void func(T&&) {
  std::cout<<"in rvalue "<<__PRETTY_FUNCTION__<<"\n";
}

//https://stackoverflow.com/questions/9813316/print-template-typename-at-compile-time
template <class T>
void func(const T&) {
    //typedef typename T::nothing X;
  std::cout<<"in lvalue "<<__PRETTY_FUNCTION__<<"\n";
}

int main()
{
    double n=3;
    func<double>(n);
    func(n);

    func<const int&&>(3);

    const double b = 5;
    func<const double&>(b);

    //const double& const a = b;
    func(b);
}
