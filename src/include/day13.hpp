#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day13 {

struct ClawMachine {
    std::pair<int, int> buttonA;
    std::pair<int, int> buttonB;
    std::pair<int, int> prize;
};

std::vector<ClawMachine> machines;

void run() {
    std::ifstream file("inputs/day13.txt");
    std::string line;
    
    std::vector<std::string> buffer;
    int count = 0;
    while (std::getline(file, line)) {
        count++;
        if (count % 4 == 0) {
            ClawMachine newMachine;
            int aXEnd = buffer[0].find_first_of(',', 12);
            int bXEnd = buffer[1].find_first_of(',', 12);
            int pXEnd = buffer[2].find_first_of(',', 9);
            newMachine.buttonA = {std::stoi(buffer[0].substr(12, aXEnd - 12)), std::stoi(buffer[0].substr(aXEnd + 3))};
            newMachine.buttonB = {std::stoi(buffer[1].substr(12, bXEnd - 12)), std::stoi(buffer[1].substr(bXEnd + 3))};
            newMachine.prize = {std::stoi(buffer[2].substr(9, pXEnd - 9)), std::stoi(buffer[2].substr(pXEnd + 4))};
            machines.emplace_back(newMachine);
            buffer.clear();
            count = 0;
        } else {
            buffer.emplace_back(line);
        }
    }
    {
        ClawMachine newMachine;
        int aXEnd = buffer[0].find_first_of(',', 12);
        int bXEnd = buffer[1].find_first_of(',', 12);
        int pXEnd = buffer[2].find_first_of(',', 9);
        newMachine.buttonA = {std::stoi(buffer[0].substr(12, aXEnd - 12)), std::stoi(buffer[0].substr(aXEnd + 3))};
        newMachine.buttonB = {std::stoi(buffer[1].substr(12, bXEnd - 12)), std::stoi(buffer[1].substr(bXEnd + 3))};
        newMachine.prize = {std::stoi(buffer[2].substr(9, pXEnd - 9)), std::stoi(buffer[2].substr(pXEnd + 4))};
        machines.emplace_back(newMachine);
    }

    long totalTokens = 0;
    for (ClawMachine& machine : machines) {
        int cheapest = -1;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                std::pair<int, int> total = {machine.buttonA.first * i + machine.buttonB.first * j, machine.buttonA.second * i + machine.buttonB.second * j};
                if (total == machine.prize) {
                    int cost = 3 * i + j;
                    if (cost < cheapest || cheapest == -1) {
                        cheapest = cost;
                    }
                }
            }
        }
        if (cheapest != -1) {
            totalTokens += cheapest;
        }
    }
    std::cout << "Total tokens: " << totalTokens << "\n";

    totalTokens = 0;
    for (ClawMachine& machine : machines) {
        long X_0 = machine.buttonA.first;
        long X_1 = machine.buttonB.first;
        long Y_0 = machine.buttonA.second;
        long Y_1 = machine.buttonB.second;
        long X_f = machine.prize.first + 10000000000000;
        long Y_f = machine.prize.second + 10000000000000;

        if ((X_f * Y_0 - X_0 * Y_f) % (X_1 * Y_0 - X_0 * Y_1) != 0) continue;
        long b = (X_f * Y_0 - X_0 * Y_f)/(X_1 * Y_0 - X_0 * Y_1);
        long a = (Y_f - Y_1 * b) / Y_0;

        std::cout << a << ", " << b << "\n";
        totalTokens += 3 * a + b;
    }
    std::cout << "Total tokens: " << totalTokens << "\n";
}

}