#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <stdint.h>

class Board {
    private:
        std::vector<std::vector<bool>> board;
        int rows;
        int columns;
    public:
        Board(const std::vector<std::vector<bool>>& _board);
        void printBoard();
        short getAliveNeighbors(const int& rowIndex, const int& columnIndex);
        void nextGeneration();
};

#endif // BOARD_H
