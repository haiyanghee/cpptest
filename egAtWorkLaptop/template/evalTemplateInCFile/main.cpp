#include "lib.h"

struct B{
public:
    double d=89;
};

template <int c>
void h(){
    c;
}

template <struct B b>
void g(){
    b.d;
}

int main(){
    //int a=3;
    //f(a);
    ff();


    constexpr B b{};
    g<b>();
}
