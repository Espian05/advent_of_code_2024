#include <iostream>
#include <fstream> 
#include <vector>

namespace Day1 {

std::vector<int> left;
std::vector<int> right;

void parseLine(std::string line) {
    int space = line.find_first_of(' ');
    
    std::string first = line.substr(0, space);
    std::string second= line.substr(space, line.size() - space);

    left.emplace_back(std::stoi(first));
    right.emplace_back(std::stoi(second));
}

void run() {
    std::ifstream file("inputs/day1.txt");
    std::string input;
    
    while (std::getline(file, input)) {
        parseLine(input);
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // Part 1
    int totalDistance = 0;
    for (int i = 0; i < left.size(); i++) {
        totalDistance += abs(left[i] - right[i]);
    }

    std::cout << "Total distance: " << totalDistance << "\n";

    // Part 2
    int similarity = 0;

    for (int i = 0; i < left.size(); i++) {
        int n = 0;
        for (int j = 0; j < right.size(); j++) {
            if (left[i] == right[j]) n++;
        }
        similarity += left[i] * n;
    }

    std::cout << "Similarity score: " << similarity << "\n";
}

}
