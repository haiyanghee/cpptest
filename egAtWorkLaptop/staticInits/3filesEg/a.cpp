#include "b.h"
#include "a.h"
#include <iostream>


C* A::initA(){
    my_c.printVectSize();
    my_c.initC();
    my_c.printVectSize();
    return &my_c;
}

void A::printVectSize(){
    my_c.printVectSize();
}
//static initialize to empty vector
C A::my_c;
