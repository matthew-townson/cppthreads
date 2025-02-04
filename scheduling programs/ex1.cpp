#include <iostream>
#include <thread>
//#include <mutex>
#include <chrono>
#include <semaphore>

/*

Print out 2 threads T1 and T2, and only allow one to print at once

*/

using binary_semaphore = std::counting_semaphore<1>;

std::binary_semaphore printing(1);

void t1Print() {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
    printing.acquire();
    std::cout << "thread1" << std::endl;
    printing.release();

}

void t2Print() {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
    printing.acquire();
    std::cout << "thread2" << std::endl;
    printing.release();
}

int main() {
    srand(time(0));
    std::thread thread1(t1Print);
    std::thread thread2(t2Print);

    thread1.join();
    thread2.join();
}