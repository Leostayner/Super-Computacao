#ifndef EXEMPLO_H
#define EXEMPLO_H

#include <string>
#include <vector>
#include <utility>

class Experimento{

    public:
        
        int n;
        double time;
        std::vector<double> vec;
        std::string name;

        std::vector<double> gera_entrada();
        double  duration();
        
        std::pair<double, double> run();
        virtual void experiment_code(){};
        
        bool operator<(const Experimento&);
        bool operator<(double);
};

#endif
