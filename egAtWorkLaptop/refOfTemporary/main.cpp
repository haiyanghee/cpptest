#include "stdio.h"

int f(){ return 69; }
int main(){
    // int* a = &f();
    // const int* aa = &f();
     int& a = f();
     const int& aa = f();
}
