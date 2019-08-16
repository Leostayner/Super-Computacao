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
    std::ofstream myfile;
    myfile.open("data.json");
    Json::Value obj;
 
    Log  lg("Log");
    Sqrt sq("Sqrt");
    Sum  sm("Sum");
    Pow3 pw3("Pow3");
    Pow3Mult pw3m("Pow3Mult");

    Experimento *e1 = &lg;
    Experimento *e2 = &sq;
    Experimento *e3 = &sm;
    Experimento *e4 = &pw3;
    Experimento *e5 = &pw3m;
    
    Experimento *le[5] = {e1, e2, e3, e4, e5};

    for(int i = 0; i < MAX_SIZE; i++){

        for (auto e : le){ 
            double min = pow(10,10); 
            double max = 0;

            e->n = MAX_SIZE;
            e->gera_entrada(); 
            
            for(int i = 0; i < 10; i++){
                e->run();
                
                if(min > e->duration())
                    min = e->duration();
                
                if(max < e->duration())
                    max = e->duration();
            }
            
            obj[e->name][i] = (max - min) / 2;
            
            if(e->duration() < 0.1)
                std::cout << e->name << "_" << i << std::endl;    

            e->~Experimento();
        }
    }

    myfile << obj;
    myfile.close();
}