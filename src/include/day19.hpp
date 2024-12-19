#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

namespace Day19 {

std::vector<std::string> towels;
std::vector<std::string> patterns;

std::map<std::string, bool> memo;
std::map<std::string, long> memo2;

bool isPossible(std::string target, std::vector<std::string> shortlist, int index) {
    if (index == target.size()) return true;

    std::string trueTarget = target.substr(index);
    if (memo.contains(trueTarget)) {
        return memo[trueTarget];
    }

    bool result = false;
    for (int s = 0; s < shortlist.size(); s++) {
        if (trueTarget.starts_with(shortlist[s])) {
            result |= isPossible(target, shortlist, index + shortlist[s].size());
        }
    }
    memo.emplace(trueTarget, result);
    return result;
}

long isPossibleTwo(std::string target, std::vector<std::string> shortlist, int index) {
    if (index == target.size()) return 1;

    std::string trueTarget = target.substr(index);
    if (memo2.contains(trueTarget)) {
        return memo2[trueTarget];
    }

    long result = 0;
    for (int s = 0; s < shortlist.size(); s++) {
        if (trueTarget.starts_with(shortlist[s])) {
            result += isPossibleTwo(target, shortlist, index + shortlist[s].size());
        }
    }
    memo2.emplace(trueTarget, result);
    return result;
}

void run() {
    std::ifstream file("inputs/day19.txt");
    std::string line;
    bool line0 = true;

    while (std::getline(file, line)) {
        if (line0) {
            line0 = false;
            std::string buffer = "";
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == ',') {
                    towels.emplace_back(buffer);
                    buffer.clear();
                    i++;
                } else {
                    buffer.push_back(line[i]);
                }
            }
            towels.emplace_back(buffer);
        } else {
            if (!line.empty()) {
                patterns.emplace_back(line);
            }
        }
    }

    for (int t = 0; t < towels.size(); t++) {
        std::cout << towels[t] << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < patterns.size(); i++) {
        std::cout << patterns[i] << "\n"; 
    }
    std::cout << "\n";

    // Iterate through each pattern
    int totalPossible = 0;
    long totalTotal = 0;
    for (int p = 0; p < patterns.size(); p++) {
        std::string target = patterns[p];

        std::vector<std::string> shortlist;
        for (int t = 0; t < towels.size(); t++) {
            if (target.contains(towels[t])) {
                shortlist.emplace_back(towels[t]);
            }
        }

        long result = isPossibleTwo(target, shortlist, 0);
        totalTotal += result;
        std::cout << result << "\n";

        if (result != 0) {
            std::cout << patterns[p] << " is possible\n";
            totalPossible++;
        } else {
            std::cout << patterns[p] << " is impossible\n";
        }
    }
    std::cout << "Total possible: " << totalPossible << "\n";
    std::cout << "Total total: " << totalTotal << "\n";
}

}