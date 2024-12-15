#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day7 {

std::vector<std::vector<long long>> numbers = {};

void parseInput(std::string input) {
    std::vector<long long> row;
    int colon = input.find_first_of(':');
    row.emplace_back(std::stoll(input.substr(0, colon)));

    std::string buffer;
    for (int i = colon + 2; i < input.size(); i++) {
        if (input[i] == ' ') {
            row.emplace_back(std::stoll(buffer));
            buffer.clear();
        } else {
            buffer += input[i];
        }
    }
    row.emplace_back(std::stoll(buffer));
    buffer.clear();

    numbers.emplace_back(row);
    return;
}

long long test(long long total, std::vector<long long>& possible, int index, long long target) {
    //std::cout << "Total: " << total << "\tTarget: " << target << "\n"; 
    if (total > target) return 0;
    if (index == possible.size()) {
        if (total == target) return target;
        return 0;
    }

    return std::max(
        test(total + possible[index], possible, index + 1, target),
        test(total * possible[index], possible, index + 1, target));
}

long long test2(long long total, std::vector<long long>& possible, int index, long long target) {
    //std::cout << "Total: " << total << "\tTarget: " << target << "\n"; 
    if (total > target) return 0;
    if (index == possible.size()) {
        if (total == target) return target;
        return 0;
    }

    return std::max(std::max(
        test2(total + possible[index], possible, index + 1, target),
        test2(total * possible[index], possible, index + 1, target)),
        test2(std::stoll(std::to_string(total) + std::to_string(possible[index])), possible, index + 1, target));
}

void run() {
    std::ifstream file("inputs/day7.txt");
    std::string input;
    
    while (std::getline(file, input)) {
        parseInput(input);
    }

    std::cout << "TEST\n";
    std::cout << std::stoll(std::to_string(100ULL) + std::to_string(5ULL)) << "\n";
    std::cout << "\n\n";

    std::cout << "\n";
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i][0] << ": ";
        for (int k = 1; k < numbers[i].size(); k++) {
            std::cout << numbers[i][k] << ", ";
        }
        std::cout << "\n";
    }

    long long total = 0;
    for (std::vector<long long>& row : numbers) {
        total += test(row[1], row, 2, row[0]);
    }
    std::cout << "Total: " << total << "\n";

    total = 0;
    for (std::vector<long long>& row : numbers) {
        total += test2(row[1], row, 2, row[0]);
    }
    std::cout << "Total2: " << total << "\n";
}

}