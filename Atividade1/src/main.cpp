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

#define MAX_SIZE 10000000

int main(int argc, const char *argv[]){
    //Output Data File
    std::ofstream myfile;
    std::string fileName  = argv[0] + 9;
    std::string extension = ".json";
    
    myfile.open(fileName + extension);
    Json::Value obj;
    
    //Times Table
    std::map<std::string, std::vector<std::pair<double, double>>> table;

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
    for (auto e : le){
        for(int i = 1000; i < MAX_SIZE; i *= 10){
            e->n = i;
            e->gera_entrada(); 
            
            table[e->name].push_back(e->run());
            
            if(e->duration() < 0.1)
                std::cout << e->name << "_" << i << std::endl;
        }
    }
    
    //Save Table in File
    for (const auto& sm_pair : table)
        for (auto i = sm_pair.second.begin(); i != sm_pair.second.end(); ++i){
            obj[sm_pair.first]["Mean"].append(std::get<0>(*i));
            obj[sm_pair.first]["STD"].append(std::get<1>(*i));
        }

    myfile << obj;
    myfile.close();
}