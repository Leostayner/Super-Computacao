#include "sumsimd.hpp"
#include <iostream>
#include <string>
#include <x86intrin.h>

SumSIMD::SumSIMD(std::string _name){name = _name;}

void SumSIMD::experiment_code(){
    double tmp = 0;
    
    for(int i = 0; i < n; ++i)
        __m256 odds   = _mm256_set_ps(1.0,3.0,5.0,7.0,9.0,11.0,13.0,15.0);

    
    for (int i = 0; i < n; ++i)
        tmp += vec[i];
}