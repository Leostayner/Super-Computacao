#include <iostream>
#include <math.h>
#include "sqrt.hpp"
#include <string>

Sqrt::Sqrt(std::string _name){name = _name;}

void Sqrt::experiment_code(){
    for(int i = 0; i < n; ++i)
        vec[i] = sqrt(vec[i]);
}