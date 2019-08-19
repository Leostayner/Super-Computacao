#include "sum.hpp"
#include <iostream>
#include <string>

Sum::Sum(std::string _name){name = _name;}

void Sum::experiment_code(){
    double tmp = 0;
    for (int i = 0; i < n; ++i)
        tmp += vec[i];
}