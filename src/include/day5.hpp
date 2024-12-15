#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day5 {

std::vector<std::pair<int, int>> rules;
std::vector<std::vector<int>> updates;

void readUpdate(std::string input) {
    std::vector<int> update;
    std::string buffer = "";

    for (char& c : input) {
        if (c == ',') {
            update.emplace_back(std::stoi(buffer));
            buffer = "";
        } else {
            buffer.push_back(c);
        }
    }
    update.emplace_back(std::stoi(buffer));

    updates.emplace_back(update);
}

int findPos(std::vector<int> input, int target) {
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == target) return i;
    }
    return -1;
}

bool validateUpdate(std::vector<int> update) {
    for (int i = 0; i < rules.size(); i++) {
        // For each rule, check it is followed?
        for (std::pair<int, int>& rule : rules) {
            int posFirst = findPos(update, rule.first);
            int posSecond = findPos(update, rule.second);

            if (posFirst == -1 || posSecond == -1) continue;

            if (posFirst > posSecond) {
                return false;
            }
        }
    }
    return true;
}

void run() {
    std::ifstream file("inputs/day5.txt");
    std::string input;
    
    int state = 0;
    while (std::getline(file, input)) {
        if (input.empty()) {
            state = 1;
            continue;
        }
        if (state == 0) { // This means we're reading in the rules
            std::string first = input.substr(0, 2);
            std::string second = input.substr(3, 2);
            rules.emplace_back(std::stoi(first), std::stoi(second));
        } else { // This means we're reading sequences
            readUpdate(input);
        }
    }

    // Print the rules and the updates to verify they're right
    std::cout << "Rules:\n";
    for (std::pair<int, int> &pair : rules) {
        std::cout << pair.first << "|" << pair.second << "\n";
    }

    std::cout << "Updates:\n";
    for (std::vector<int> &update : updates) {
        for (int& thing : update) {
            std::cout << thing << ",";
        }
        std::cout << "\r\n";
    }

    // Go through and identify all the runs that are valid.
    // Do this by iterating through each run from 0 to n-1 and checking
    // that if a rule exists it is followed
    int total = 0;
    std::vector<std::vector<int>> brokenUpdates;
    for (std::vector<int>& update : updates) {
        if (validateUpdate(update)) {
            std::cout << "Adding " << update[(update.size() - 1) / 2] << "\n";
            total += update[(update.size() - 1) / 2];
        } else {
            brokenUpdates.emplace_back(update);
        }
    }

    std::cout << "Total: " << total << "\n";

    std::cout << "Fixing the fucking rules apparently?\n";
    int brokenTotal = 0;
    // Fix the fucking rules apparently???
    for (std::vector<int>& update : brokenUpdates) {
        for (int i = 0; i < rules.size(); i++) {
            // For each rule, check it is followed?
            for (std::pair<int, int>& rule : rules) {
                int posFirst = findPos(update, rule.first);
                int posSecond = findPos(update, rule.second);

                if (posFirst == -1 || posSecond == -1) continue;
                std::cout << "First: " << posFirst << "\tSecond: " << posSecond << "\n";

                if (posFirst > posSecond) {
                    update[posSecond] = rule.first;
                    update[posFirst] = rule.second;
                    std::cout << "Swapping " << rule.first << " with " << rule.second << "\n";
                    i = 0;
                }
            }
        }
        std::cout << "Rule fixed!\n";
        brokenTotal += update[(update.size() - 1) / 2];
    }
    std::cout << "Broken total: " << brokenTotal << "\n";
}

}