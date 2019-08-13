#ifndef EXEMPLO_H
#define EXEMPLO_H

class Experimento{

    public:
        
        int n;
        double *vec;
        double time;

        double* gera_entrada();
        double  duration();
        ~Experimento();

        virtual void experiment_code(){};
        void run();
};

#endif
