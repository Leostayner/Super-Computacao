//g++ pi.cpp -lpthread
#include <iostream>
#include <chrono>
#include <thread>

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

void test(){
    std::cout << "a";
}


int main() {
    std::thread *lt = new std::thread[NUM_THREADS];
    double step = 1.0 / (double)NUM_STEPS;

    double *lpi = new double[NUM_THREADS];
    double  pi;;

    auto start_time = high_resolution_clock::now();

    for(int i=0; i<NUM_THREADS; ++i)
        lt[i] = std::thread(partialPi, int(i * NUM_STEPS/NUM_THREADS), int((i+1) * NUM_STEPS/NUM_THREADS), step, lpi, i);
        
    for(int i=0; i<NUM_THREADS; ++i)
        lt[i].join();

    for(int i=0; i<NUM_THREADS; ++i)
        pi += lpi[i];
    
    pi *= step;

    auto runtime = duration_cast<seconds> (high_resolution_clock::now() - start_time);

    std::cout << "O valor de pi calculado com " << NUM_STEPS << " passos levou ";
    std::cout << runtime.count() << " segundo(s) e chegou no valor : ";
    std::cout.precision(17);
    std::cout << pi << std::endl;

}