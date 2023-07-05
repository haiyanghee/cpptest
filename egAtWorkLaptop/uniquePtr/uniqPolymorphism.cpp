#include <memory>
#include <stdio.h>

struct A{
    virtual ~A(){
        printf("destructing in A\n");
    }
};

struct B : public A{
    virtual ~B(){
        printf("destructing in B\n");
    }
};

int main(){
    std::unique_ptr<A> ptr;
    ptr = std::unique_ptr<B>(new B()); //can convert pointer
    //ptr = std::unique_ptr<int>(new int()); //can't convert pointer
}
