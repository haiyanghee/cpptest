#include <stdio.h>
struct A{
    virtual void f(){ printf("A::f()\n"); }
};

struct B : public A{
    //void f() override { printf("B::f()\n"); }
    virtual void f() { printf("B::f()\n"); }
};

struct C : public B{
    void f() override { printf("C::f()\n"); }
};

int main(){
    C c;
    c.f();
}
