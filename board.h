#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <stdint.h>

class Board {
    private:
        std::vector<std::vector<bool>> board;
        int rows;
        int columns;
        short getAliveNeighbors(const int& rowIndex, const int& columnIndex);
    public:
        Board(const std::vector<std::vector<bool>>& _board);
        void printBoard();
        void nextGeneration();
};

#endif // BOARD_H
