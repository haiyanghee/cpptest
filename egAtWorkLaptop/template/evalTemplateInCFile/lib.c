#include "lib.h"

template <typename A>
void f(A a){
    std::cout<<"f()" << a<<"\n";
}

void ff(){
    int a=240;
    f(a);
}
