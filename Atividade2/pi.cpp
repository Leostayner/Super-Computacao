//g++ -O3 pi.cpp -o pi -fopenmp -lpthread

#include <iostream>
#include <chrono>
#include <thread>
#include <utility>
#include <omp.h>

#define NUM_THREADS 4
#define NUM_STEPS 100000000
 

using namespace std::chrono;


void partialPi(int start, int end, double step, double *lpi, int id){
    double x;
    
    for (int i = start; i < end; i++) {
        x = (i + 0.5) * step;
        lpi[id] = lpi[id] + 4.0 / (1.0 + x * x);
    }
}


double pi_threads_raiz(long steps){
    std::thread *lt = new std::thread[NUM_THREADS];
    double step = 1.0 / (double)NUM_STEPS;

    double *lpi = new double[NUM_THREADS];
    double  pi;;

    for(int i=0; i<NUM_THREADS; ++i)
        lt[i] = std::thread(partialPi, int(i * NUM_STEPS/NUM_THREADS), int((i+1) * NUM_STEPS/NUM_THREADS), step, lpi, i);
        
    for(int i=0; i<NUM_THREADS; ++i)
        lt[i].join();

    for(int i=0; i<NUM_THREADS; ++i)
        pi += lpi[i];
    
    pi *= step;
    return pi;
}


double pi_seq(long steps){
    int i;
    double x, pi, sum = 0.0;
    double step = 1.0 / (double)steps;

    auto start_time = std::chrono::high_resolution_clock::now();
    for (i = 0; i < steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    return pi;
}


double pi_omp_parallel(long steps){
    double step = 1.0 / (double)NUM_STEPS;

    double *lpi = new double[NUM_THREADS];
    double  pi;
    
    #pragma omp parallel
    {
        for (int i = int(omp_get_thread_num() * NUM_STEPS/NUM_THREADS); i < int((omp_get_thread_num()+1) * NUM_STEPS/NUM_THREADS); i++) {
            double x = (i + 0.5) * step;
            lpi[omp_get_thread_num()] = lpi[omp_get_thread_num()] + 4.0 / (1.0 + x * x);
        }    
    }
    
    for(int i=0; i<NUM_THREADS; ++i)
        pi += lpi[i];
    
    pi *= step;
    return pi;
}

double pi_omp_parallel_local(long steps){
    double step = 1.0 / (double)NUM_STEPS;

    double *lpi = new double[NUM_THREADS];
    double  pi;
    
    #pragma omp parallel
    {   
        double sum = 0;
        for (int i = int(omp_get_thread_num() * NUM_STEPS/NUM_THREADS); i < int((omp_get_thread_num()+1) * NUM_STEPS/NUM_THREADS); i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        lpi[omp_get_thread_num()] = sum;    
    }
    
    for(int i=0; i<NUM_THREADS; ++i)
        pi += lpi[i];
    
    pi *= step;
    return pi;
}

double pi_omp_parallel_atomic(long steps){
    double step = 1.0 / (double)NUM_STEPS;
    double pi;
    
    #pragma omp parallel
    {
        double sum = 0;
        for (int i = int(omp_get_thread_num() * NUM_STEPS/NUM_THREADS); i < int((omp_get_thread_num()+1) * NUM_STEPS/NUM_THREADS); i++) {
            double x = (i + 0.5) * step;    
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp atomic
        pi += sum;    
    }
    
    pi *= step;
    return pi;
}

double pi_omp_parallel_critical(long steps){
    double step = 1.0 / (double)NUM_STEPS;
    double pi;
    
    #pragma omp parallel
    {
        double sum = 0;
        for (int i = int(omp_get_thread_num() * NUM_STEPS/NUM_THREADS); i < int((omp_get_thread_num()+1) * NUM_STEPS/NUM_THREADS); i++) {
            double x = (i + 0.5) * step;    
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        pi += sum;    
    }
    
    pi *= step;
    return pi;
}

double pi_omp_parallel_critical_errado(long steps){
    double step = 1.0 / (double)NUM_STEPS;

    double *lpi = new double[NUM_THREADS];
    double  pi;
    
    #pragma omp parallel
    {
        for (int i = int(omp_get_thread_num() * NUM_STEPS/NUM_THREADS); i < int((omp_get_thread_num()+1) * NUM_STEPS/NUM_THREADS); i++) {
            double x = (i + 0.5) * step;
            #pragma omp critical
            lpi[omp_get_thread_num()] = lpi[omp_get_thread_num()] + 4.0 / (1.0 + x * x);
        }    
    }
    
    for(int i=0; i<NUM_THREADS; ++i)
        pi += lpi[i];
    
    pi *= step;
    return pi;
}


double pi_omp_parallel_for(long steps){
    double step = 1.0 / (double)NUM_STEPS;
    double pi;
    
    #pragma omp parallel
    #pragma omp for reduction(+:pi)
    for (int i = 0; i < NUM_STEPS; ++i) {
        double x = (i + 0.5) * step;    
        pi += 4.0 / (1.0 + x * x);
    }

    pi *= step;
    return pi;
}


std::pair<double, double> run(int selectFunction){
    double pi;
    auto start_time = high_resolution_clock::now();
    
    if(selectFunction == 1)
        pi = pi_threads_raiz(NUM_STEPS);
    
    else if(selectFunction == 2)
        pi = pi_seq(NUM_STEPS);

    else if(selectFunction == 3)
        pi = pi_omp_parallel(NUM_STEPS);
    
    else if(selectFunction == 4)
        pi = pi_omp_parallel_local(NUM_STEPS);
    
    else if(selectFunction == 5)
        pi = pi_omp_parallel_atomic(NUM_STEPS);

    else if(selectFunction == 6)
        pi = pi_omp_parallel_critical(NUM_STEPS);
        
    else if(selectFunction == 7)
        pi_omp_parallel_critical_errado(NUM_STEPS);

    else
        pi_omp_parallel_for(NUM_STEPS);
    
    

    auto runtime = duration_cast<duration<double>>(high_resolution_clock::now() - start_time).count();

    std::cout << "O valor de pi calculado com " << NUM_STEPS << " passos levou ";
    std::cout << runtime << " segundo(s) e chegou no valor : ";
    std::cout.precision(17);
    std::cout << pi << std::endl;


    return std::make_pair(pi, runtime);
}


int main() {
    std::pair<double, double> result;

    result = run(1);
    result = run(2);
    result = run(3);
    result = run(4);
    result = run(5);
    result = run(6);
    result = run(7);
    result = run(8);
}