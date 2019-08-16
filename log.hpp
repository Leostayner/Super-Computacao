#ifndef LOG_H
#define LOG_H

#include "experimento.hpp"

class Log: public Experimento{
    public:
        void experiment_code();
        Log(std::string);    
};

#endif
