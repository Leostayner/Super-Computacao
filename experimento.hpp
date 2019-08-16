#ifndef EXEMPLO_H
#define EXEMPLO_H

#include <string>

class Experimento{

    public:
        
        int n;
        double *vec;
        double time;
        std::string name;

        double* gera_entrada();
        double  duration();
        ~Experimento();

        virtual void experiment_code(){};
        void run();

        bool operator<(const Experimento&);
        bool operator<(double);
};

#endif
