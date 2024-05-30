#pragma once

#include <vector>
#include <string>
#include <iostream>

struct A{
public:
    static std::vector<int>* initA();
    static void printVectSize();
    static std::vector<int> my_static_vect;
};

struct B{
    B();
};
