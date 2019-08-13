#include <iostream>
#include <math.h>
#include "sqrt.hpp"

void Sqrt::experiment_code(){
    for(int i = 0; i < n; ++i)
        vec[i] = sqrt(vec[i]);
}