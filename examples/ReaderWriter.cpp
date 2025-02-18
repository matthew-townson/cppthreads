#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <mutex>

using binary_semaphore = std::counting_semaphore<1>;

// Can I just replace binary_semaphore here by mutex? Justify your answer.
std::binary_semaphore wr(1);
std::mutex rd; //Or binary semaphore
int numReaders = 0;

std::mutex bufferAccess;

int buffer[6] = {0,0,0,0,0,0};

void printBuffer(){
    std::string bufferString = "";
    for (int i = 0; i < 6; i++){
        bufferString +=  std::to_string(buffer[i]);
        if (i != 5) bufferString += ",";
    }
    std::cout << bufferString << std::endl;
}

void writef(){
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

void readf(){
    srand(time(0));
    while (true){
        // Must both lines (increment and if) be between lock() and unlock()?
        rd.lock();
        numReaders++;
        if (numReaders==1) wr.acquire();
        rd.unlock(); 

        int index = rand()%6;
        std::cout << "Reading " << buffer[index] << " from index " << index << std::endl;

        // Must both lines (decrement and if) be between lock() and unlock()?
        rd.lock();
        numReaders--;
        if (numReaders==0) wr.release();
        rd.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(rand() % 5)); 
    }
}


int main(){
    std::thread writefr(writef);
    std::thread writefr2(writef);
    std::thread writefr3(writef);
    std::thread reader(readf);
    std::thread reader2(readf);
    std::thread reader3(readf);
    std::thread reader4(readf);

    writefr.join();
    writefr2.join();
    writefr3.join();
    reader.join();
    reader2.join();
    reader3.join();
    reader4.join();
}