#pragma once
#include <vector>
#include <string>
#include "c.h"

struct A{
public:
    static std::vector<int>* initA();
    static void printVectSize();
    static std::vector<int> my_static_vect;
};

    //extern std::vector<int> my_static_vect;
