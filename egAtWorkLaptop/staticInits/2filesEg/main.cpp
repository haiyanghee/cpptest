#include "a.h"
#include "b.h"
#include <iostream>

//B myb; //check in b.h for making it static member var

int main(){
    std::cout<<"in main, printing vectsize: \n";
    A::printVectSize();
}
