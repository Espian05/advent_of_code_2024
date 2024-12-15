#include <iostream>
#include <fstream> 
#include <vector>

namespace Day4 {

std::vector<std::string> wordsearch;
std::vector<std::vector<bool>> Xs;

enum Direction {
    UP = 0,
    UP_RIGHT = 1,
    RIGHT = 2,
    DOWN_RIGHT = 4,
    DOWN = 8,
    DOWN_LEFT = 16,
    LEFT = 32,
    UP_LEFT = 64
};

int recursiveSearch(int x, int y, Direction direction, std::string targetWord, int index) {
    if (index == targetWord.size()) {
        std::cout << "Word found! Ended at (" << x << ", " << y << ")\n";
        return 1;
    }

    std::cout << "(" << x << ", " << y << ") direction" << direction << "\n";

    // Check bounderies
    switch (direction) {
        case Direction::UP:
            if (y == 0) return 0;
            if (wordsearch[y-1][x] == targetWord[index])
                return recursiveSearch(x, y-1, direction, targetWord, ++index);
            return 0;
            break;
        case Direction::UP_RIGHT:
            if (y == 0 || x == wordsearch[0].size() - 1) return 0;
            if (wordsearch[y-1][x+1] == targetWord[index])
                return recursiveSearch(x+1, y-1, direction, targetWord, ++index);
            return 0;
            break;
        case Direction::RIGHT:
            if (x == wordsearch[0].size() - 1) return 0;
            if (wordsearch[y][x+1] == targetWord[index])
                return recursiveSearch(x+1, y, direction, targetWord, ++index);
            return 0;
            break;
        case Direction::DOWN_RIGHT:
            if (x == wordsearch[0].size() - 1 || y == wordsearch.size() - 1) return 0;
            if (wordsearch[y+1][x+1] == targetWord[index])
                return recursiveSearch(x+1, y+1, direction, targetWord, ++index);
            return 0;
            break;
        case Direction::DOWN:
            if (y == wordsearch.size() - 1) return 0;
            if (wordsearch[y+1][x] == targetWord[index])
                return recursiveSearch(x, y+1, direction, targetWord, ++index);
            return 0;
            break;
        case Direction::DOWN_LEFT:
            if (y == wordsearch.size() - 1 || x == 0) return 0;
            if (wordsearch[y+1][x-1] == targetWord[index])
                return recursiveSearch(x-1, y+1, direction, targetWord, ++index);
            return 0;
            break;
        case Direction::LEFT:
            if (x == 0) return 0;
            if (wordsearch[y][x-1] == targetWord[index])
                return recursiveSearch(x-1, y, direction, targetWord, ++index);
            return 0;
            break;
        case Direction::UP_LEFT:
            if (x == 0 || y == 0) return 0;
            if (wordsearch[y-1][x-1] == targetWord[index])
                return recursiveSearch(x-1, y-1, direction, targetWord, ++index);
            return 0;
            break;
    }
}

void run() {
    std::ifstream file("inputs/day4.txt");
    std::string input;
    
    while (std::getline(file, input)) {
        wordsearch.emplace_back(input);
    }

    for (std::string& row : wordsearch) {
        std::cout << row << "\n";
    }

    std::string target = "XMAS";
    int totalFound = 0;

    // Identify all occurances of "X", these will be our focal points for a search
    for (int y = 0; y < wordsearch.size(); y++) {
        for (int x = 0; x < wordsearch[y].size(); x++) {
            if (wordsearch[y][x] == 'X') {
                totalFound += recursiveSearch(x, y, Direction::UP, "XMAS", 1);
                totalFound += recursiveSearch(x, y, Direction::UP_RIGHT, "XMAS", 1);
                totalFound += recursiveSearch(x, y, Direction::RIGHT, "XMAS", 1);
                totalFound += recursiveSearch(x, y, Direction::DOWN_RIGHT, "XMAS", 1);
                totalFound += recursiveSearch(x, y, Direction::DOWN, "XMAS", 1);
                totalFound += recursiveSearch(x, y, Direction::DOWN_LEFT, "XMAS", 1);
                totalFound += recursiveSearch(x, y, Direction::LEFT, "XMAS", 1);
                totalFound += recursiveSearch(x, y, Direction::UP_LEFT, "XMAS", 1);
            }
        }
    }

    std::cout << "Total XMAS found: " << totalFound << "\n";

    totalFound = 0;

    for (int y = 1; y < wordsearch.size() - 1; y++) {
        for (int x = 1; x < wordsearch[y].size() - 1; x++) {
            if (wordsearch[y][x] == 'A') {
                int number = 0;
                if (wordsearch[y+1][x-1] == 'M' && wordsearch[y-1][x+1] == 'S')
                    number++;
                if (wordsearch[y+1][x-1] == 'S' && wordsearch[y-1][x+1] == 'M')
                    number++;
                
                if (wordsearch[y-1][x-1] == 'M' && wordsearch[y+1][x+1] == 'S')
                    number++;
                if (wordsearch[y-1][x-1] == 'S' && wordsearch[y+1][x+1] == 'M')
                    number++;
                
                if (number == 2) {
                    totalFound++;
                }
            }
        }
    }

    std::cout << "Total X-MAS found: " << totalFound << "\n";
}

}