#include <iostream>
//#include <type_traits>

namespace detail {
 
template <class T>
struct type_identity { using type = T; 
    using WT = int;
    void f(){std::cout<<"in type id f()\n";}
}; // or use std::type_identity (since C++20)



template <class T
//, class U = T& 
//,class B = typename U::what
> // Note that `cv void&` is a substitution failure
type_identity<T&> try_add_lvalue_reference(int) {
    T::what;
        std::cout<<"I wS?\n";
return {};
}
template <class T, class U = T

, class B = typename U::what

> // Handle T = cv void case
type_identity<T> try_add_lvalue_reference(...)  {
    T::asdf;
    std::cout<<"I was in wdff\n";

return {};
}
 
template <class T>
auto try_add_rvalue_reference(int) -> type_identity<T&&>;
template <class T>
auto try_add_rvalue_reference(...) -> type_identity<T>{
    T::asdf;
}
 
} // namespace detail
 
template <class T>
struct madd_lvalue_reference
    : decltype(detail::try_add_lvalue_reference<T>(1)) {};
 
template <class T>
struct madd_rvalue_reference
    : decltype(detail::try_add_rvalue_reference<T>(69)) {};
 
int main()
{
   //using nonref = int;
   //using lref = typename madd_lvalue_reference<nonref>::type;
   //using rref = typename madd_rvalue_reference<nonref>::type;

   //detail::try_add_lvalue_reference<void>(1);
   using WW = decltype(detail::try_add_lvalue_reference<void>(1));
   using voidref =  madd_lvalue_reference<void>::type;

    //WW::dedcl;

    madd_lvalue_reference<void> a;
    //a::type;
    detail::type_identity<void> ti;
 
    //std::cout<< std::is_reference_v<voidref> << '\n';
 /*
   std::cout << std::boolalpha
             << std::is_lvalue_reference<nonref>::value << '\n'
             << std::is_lvalue_reference<lref>::value << '\n'
             << std::is_rvalue_reference<rref>::value << '\n'
             << std::is_reference_v<voidref> << '\n';
             */
}
