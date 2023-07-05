#include <iostream>

/*
template <typename AnyVar>
void f(const AnyVar &a)
{
	//std::cout << " in f<AnyVar>(a)!\n";

    //if constexpr(false){
    //static_assert(false, "f is not valid overload!");
    static_assert(sizeof(AnyVar)==0, "f is not valid overload!");
    //}
}
*/

//template <typename AnyVar>
//void f(const AnyVar &a) = delete;


//template <typename AnyVar>
//void f(const AnyVar &a){
//    static_assert(false, "f is not valid specialization!");
//}

/*
template<typename S>
struct A{
    void g(S s) { std::cout<<"s = "<<s<<"\n";}

    template <typename T>
    inline static void f(const T &a){
    }

    template <>
    inline static void f(const int& a)
    {
        std::cout << " in f<int>(& a), a = "<<a<<"\n";
    }
};


int main()
{
    A<int> a;
	a.f(3);
    int* p;
    a.f(p);
    //f(2.3);
}
*/
struct A{

    template <typename T, typename A>
    inline static void f(const T &a, const A &b){
    }

    template <typename T>
    inline static void f(const T &a, const int &b){
        std::cout<<"b = "<<b<<"\n";
    }

    //uncomment to get compiler error
    //template <>
    //inline static void f(const int &a, const int &b){
    //    std::cout<<"a = "<<a<<",b = "<<b<<"\n";
    //}
};


int main()
{
    A a;
	a.f(1,3);
    int* p;
    //a.f(1,p);
    //f(2.3);
}
