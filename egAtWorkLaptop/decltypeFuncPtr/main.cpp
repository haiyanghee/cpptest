#include <stdio.h>

void f(int a){
    printf("in f, a = %d\n", a);
}

using g = decltype(f);
using gg = decltype(&f);

g wdf;

int main(){

    wdf(1);

    gg(2);
}
