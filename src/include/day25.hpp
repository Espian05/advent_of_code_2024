#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

#include <memory>

#include <bitset>
#include <unordered_set>

namespace Day25 {

std::vector<std::vector<int>> keys;
std::vector<std::vector<int>> locks;

void run() {
    srand(time(NULL));

    std::ifstream file("inputs/day25.txt");
    std::string line;

    std::vector<std::string> buffer;
    while (std::getline(file, line)) {
        if (line.empty()) {
            std::vector<int> mold;
            for (int x = 0; x < 5; x++) {
                int count = 0;
                for (int y = 1; y < buffer.size() - 1; y++) {
                    if (buffer[y][x] == '#') count++;
                }
                mold.emplace_back(count);
            }
            if (buffer[0] == "#####") {
                locks.emplace_back(mold);
            } else {
                keys.emplace_back(mold);
            }
            buffer.clear();
        } else {
            buffer.emplace_back(line);
        }
    }
    {   // One more for the buffer
        std::vector<int> mold;
        for (int x = 0; x < 5; x++) {
            int count = 0;
            for (int y = 1; y < buffer.size() - 1; y++) {
                if (buffer[y][x] == '#') count++;
            }
            mold.emplace_back(count);
        }
        if (buffer[0] == "#####") {
            locks.emplace_back(mold);
        } else {
            keys.emplace_back(mold);
        }
    }

    std::cout << "Keys:\n";
    for (auto& k : keys) {
        for (auto& i : k) {
            std::cout << i << ", ";
        }
        std::cout << "\n";
    }

    std::cout << "Locks:\n";
    for (auto& l : locks) {
        for (auto& i : l) {
            std::cout << i << ", ";
        }
        std::cout << "\n";
    }

    int total = 0;
    for (int k = 0; k < keys.size(); k++) {
        for (int l = 0; l < locks.size(); l++) {
            int count = 0;
            for (int i = 0; i < keys[k].size(); i++) {
                if (keys[k][i] + locks[l][i] <= 5) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == locks[l].size()) {
                total++;
            }
        }
    }
    std::cout << "Total: " << total << "\n";

}

}