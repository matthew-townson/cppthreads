#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

// Modify values of the binary semaphores: e.g., (1,1), or (0,0), or (0,1). 
// What happens?
// If the behavior is incorrect, describe why?

std::binary_semaphore prod(1);
std::binary_semaphore cons(0);
int buffer[1] = {0};

void produce(){
    srand(time(0));
    while (true){
        prod.acquire();
        buffer[0] = rand() % 100 + 1;
        std::cout << "Producing Item: " << buffer[0] << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
        cons.release();
    }

}

void consume(){
    srand(time(0));
    while (true){
        cons.acquire();
        std::cout << "Consuming Item: " << buffer[0] << std::endl;
        buffer[0] = 0;
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
        prod.release();
    }
}


int main(){
    std::thread producer(produce);
    std::thread consumer(consume);

    producer.join();
    consumer.join();
}