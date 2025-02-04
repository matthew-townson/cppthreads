#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>

/*
Two threads, ensure that T1 before T2
*/

using binary_semaphore = std::counting_semaphore<0>;

std::binary_semaphore printing(0);

void t1Print() {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
    std::cout << "thread1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
    printing.release();
}

void t2Print() {
    printing.acquire();
    std::cout << "thread2" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
    printing.release();
}

int main() {
    srand(time(0));
    std::thread thread1(t1Print);
    std::thread thread2(t2Print);

    thread1.join();
    thread2.join();
}