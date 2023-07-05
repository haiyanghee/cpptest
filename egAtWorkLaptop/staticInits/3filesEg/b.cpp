#include "b.h"
#include "a.h"
#include <iostream>

C* B::my_static_ptr=nullptr;

B::B(){
    std::cout<<__func__<<": in B's constructor = \n";
    my_static_ptr = A::initA();
    std::cout<<__func__<<": finished with vect size = \n";
    my_static_ptr->printVectSize();
}
