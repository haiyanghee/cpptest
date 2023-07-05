#include <iostream>

//template<typename T> constexpr bool always_false = false;
template<class> inline constexpr bool always_false_v = false;

template<int val>
void f(){
    if constexpr (val == 3){

    }
    else{
       // static_assert(sizeof(T) == 0, "badd");
        static_assert(always_false_v<int>, "badd");
    }
}

template <class>
constexpr bool dependent_false = false; // workaroud before CWG2518/P2593R1
 
//template<T val, typename T>
template<typename T, T val>
void g(){
    if constexpr (val == 3){}
    else{ static_assert(always_false_v<int>, "badd"); }
}

struct A{
    int m;
    struct {
        int c;
        class D {
            public:
            int e;
        }d;
    } b;
};

//template<decltype(A.m) val> <--- BAD
//template<decltype(A::m) val>
//template<decltype(A::b::c) val> <--- BADD
//template<decltype(A::b.c) val>
template<decltype(A::b.d.e) val>
void h(){
    using T = int;
    if constexpr (val == 3){}
    else{ static_assert(always_false_v<void>, "badd"); }
    //else{ static_assert(false, "badd"); }
}

//struct B{
//    static_assert(always_false_v<void>, "asdf"); //BAD
//};

template<typename T>
struct BB{
    static_assert(always_false_v<T>, "asdf"); //OK
};

int main(){
    //f<3>();
    //g<decltype(3),3>();

    h<3>();
}
