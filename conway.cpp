#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include "board.h"
#include <string>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> templates = {
    { 
    "blinker",
    "0 0 0 0 0\n0 0 1 0 0\n0 0 1 0 0\n0 0 1 0 0\n0 0 0 0 0"
    }
};

void sleep(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

// Allows text to be read by parseLines function
std::vector<std::string> split(const std::string& text) {
    std::stringstream ss(text);
    std::string current;
    std::vector<std::string> res;

    while (std::getline(ss, current, '\n')) {
        res.push_back(current);
    } 
    return res;
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
    std::vector<std::vector<bool>> initialBoard;
    std::string templateName;
    char mode;

    std::cout << "Board Template or Custom (config.txt)?" << std::endl;
    std::cout << "[T]emplate, [C]ustom" << std::endl;
    std::cin >> mode;

    switch (mode) {
        case 'T':
            std::cout << "Which board template would you like to use?" << std::endl;
            for (auto const& [title, boardLayout] : templates) {
                std::cout << title << std::endl;
                std::cout << boardLayout << std::endl;

            std::cin >> templateName;
            initialBoard = parseLines(split(templates[templateName]));

            break;
        }

        case 'C':
            initialBoard = parseLines(readFile());
            break;
    }

    Board board(initialBoard);

    std::cout << "Press enter to contine : ";
    std::cin.ignore();
    std::cout << std::endl;

    while (true) {
        board.printBoard();
        board.nextGeneration();
        sleep(1000);
    }
}
