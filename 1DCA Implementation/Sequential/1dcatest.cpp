#include <iostream>
#include <chrono>
#include <thread>
#include <utility>
#include <cstring>
#include <string>

#define RUNTIMES 550
#define LENGTH 120

void printblock(int type) {
    switch(type) {
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

void printCycle(int arr[]) {
    for (int i = 0; i < LENGTH; i++) {
        printblock(arr[i]+1);
        //std::cout << arr[i]+1;
    }
    printblock(0);
}

int main() {
    // Initialise array of cells
    int* cells = new int[LENGTH]; //{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int i = 0; i < LENGTH; i++) {
        if ( i == LENGTH -1 ) { //i == (LENGTH*1)/2
            cells[i] = 1;
        } else {
            cells[i] = 0;
        }
    }

    // Initialised cells
    std::cout << "INIT CELLS\n";
    for ( int i = 0; i < LENGTH; i++ ) {
        std::cout << cells[i];
    }
    std::cout << std::endl;

    /* Rule: Cells 0 and 26 cannot be changed */

    printCycle(cells);
    for (int i = 0; i < RUNTIMES; i++) {
        bool inRange = true;
        while (inRange) {
            // Print the current generation of cells
            int* pCells = new int[LENGTH];

            // set previous array
            for ( int k = 0; k < LENGTH; k++ ) {
                pCells[k] = cells[k];
            }

            for (int t = 0; t < LENGTH - 1; t++) {
                // Get the 3 sequence
                std::string strseq = "";
                for (int n = 0; n < 3; n++) {
                    strseq += std::to_string(pCells[n + t]);
                }

                // Change array entry
                if ( strseq == "000" ) {
                    cells[t+1] = 0;
                } else if ( strseq == "001" ) {
                    cells[t+1] = 1;
                } else if ( strseq == "010" ) {
                    cells[t+1] = 1;
                } else if ( strseq == "011" ) {
                    cells[t+1] = 1;
                } else if ( strseq == "100" ) {
                    cells[t+1] = 0;
                } else if ( strseq == "101" ) {
                    cells[t+1] = 1;
                } else if ( strseq == "110" ) {
                    cells[t+1] = 1;
                } else if ( strseq == "111" ) {
                    cells[t+1] = 0;
                } else {
                    break;
                }
            }
            printCycle(cells);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            inRange = false;
        }
    }

    return 0;
}
