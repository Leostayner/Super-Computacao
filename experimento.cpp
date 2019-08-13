#include "experimento.hpp"
#include <iostream>
#include <chrono>

Experimento::~Experimento() 
{ 
    delete []vec; 
} 

double* Experimento::gera_entrada(){
    vec = new double[n];
    for(int i = 0; i < n; ++i)
        vec[i] = (double) (rand() %41)/10;
    
    return vec;
}

double Experimento::duration(){
    return time;
}

void Experimento::run(){
    auto start = std::chrono::high_resolution_clock::now();
    experiment_code();
    auto end   = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count();    
    time = end;
}

