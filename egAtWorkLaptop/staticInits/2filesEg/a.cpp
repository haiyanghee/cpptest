#include "b.h"
#include "a.h"
#include <iostream>


std::vector<int>* A::initA(){
    std::cout<<__func__<<": will clear and resize vector\n";
    //my_static_vect.clear();
    my_static_vect.resize(1000);
    std::cout<<__func__<<": finished with vect size = "<< my_static_vect.size()<<"\n";
    return &my_static_vect;
}

void A::printVectSize(){
    std::cout<<__func__<<": vect size = "<< my_static_vect.size()<<"\n";
}
//static initialize to empty vector
std::vector<int> A::my_static_vect;
//std::vector<int> my_static_vect;
