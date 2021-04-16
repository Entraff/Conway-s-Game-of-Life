#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include "board.h"

void sleep(uint32_t x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

int main() {
    std::vector<std::vector<bool>> initialBoard = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0}
    };
    Board board(initialBoard);
    
    std::cout << "Press enter to contine : ";
    std::cin.ignore();

    while (true) {
        board.printBoard();
        board.nextGeneration();
        sleep(1000);
    }
}
