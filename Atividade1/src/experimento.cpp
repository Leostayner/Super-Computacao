#include "experimento.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <random>
#include <utility> 

#define RDMN 5.0
#define RDST 0.5

using namespace std::chrono; 

std::vector<double> Experimento::gera_entrada(){
    std::mt19937 generator;
    std::normal_distribution<double> normal(RDMN, RDST);

    for (int i = 0; i < n; ++i)    
        vec.push_back(normal(generator));

    return vec;
}

double Experimento::duration(){
    return time;
}

std::pair<double, double> Experimento::run(){
    std::array<double, 10> values;

    double mean = 0;
    double stdm;
    
    for(int i = 0; i < 10; i++){
        auto start = high_resolution_clock::now();
        experiment_code();
        auto end   = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();    
        
        values[i]  = end;
        mean       += end;
    }

    mean  = mean / 10;
    for(auto value: values){
        stdm += pow(value - mean, 2);
    }

    stdm = sqrt(stdm/10);    
    time = mean;

    std::pair<double, double> retVal(mean, stdm);
    return retVal;
}

bool Experimento::operator<(const Experimento& e){    
    if(this->time < e.time && this->n == e.n)
        return true;
    
    return false;
}

bool Experimento::operator<(double d){    
    return  this->time < d;
}
