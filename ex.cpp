#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

#include "experimento.hpp"
#include "log.hpp"
#include "sqrt.hpp"
#include "sum.hpp"
#include "pow3.hpp"
#include "pow3mult.hpp"

#define MAX_SIZE 4

int main(){
    //std::ofstream myfile;
    //myfile.open("data.json");
    //Json::Value obj;
    
    Log  lg;
    Sqrt sq;
    Sum  sm;
    Pow3 pw3;
    Pow3Mult pw3m;

    Experimento *e1 = &lg;
    Experimento *e2 = &sq;
    Experimento *e3 = &sm;
    Experimento *e4 = &pw3;
    Experimento *e5 = &pw3m;
    
    Experimento *le[5] = {e1, e2, e3, e4, e5};

    for(int i = 0; i < MAX_SIZE; i++){

        for (auto e : le){ 
            e->n = MAX_SIZE;

            e->gera_entrada(); 
            e->run();
            e->duration();
            e->~Experimento();
        }
    }

    //myfile << obj;
    //myfile.close();
}