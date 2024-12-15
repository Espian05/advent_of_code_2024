#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day10 {

std::vector<std::string> input;

std::vector<char> heads = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool isIn(std::vector<std::pair<int, int>> arr, std::pair<int, int> target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            std::cout << arr[i].first << ", " << arr[i].second << " == " << target.first << ", " << target.second << "\n";
            return false;
        }
    }
    std::cout << "New trailend at " << target.first << ", " << target.second << "\n";
    return false;
}

std::vector<std::pair<int, int>> followTrail(int x, int y, int target) {
    std::cout << "(" << x << ", " << y << "), " << target << "\n";

    if (target == 10) {
        return {std::pair<int, int>(x, y)};
    }

    std::vector<std::pair<int, int>> seen;
    if (x > 0) {
        if (input[y][x-1] == heads[target]) {
            std::vector<std::pair<int, int>> here;
            here = followTrail(x-1, y, target + 1);
            for (int i = 0; i < here.size(); i++) {
                if (!isIn(seen, here[i])) {
                    seen.emplace_back(here[i]);
                }
            }
        }
    }
    if (y > 0) {
        if (input[y-1][x] == heads[target]) {
            std::vector<std::pair<int, int>> here;
            here = followTrail(x, y-1, target + 1);
            for (int i = 0; i < here.size(); i++) {
                if (!isIn(seen, here[i])) {
                    seen.emplace_back(here[i]);
                }
            }
        }
    }
    if (y < input.size() - 1) {
        if (input[y+1][x] == heads[target]) {
            std::vector<std::pair<int, int>> here;
            here = followTrail(x, y+1, target + 1);
            for (int i = 0; i < here.size(); i++) {
                if (!isIn(seen, here[i])) {
                    seen.emplace_back(here[i]);
                }
            }
        }
    } 
    if (x < input[0].size() - 1) {
        if (input[y][x+1] == heads[target]) {
            std::vector<std::pair<int, int>> here;
            here = followTrail(x+1, y, target + 1);
            for (int i = 0; i < here.size(); i++) {
                if (!isIn(seen, here[i])) {
                    seen.emplace_back(here[i]);
                }
            }
        }
    }

    std::cout << "Length: " << seen.size() << "\n";

    return seen;
}

void part1() {
    // From all 0s, traverse the input space and find the 9s
    int total = 0;
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[0].size(); x++) {
            std::vector<std::pair<int, int>> heads;
            if (input[y][x] == '0') {
                heads = followTrail(x, y, 1);
                total += heads.size();
                std::cout << "Trailheadscore: " << heads.size() << "\n";
            }
        }
    }
    std::cout << "Total: " << total << "\n";
}

void run() {
    std::ifstream file("inputs/day10.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        input.emplace_back(line);
    }

    part1();
}

}