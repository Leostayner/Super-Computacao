#include <iostream>
#include "pow3mult.hpp"
#include <string>

Pow3Mult::Pow3Mult(std::string _name){name = _name;}

void Pow3Mult::experiment_code(){
    for(int i = 0; i < n; ++i)
        vec[i] = vec[i]*3;
}