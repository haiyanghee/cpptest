#include "sameTranslationUnit.h"

//NOTE: if you define `B myb` inside sameTranslationUnit.cpp (so its in same translation unit)
B myb;
extern B myb;

int main(){
    //B localb;
    std::cout<<"in main, printing vectsize: \n";
    A::printVectSize();
}
