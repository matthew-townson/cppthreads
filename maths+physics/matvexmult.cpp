#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <mutex>
#include <omp.h>

#define M 3
#define N 2

void matvexmult() {
    srand(time(0));
    int vector[M], matrix[N][M], newmat[N][M];

    // init vector values
    for(int i = 0; i < M; i++) {
        vector[i] = rand() % 6;
    }

    // init matrix values
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 6;
        }
    }

    // print initial matrix and vector
    for(int i = 0; i < M; i++) {
        std::cout << "[ " << matrix[i][0] << " , " << matrix[i][1] << " ]   " << "   [" << vector[i] << "]" << std::endl;
    }

    // mult values
    #pragma omp parallel for
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            newmat[i][j] = matrix[i][j] * vector[i];
        }
    }

    for(int i = 0; i < M; i++) {
        std::cout << "[ " << newmat[i][0] << " , " << newmat[i][1] << " ]" << std::endl;
    }


}

int main() {
    matvexmult();
}