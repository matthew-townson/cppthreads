#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>

/*
3 threads, must be in order 2, 1, 3
*/

std::binary_semaphore
    semWaitFor2{0},
    semWaitFor1{0};

void randWait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
}

void t1Print() {
    semWaitFor2.acquire();
    std::cout << "thread1 acquire" << std::endl;
    randWait();
    std::cout << "thread1 release" << std::endl;
    semWaitFor1.release();
}

void t2Print() {
    randWait();
    std::cout << "thread2 acquire" << std::endl;
    randWait();
    std::cout << "thread2 release" << std::endl;
    semWaitFor2.release();
}

void t3Print() {
    semWaitFor1.acquire();
    std::cout << "thread3 acquire" << std::endl;
    randWait();
    std::cout << "thread3 release" << std::endl;
    semWaitFor1.release();
}

int main() {
    srand(time(0));
    std::thread thread1(t1Print);
    std::thread thread2(t2Print);
    std::thread thread3(t3Print);
    
    thread1.join();
    thread2.join();
    thread3.join();
}