#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <mutex>
#include <omp.h>

#define VECTSIZE 4
#define MULTBY 2

void SAXPY() {
    srand(time(0));
    int vector1[VECTSIZE], vector2[VECTSIZE], newvect[VECTSIZE];

    // init vector values
    for(int i = 0; i < VECTSIZE; i++) {
        vector1[i] = rand() % 6;
    }

    for(int i = 0; i < VECTSIZE; i++) {
        vector2[i] = rand() % 6;
    }

    // print initial vectors
    for(int i = 0; i < VECTSIZE; i++) {
        std::cout << "[" << vector1[i] << "] " << " [" << vector2[i] << "]" << std::endl;
    }

    // multiply
    #pragma omp parallel for
    for(int i = 0; i < VECTSIZE; i++) {
        newvect[i] = (MULTBY * vector1[i]) + vector2[i];
    }

    // print final vector
    std::cout << "FINAL VECTOR:" << std::endl;
    for(int i = 0; i < VECTSIZE; i++) {
        std::cout << "[" << newvect[i] << "]" << std::endl;
    }
}

int main() {
    SAXPY();
}