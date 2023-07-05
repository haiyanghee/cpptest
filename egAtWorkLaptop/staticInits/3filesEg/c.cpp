#include "c.h"
#include <iostream>


C::C(){
    std::cout<<__func__<<": C constructor called\n";
}

void C::initC(){
    std::cout<<__func__<<": will clear and resize vector\n";
    //my_static_vect.clear();
    my_static_vect.resize(1000);
    std::cout<<__func__<<": finished with vect size = "<< my_static_vect.size()<<"\n";
}

void C::printVectSize(){
    std::cout<<__func__<<": vect size = "<< my_static_vect.size()<<"\n";
}
