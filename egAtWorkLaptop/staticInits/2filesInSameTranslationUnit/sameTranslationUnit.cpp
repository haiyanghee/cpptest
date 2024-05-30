#include "sameTranslationUnit.h"


//If you put it at the top, its bad (for some reason)
//B myb;

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

//NOTE: the order on where we put this doesn't matter, as this should be part of Unordered dynamic initialization (static member var)
std::vector<int> A::my_static_vect;

//----------------------

B::B(){
    std::cout<<__func__<<": in B's constructor = \n";
    auto my_static_ptr = A::initA();
    std::cout<<__func__<<": finished with vect size = \n";
    std::cout<<__func__<<": vect size = "<< my_static_ptr->size()<<"\n";
}

//if you put it at the bottom, its good (for some reason)
//B myb;
