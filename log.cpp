#include <iostream>
#include <math.h>
#include "log.hpp"

void Log::experiment_code(){
    for(int i = 0; i < n; ++i)
        vec[i] = log(vec[i]); 
}