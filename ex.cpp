// g++ -std=c++11 ex5.cpp -ljsoncpp

#include <iostream>
#include <math.h>
#include <chrono>
#include <sstream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

#define MAX_SIZE 4

using namespace std::chrono;

double * gera_vetor(int n){
    double *vec = new double[n];
    for(int i = 0; i < n; ++i){
        vec[i] = (double) (rand() %41)/10;
        std::cout << vec[i] << std::endl;
    }
    return vec;
}

void log(double *vec, int n){
    std::cout<< "\nLOG" << std::endl;
    for(int i = 0; i < n; ++i)
        std::cout << log(vec[i]) << std::endl; 

}

void sqrt(double *vec, int n){
    std::cout<< "\nSQRT" << std::endl;
    for(int i = 0; i < n; ++i)
        std::cout << sqrt(vec[i]) << std::endl;
}

void pow3(double *vec, int n){
    std::cout<< "\nPOW3" << std::endl;
    for(int i = 0; i < n; ++i)
        std::cout << pow(vec[i], 3) << std::endl;

}

void pow3mult(double *vec, int n){
    std::cout<< "\nPOW3MULT" << std::endl;
    for(int i = 0; i < n; ++i)
        std::cout << vec[i] * 3 << std::endl;
}

double sum(double *vec, int n){
    //std::cout<< "\nSUM" << std::endl; 
    double tmp = 0;
    for (int i = 0; i < n; ++i)
        tmp += vec[i];

    std::cout << tmp << std::endl;;
}

int main(){

    std::ofstream myfile;
    myfile.open("data.json");
    
    Json::Value obj;

    std::string name = "";

    for(int n = 1; n < MAX_SIZE; ++n){
        //std::cout << "N:" << n << std::endl;
        double *vec = gera_vetor(n);
        
        for(int i = 0; i < 5; ++i){
            auto start = high_resolution_clock::now();
            
            if     (i == 0) {log(vec, n);       name = "log";}
            else if(i == 1) {sqrt(vec, n);      name = "sqrt";}
            else if(i == 2) {pow3(vec, n);      name = "pow3";}
            else if(i == 3) {pow3mult(vec, n);  name = "pow3mult";}
            else if(i == 4) {sum(vec, n);       name = "sum";}
            
            auto end   = duration_cast<duration<double>>(high_resolution_clock::now() - start).count();
            //std::cout << "Tempo de Execução: " << end << "segundos" << std::endl;
            obj[name][n - 1]["Size"] = n;
            obj[name][n - 1]["Time"] = end;
        }
    }

    myfile << obj;
    myfile.close();
}