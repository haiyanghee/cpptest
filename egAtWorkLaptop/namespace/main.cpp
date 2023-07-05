#include <iostream>

namespace G{
    namespace A {
        void f(){ std::cout<<"in A::f()\n"; }
    };
    using namespace A;

    void g(){
        f();
    }

    namespace B {
        void f(){ std::cout<<"in B::f()\n"; }
        //void g();
    };
    using namespace B;
};

int main(){
    G::g();
    //f();
}
