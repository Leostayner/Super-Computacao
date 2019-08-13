#include <iostream>
#include <math.h>
#include "pow3.hpp"

void Pow3::experiment_code(){
    for(int i = 0; i < n; ++i)
        vec[i] = pow(vec[i], 3);
}