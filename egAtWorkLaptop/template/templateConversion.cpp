#include <iostream>

struct A{
    unsigned char a[3];
};

template <typename T>
struct deduced_type;

template <typename T, size_t N>
void f(const T (&arr)[N], T a) {}

template <typename T, typename U, size_t N>
void g(const T (&arr)[N], U a) {
    f(arr, (T)a);
}

template<typename T, T a>
void h(){}

//template <size_t N>
//void f(const std::decay<decltype(A::a[0])>::type (&arr)[N], std::decay<decltype(A::a[0])>::type a) {
//    //deduced_type<std::decay<decltype(A::a[0])>::type> b;
//}

int main(){
    A a;
    //f(a.a, 3);
    //f(a.a, (unsigned char)3);

    //g(a.a, 3);
    h<unsigned char, 3>();
}
