#include <iostream>
#include <chrono>
#include <thread>
#include <utility>
#include <string>
#include <fstring>

#define RUNTIMES 550
#define LENGTH 120
#define SPEED 20

class CellularAutomaton {
    private:
        int runtimes;
        int length;
        int* cells;
    
    public:
        //Constructor
        CellularAutomaton(int defRuns, int defLen) {
            runtimes = defRuns;
            length = defLen;

            // Initialise cells
            cells = new int[length];
            for (int i = 0; i < length; i++) {
                if ( i == length -1 ) {
                    cells[i] = 1;
                } else {
                    cells[i] = 0;
                }
            }
        }

        // Print "aliasing" to blocks
        void printBlocks(int inp) {
            switch(inp) {
                case 0:
                    std::cout << std::endl;
                    break;
                case 1:
                    std::cout << "  ";
                    break;
                case 2:
                    std::cout << "██";
                    break;
            }
        }

        // Print current iteration
        void printIteration(int cellsIteration[]) {
            for (int i = 0; i < length; i++) {
                printBlocks(cellsIteration[i]+1);
            } printBlocks(0);
        }

        // Write to textfile
        void writeToFile(std::string filename, int data[]) {
            std::ofstream file (filename);
            if (file.is_open())
            {
                for (int i = 0; i < length; i++) {
                    file << data[i];
                }
            }
            file.close();
        }
};

void main() {
    CellularAutomaton automaton(RUNTIMES, LENGTH);
}