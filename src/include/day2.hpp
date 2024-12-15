#include <iostream>
#include <fstream> 
#include <vector>

namespace Day2 {

std::vector<std::vector<int>> matrix;

void parseLine(std::string &line) {
    std::string buffer = "";
    std::vector<int> row;
    for (char& c : line) {
        if (c == ' ') {
            row.emplace_back(std::stoi(buffer));
            buffer.clear();
        } else {
            buffer.push_back(c);
        }
    }
    row.push_back(std::stoi(buffer));
    matrix.emplace_back(row);
}

bool isIncreasing(std::vector<int> &vector) {
    for (int i = 0; i < vector.size() - 1; i++) {
        if (vector[i + 1] < vector[i]) {
            return false;
        }
    }

    return true;
}

bool isDecreasing(std::vector<int> &vector) {
    for (int i = 0; i < vector.size() - 1; i++) {
        if (vector[i + 1] > vector[i]) {
            return false;
        }
    }

    return true;
}

bool checkDiff(std::vector<int> &vector) {
    for (int i = 0; i < vector.size() - 1; i++) {
        int diff = abs(vector[i] - vector[i + 1]);
        if (diff < 1 || diff > 3) {
            return false;
        }
    }

    return true;
}

void run() {
    std::ifstream file("inputs/day2.txt");
    std::string input;
    
    while (std::getline(file, input)) {
        parseLine(input);
    }


    // Part 1
    int safeReports = 0;

    for (std::vector<int>& report : matrix) {
        if ((isIncreasing(report) || isDecreasing(report)) && checkDiff(report)) {
            safeReports++;
            std::cout << "Safe\n";
        } else {
            std::cout << "Unsafe\n";
        }
    }

    std::cout << "Safe reports damped: " << safeReports << "\n";

    // Part 2
    safeReports = 0;

    for (std::vector<int>& report : matrix) {
        if ((isIncreasing(report) || isDecreasing(report)) && checkDiff(report)) {
            safeReports++;
            std::cout << "Safe\n";
            continue;
        }

        bool safe = false;
        for (int i = 0; i < report.size(); i++) {
            if (safe) break;
            std::vector<int> copy = report;
            copy.erase(copy.begin() + i);

            if ((isIncreasing(copy) || isDecreasing(copy)) && checkDiff(copy)) {
                safeReports++;
                safe = true;
                std::cout << "Safe\n";
                continue;
            }
        }
        std::cout << "Unsafe\n";
    }

    std::cout << "Safe reports undamped: " << safeReports << "\n";
}

}