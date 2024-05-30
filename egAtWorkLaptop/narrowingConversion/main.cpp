#include <cstddef>
#include <iostream>
#include <string>

// we will attempt to do narrowing conversion checks at compile time
//this is the same std::void_t definition introduced in C++17. Please refer to https://en.cppreference.com/w/cpp/types/void_t (note our gcc compilers are version >= 5, so no need to worry about CWG issue 1558, which is also mentioned in the reference)

template <typename...> using myvoid_t = void;
//template <typename... Args> using myvoid_t = std::void_t<Args...>;

template <typename From, typename To, typename = void> struct myIs_narrowing_conversion : std::true_type
{
};
//NOTE: brace initialization will detect narrowing conversions (https://en.cppreference.com/w/cpp/language/list_initialization#Narrowing_conversions)
//here we use SFINAE to with brace initialization to determine if we have a narrowing conversion
template <typename From, typename To>
struct myIs_narrowing_conversion<From, To, myvoid_t<decltype(To{ std::declval<From>() })>> : std::false_type
{
};


#ifndef __cpp_template_auto

template <typename From, From val, typename To, typename = void>
struct myIs_narrowing_conversionForValue : std::true_type
{
};
//NOTE: brace initialization will detect narrowing conversions (https://en.cppreference.com/w/cpp/language/list_initialization#Narrowing_conversions)
//here we use SFINAE to with brace initialization to determine if we have a narrowing conversion
template <typename From, From val, typename To>
struct myIs_narrowing_conversionForValue<From, val, To, myvoid_t<decltype(To{ val })>> : std::false_type
{
};

#else

//C++17 auto in template parameters
template <auto val, typename To, typename = void>
struct myIs_narrowing_conversionForValue : std::true_type
{
};
//NOTE: brace initialization will detect narrowing conversions (https://en.cppreference.com/w/cpp/language/list_initialization#Narrowing_conversions)
//here we use SFINAE to with brace initialization to determine if we have a narrowing conversion
template <auto val, typename To>
struct myIs_narrowing_conversionForValue<val, To, myvoid_t<decltype(To{ val })>> : std::false_type
{
    using ValueType = decltype(val);
};
#endif

template <typename From, typename To>
struct testDecltype : std::false_type
{
        //using From::a;
        //using To::a;
        //using F = decltype(std::declval<From>());
        //using F::a;
    using someRandomType = decltype(To{ std::declval<From>() });
};

struct A{
    int a;
    //A(int a):a(a){ //NOTE: int with int&& overload is ambiguous ...
    //but doesn't matter if constructor has side effects.. compiler will not actually construct the instance (because it's never used I guess)
    /*
    A(const int& a):a(a){
        std::cout<<"some side effect in A's constructor\n";
    }
    //A(int&& a):a(a){ std::cout<<"some side effect in A's move constructor\n"; }
    A(int&& ){ std::cout<<"some side effect in A's move constructor\n"; }
    */
    constexpr A(int&& a):a(a){} //for constructing A{} at compile time
};

struct B{
    double a;
    B(A a):a(a.a){
    //B(std::string ){
        std::cout<<"some side effect in B's constructor\n";
    }
};

int main(){
    testDecltype<int, A> w;


    //static_assert(!myIs_narrowing_conversion<int, char>::value, "can't convert int to char in general..");
    static_assert(!myIs_narrowing_conversion< char, int >::value, "can convert char to int in general..");
    static_assert(!myIs_narrowing_conversion< int, A >::value, "can convert int to A in general..");
    //static_assert(!myIs_narrowing_conversion< double, A >::value, "can convert int to A in general..");

    //static_assert(!myIs_narrowing_conversion< A, B>::value, "can convert int to A in general..");

#ifndef __cpp_template_auto
    static_assert(!myIs_narrowing_conversionForValue< char,1, int >::value, "can convert char to int in general..");
    static_assert(!myIs_narrowing_conversionForValue< int, 69, A >::value, "can convert int to A in general..");
    //static_assert(!myIs_narrowing_conversionForValue< B, B{{22}}, A >::value, "can convert int to A in general..");
#else
    static_assert(!myIs_narrowing_conversionForValue< 1, int >::value, "can convert char to int in general..");
    static_assert(!myIs_narrowing_conversionForValue< 69, A >::value, "can convert int to A in general..");
    //myIs_narrowing_conversionForValue< 69, A >::ValueType::asdf;

    //static_assert(!myIs_narrowing_conversionForValue< A{22}, B >::value, "can convert int to A in general.."); //this will compile with C++20, as it allows literal class non-template parameter
    //testDecltype<A, B> ww;
#endif

    static_assert(std::is_constructible<int, char>::value, "can't convert int to char in general..");
    static_assert(std::is_constructible<char, int>::value, "can't convert int to char in general..");
}
