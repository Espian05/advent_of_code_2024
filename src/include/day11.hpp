#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day11 {

std::vector<std::string> input;

std::map<std::pair<std::string, int>, long long> previous;

std::vector<std::string> blink(std::vector<std::string> state) {
    for (int i = 0; i < state.size(); i++) {
        long long value = std::stoll(state[i]);
        int length = state[i].size();
        if (value == 0) {
            state[i] = "1";
        } else if (length % 2 == 0) {
            std::string firstHalf = state[i].substr(0, length / 2);
            std::string secondHalf = state[i].substr(length / 2);
            firstHalf = std::to_string(std::stoll(firstHalf));
            secondHalf = std::to_string(std::stoll(secondHalf));
            state[i] = firstHalf;
            state.insert(state.begin() + i + 1, secondHalf);
            i++;
        } else {
            state[i] = std::to_string(value * 2024);
        }
    }

    return state;
}

void parseInput(std::string line) {
    std::string buffer;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            input.emplace_back(buffer);
            buffer.clear();
        } else {
            buffer.push_back(line[i]);
        }
    }
    input.emplace_back(buffer);
}

long long iterateWithMap(std::string in, int depth) {
    if (depth == 0) return 1;

    if (previous.contains({in, depth})) {
        return previous[{in, depth}];
    } else {
        long long value = std::stoll(in);

        if (value == 0) return iterateWithMap("1", depth-1);
        else if (in.size() % 2 == 0) {
            std::string firstHalf = in.substr(0, in.size()/2);
            std::string secondHalf = in.substr(in.size()/2);
            firstHalf = std::to_string(std::stoll(firstHalf));
            secondHalf = std::to_string(std::stoll(secondHalf));
            long long result = iterateWithMap(firstHalf, depth-1) + 
                iterateWithMap(secondHalf, depth-1);
            previous.emplace(std::pair<std::string, int>(in, depth), result);
            return result;
        } else {
            long long result = iterateWithMap(std::to_string(value * 2024), depth-1);
            previous.emplace(std::pair<std::string, int>(in, depth), result);
            return result;
        }
    }
}

void run() {
    std::ifstream file("inputs/day11.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        parseInput(line);
    }

    // Going to try recursion for part 2
    long long total = 0;
    for (int i = 0; i < input.size(); i++) {
        total += iterateWithMap(input[i], 100);
        std::cout << "Done with " << i << "\n";
    }
    std::cout << "Over 75, " << total << " stones.\n";
}

}