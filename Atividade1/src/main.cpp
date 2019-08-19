#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>
#include <vector>

#include "experimento.hpp"
#include "log.hpp"
#include "sqrt.hpp"
#include "sum.hpp"
#include "pow3.hpp"
#include "pow3mult.hpp"

#define MAX_SIZE 1000

int main(int argc, const char *argv[]){
    //Output Data File
    std::ofstream myfile;
    std::string fileName  = argv[0] + 2;
    std::string extension = ".json";
    
    myfile.open(fileName + extension);
    Json::Value obj;
    
    std::vector<std::pair<double, double>> times;

    //Instance of the experiments
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
    
    //Run experiments
    for (auto e : le)
        for(int i = 0; i < MAX_SIZE; i++){

            e->n = MAX_SIZE;
            e->gera_entrada(); 
            
            times.push_back(e->run());
            
            if(e->duration() < 0.1)
                std::cout << e->name << "_" << i << std::endl;
        }
    
    //Save data to file
    for (auto i = times.begin(); i != times.end(); ++i){
        obj["Mean"].append(std::get<0>(*i));
        obj["STD"].append(std::get<1>(*i));
    }

    myfile << obj;
    myfile.close();
}