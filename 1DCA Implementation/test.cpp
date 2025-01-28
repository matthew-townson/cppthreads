#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

void f() {
    for ( int i = 0; i < 5; i++ ){
        std::cout << i << "steps\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

int main() {
    std::thread t1(f);
    std::thread t2(f);
    t1.join();
    t2.join();
}