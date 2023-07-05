#include <iostream>
#include "header.h"


//NOTE: glibc is automatically linked ....
//use -nodefaultlibs to test to explicitly link what you need
// g++ -nodefaultlibs -fPIC -Wl,--no-undefined -lstdc++ -lc ./main.cpp -o main.o
void g(){
    f();
    std::cout<<"ffff\n";
}
