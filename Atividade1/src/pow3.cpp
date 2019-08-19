#include <iostream>
#include <math.h>
#include "pow3.hpp"
#include <string>

Pow3::Pow3(std::string _name){name = _name;}

void Pow3::experiment_code(){
    for(int i = 0; i < n; ++i)
        vec[i] = pow(vec[i], 3);
}