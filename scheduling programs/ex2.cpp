#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>

/*
4 Threads - only allow two threads to print at same time
*/

#define WAITTIMEMS 5000

std::counting_semaphore<2> printing(2);

void t1Print() {
    printing.acquire();
    std::cout << "thread1 acquire" << std::endl << "thread1 sleeping" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % WAITTIMEMS));
    std::cout << "thread1 released" << std::endl;
    printing.release();
}

void t2Print() {
    printing.acquire();
    std::cout << "thread2 acquire" << std::endl << "thread2 sleeping" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % WAITTIMEMS));
    std::cout << "thread2 released" << std::endl;
    printing.release();
}

void t3Print() {
    printing.acquire();
    std::cout << "thread3 acquire" << std::endl << "thread3 sleeping" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % WAITTIMEMS));
    std::cout << "thread3 released" << std::endl;
    printing.release();
}

void t4Print() {
    printing.acquire();
    std::cout << "thread4 acquire" << std::endl << "thread4 sleeping" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % WAITTIMEMS));
    std::cout << "thread4 released" << std::endl;
    printing.release();
}

int main() {
    srand(time(0));
    std::thread thread1(t1Print);
    std::thread thread2(t2Print);
    std::thread thread3(t3Print);
    std::thread thread4(t4Print);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
}