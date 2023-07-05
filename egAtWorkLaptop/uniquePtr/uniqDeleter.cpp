#include <memory>
#include <iostream>


using unique_void_ptr = std::unique_ptr<void, void(*)(void const*)>;

template<typename T>
auto unique_void(T * ptr) -> unique_void_ptr
{
    return unique_void_ptr(ptr, [](void const * data) {
         T const * p = static_cast<T const*>(data);
         std::cout << "{" << *p << "} located at [" << p <<  "] is being deleted.\n";
         delete p;
    });
}

template<typename T>
struct F{
    using M = T;
    //F(){
    F(M p){
        std::cout<<"overload T* p\n";
    }
};

template<typename T>
struct F<T[]>{
    using M = T[];
    //F(){
    F(T* p){
        std::cout<<"overload T []\n";
    }
};

template<typename T, size_t N>
struct F<T[N]>{
    using M = T[];
    //F(){
    F(T* p){
        std::cout<<"overload T [N]\n";
    }
};


template<class T>
struct is_array  { 
    is_array(){
        std::cout<<"is arr false\n";
    }
};
 
template<class T>
struct is_array<T[]> { 
    is_array(){
        std::cout<<"is arr true\n";
    }
};


int main()
{
    auto p1 = unique_void(new int(959));
    //auto p2 = unique_void(new double(595.5));
    //auto p3 = unique_void(new std::string("Hello World"));
    auto p4 = unique_void(new int [69]);

    int a;
    int arr[3];

    F f{&a};
    //F ff{arr};
    F<decltype(arr)> fff{arr};
    F<int []> ffff{arr};

    //F <int*>f;
    ////F ff{arr};
    //F<decltype(arr)> fff;
}
