#include <bits/stdc++.h>

template <typename ... Arg>
void ff(Arg&& ... ){}

template <typename ... Arg>
void f(Arg&& ... args){
    //new int(args ...);
    ff(std::forward<Arg::asdf>(args)...);
}

int main(){
    std::string a="123e";
    f(a);
}
