#include <vector>
#include <iostream>
#include <stdio.h>

template <typename T>
void myprintRvalRef(T&& uniRef){ std::cout<<"in myprintRvalRef, uniRef = "<< uniRef<<"\n"; }
template <typename T>
void myprintLvalRef(T& uniRef){ std::cout<<"in myprintLvalRef, uniRef = "<< uniRef<<"\n"; }
template <typename T>
void myprintConstLvalRef(const T& uniRef){ std::cout<<"in myprintConstLvalRef, uniRef = "<< uniRef<<"\n"; }

struct S{
    static constexpr const char* str = (const char*)"hello";
};

struct A{
    const char* v;
    A(const char* iv):v(iv){ printf("constructor (const char* iv) of A is called!\n");}
    A(const char& iv):v(&iv){ printf("constructor (const char& iv) of A is called!\n");}
    A(const char* const * iv):v(*iv){ printf("constructor (const char** iv) of A is called!\n");}
};
std::ostream& operator<<(std::ostream& s, const A& a){ return s << a.v; }

//If you uncomment any of the commented lines, you will get compiler error with `-std=c++14`
//this is apparently fixed in c++17...
int main(){
    printf("via printf: %s\n", S::str);
    A a{S::str};
    A aa{*S::str};
    //A aaa{&S::str};

    myprintRvalRef(A{S::str});
    //myprintRvalRef(S::str);
    //myprintLvalRef(S::str);
    //myprintConstLvalRef(S::str);
}
