#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include "board.h"
#include <string>

void sleep(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

// Requires config.txt file
std::vector<std::string> readFile() {
    std::vector<std::string> text;
    std::string line;
    std::fstream file("config.txt");

    while (getline(file, line)) {
        text.push_back(line);
    }

    file.close();
    return text;
}

std::vector<std::vector<bool>> parseLines(const std::vector<std::string>& text) {
    const int rowCount = text.size();
    const int columnCount = text[0].length();
    std::vector<std::vector<bool>> res(rowCount);
    
    int i, j;
    for (i = 0; i < rowCount; ++i) {
        // j increments by 2 to avoid whitespace in between characters
        for (j = 0; j < columnCount; j += 2) {
            if (text[i][j] == '1') {
                res[i].push_back(1);
            } else {
                res[i].push_back(0);
            }
        }
    }
    return res;
}

int main() {
    std::vector<std::vector<bool>> initialBoard = parseLines(readFile());
    Board board(initialBoard);
    
    std::cout << "Press enter to contine : ";
    std::cin.ignore();

    while (true) {
        board.printBoard();
        board.nextGeneration();
        sleep(1000);
    }
}
