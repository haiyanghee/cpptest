#include <iostream>
#include <string>

struct A{
    std::string str;
    ~A(){
        std::cout<<"A is destructed\n";
    }
};
struct B{
    int b;
};

enum mytype { isA, isB};

struct C{
    mytype type=isB;
    union Ses {
        Ses(): b(){ } //intentionally using b by default
        //Ses(): a(){ } 
        A a;
        B b;
        ~Ses() {};
    }u;
    
    C() = default;
    void destructCurType(){
        switch (type){
        case isA:
            u.a.~A();
            break;
        case isB:
            u.b.~B();
          break;
        }
    }
    ~C(){destructCurType();}
};

int main(){
    C c;
    c.type=isA;
    new (&c.u.a) A(); //apparently MUST do this
    //c.u.a= A{}; //this doesn't work!
    c.u.a.str="helllllo";
    std::cout<<" str = "<<c.u.a.str<<"\n";

    //if you want to switch, you technically should destruct A first
    c.destructCurType();
    new (&c.u.b) B(); //apparently MUST do this to switch member life time
    c.type=isB; //make sure to switch the type, so the destructor of C will be properly called after scope ends
    c.u.b.b = 3;
    std::cout<<" b = "<<c.u.b.b<<"\n";
}
