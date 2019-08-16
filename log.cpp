#include <iostream>
#include <math.h>
#include "log.hpp"
#include <string>

Log::Log(std::string _name){name = _name;}

void Log::experiment_code(){
    for(int i = 0; i < n; ++i)
        vec[i] = log(vec[i]); 
}