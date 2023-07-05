#include <stdio.h>
#include "header.h"
//const char*const  HI = "HI";
using namespace W;

namespace W{

void f(){
    printf("IN F(), address of HI is %p\n", HI);
}
}
