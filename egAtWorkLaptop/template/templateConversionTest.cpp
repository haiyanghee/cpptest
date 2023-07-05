#include <iostream>
#include <type_traits>

template <typename T> 
struct IdType{ using type = T; };

/*
template <typename T> 
void f(T& arg){ 
    //using type = T; 
    template <T mask>
    struct F{

    };

};
*/

template <typename T> 
struct F{ 
    using type = T; 
    F(T& m) : m_in(m){}

    template<T mask> void setBitmask(){

      m_in |= mask;
    }
private:
    T& m_in;
};

template <typename T> 
struct G{ 
    using type = T; 
    //can't do G::setBitmask<6942>(a);... need give G type
    template<T mask> static void setBitmask(T& m_in){
      m_in |= mask;
    }
};

template <typename T, T mask> void setBitmask(T &bitmask)        
{                                                                                  
    T::asdf;
  bitmask |= mask;                                                                 
}

template <typename T, typename U> void setBitmaskArg(T &bitmask, U arg){
    T a{arg};
}




int main(){
    unsigned short a=3;
    //setBitmask<decltype(a),69420>(a);
    setBitmask<decltype(a),6942>(a);

    setBitmask<unsigned short,69420>(a);

    //setBitmaskArg(a,69420);

    //F(a).setBitmask<69420>();
    F(a).setBitmask<6942>();
    //G::setBitmask<6942>(a);
}
