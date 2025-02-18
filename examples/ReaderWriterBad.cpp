#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <mutex>

std::binary_semaphore wr(1);
int numReaders = 0;
int buffer[6] = {0,0,0,0,0,0};

void write(){
    srand(time(0));
    while (true){
        wr.acquire();
        int index = rand()%6;
        buffer[index] = rand() % 100 + 1;
        std::cout << "Writing " << buffer[index] << " to index " << index << std::endl;
        wr.release();
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 10)); 
    }

}

void read(){
    srand(time(0));
    while (true){
        numReaders++;
        // Concurrent access to numReaders is correct?
        if (numReaders==1) wr.acquire();

        int index = rand()%6;
        std::cout << "Reading " << buffer[index] << " from index " << index << std::endl;

        numReaders--;
        if (numReaders==0) wr.release();
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 5)); 
    }
}


int main(){
    std::thread writer(write);
    std::thread writer2(write);
    std::thread writer3(write);
    std::thread reader(read);
    std::thread reader2(read);
    std::thread reader3(read);
    std::thread reader4(read);

    writer.join();
    writer2.join();
    writer3.join();
    reader.join();
    reader2.join();
    reader3.join();
    reader4.join();
}