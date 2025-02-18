#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <mutex>

std::counting_semaphore<6> prod(6);
std::counting_semaphore<6> cons(0);
std::mutex bufferAccess;

int buffer[6] = {0,0,0,0,0,0};
//bool available[6] = {true,true,true,true,true,true};

void printBuffer(){
    std::string bufferString = "";
    for (int i = 0; i < 6; i++){
        bufferString +=  std::to_string(buffer[i]);
        if (i != 5) bufferString += ",";
    }
    std::cout << bufferString << std::endl;
}

void produce(){
    srand(time(0));
    while (true){
        prod.acquire();
        bufferAccess.lock();
        // Can you exchange the above two lines? Similarly for consume().

        for (int i = 0; i < 6; i++){
            if (buffer[i] == 0) {
                buffer[i] = rand() % 100 + 1;
                std::cout << "Producing Item: " << buffer[i] << std::endl;
                printBuffer();
                break;
            }

        }
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 5)); 

        bufferAccess.unlock();
        cons.release();
        // Can you exchange the above two lines? Similarly for consume().
    }

}

void consume(){
    srand(time(0));
    while (true){
        cons.acquire();
        bufferAccess.lock();

        for (int i = 0; i < 6; i++){
            if (buffer[i] != 0) {
                std::cout << "Consuming Item: " << buffer[i] << std::endl;
                buffer[i] = 0;
                printBuffer();
                break;
            }

        }
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 5)); 

        bufferAccess.unlock();
        prod.release();
    }
}


int main(){
    std::thread producer(produce);
    std::thread producer2(produce);
    std::thread producer3(produce);
    std::thread consumer(consume);
    std::thread consumer2(consume);
    std::thread consumer3(consume);
    std::thread consumer4(consume);

    producer.join();
    producer2.join();
    producer3.join();
    consumer.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
}