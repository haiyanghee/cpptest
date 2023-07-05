#include <bits/stdc++.h>

struct A{
    virtual void f() { std::cout<<"in A\n";}
};

struct B : public A{
    void f() override { std::cout<<"in B\n";}

    std::unique_ptr<B> member;
};


void g(std::unique_ptr<const B>& a){
    //g(*tmp);
}

void h(const char* a){ }

template <typename T>
void j(T const a){ }


template<unsigned int N>
void jjj(){ std::cout<<3<<"\n";}

template<int N>
void jj(){ jjj<N>();}

int main(){
    std::unique_ptr<B> b = std::make_unique<B>();
    g(b);

    char* a;
    h(a);
    //j(a);
    //j<const char*>(a);

    A aa;
    j(aa);

    jj<3L>();
}
