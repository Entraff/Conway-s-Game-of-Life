#include "board.h"
#include <vector>
#include <iostream>
#include <stdint.h>

Board::Board(const std::vector<std::vector<bool>>& _board) :
    board(_board),
    rows(_board.size()),
    columns(_board[0].size())
    {}

void Board::printBoard() {
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < columns; ++j) {
            if (board[i][j]) std::cout << "#";
            else std::cout << "-";
        }
        std::cout << std::endl;
    }
}

short Board::getAliveNeighbors(const int& rowIndex, const int& columnIndex) {
    short total = 0;
    int i, j;
    int neighborRow, neighborColumn;
    // rates through the indicies around the current index
    for (i = -1; i <= 1; ++i) {
        for (j = -1; j <= 1; ++j) {

            neighborRow = rowIndex + i;
            neighborColumn = columnIndex + j;
            
            // If the neighbor is out of bounds, continue to the next iteration
            if (neighborColumn < 0 || neighborColumn >= columns)
                continue;
            if (neighborRow < 0 || neighborRow >= rows)
                continue;

            if (board[neighborRow][neighborColumn]) total++;
        }
    }
    // One is removed because the algorithm above also counts itself if it's alive
    // In this case we only want to get the neigbors
    return board[rowIndex][columnIndex] 
           ? total - 1 : total;
}

void Board::nextGeneration() {
    // Initializes array with the same size as the previous board
    std::vector<std::vector<bool>> buffer(
        rows,
        std::vector<bool>(columns, 0)        
    );

    short aliveNeighbors;
    int i, j;
    bool currentCell, revisedCell;

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < columns; ++j) {
            currentCell = board[i][j];
            aliveNeighbors = getAliveNeighbors(i, j);
           
            // Determines whether a cell lives or dies in the next generation 
            revisedCell = currentCell;
            if (currentCell) {
                if (aliveNeighbors < 2) revisedCell = 0;
                else if (aliveNeighbors > 3) revisedCell = 0;
            } else if (aliveNeighbors == 3) revisedCell = 1;
            buffer[i][j] = revisedCell;
        }
    }
    board = buffer;
}
