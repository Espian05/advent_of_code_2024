#define _BSD_SOURCE
#define _DEFAULT_SOURCE

#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <termios.h>
#include <unistd.h>

namespace Day15 {

std::vector<std::string> warehouse = {};
std::string moves = "";

bool attemptMove(std::pair<int, int>& pos, char move) {
    if (warehouse[pos.second][pos.first] == '#') return false;
    if (warehouse[pos.second][pos.first] == '.') return true;

    std::pair<int, int> next = {};

    if (move == '^') {
        next = {pos.first, pos.second - 1};
    }
    if (move == '>') {
        next = {pos.first + 1, pos.second};
    }
    if (move == '<') {
        next = {pos.first - 1, pos.second};
    }
    if (move == 'v') {
        next = {pos.first, pos.second + 1};
    }

    //std::cout << "(" << next.first << ", " << next.second << ")\n";
    //std::cout << warehouse[pos.second][pos.first] << "\n";
    //std::cout << warehouse[next.second][next.first] << "\n";
    //std::cout << move << "\n";

    if (warehouse[pos.second][pos.first] == '@') {
        if (attemptMove(next, move)) {
            warehouse[next.second][next.first] = '@';
            warehouse[pos.second][pos.first] = '.';
            pos = next;
            return true;
        }
        return false;
    }
    if (warehouse[pos.second][pos.first] == '[') {
        std::vector<std::string> copy = warehouse;
        std::pair<int, int> otherNext = {next.first + 1, next.second};

        if (move == '<') { // Man, fuck edgecases
            if (attemptMove(next, move)) {
                warehouse[next.second][next.first] = '[';
                warehouse[pos.second][pos.first] = ']';
                warehouse[pos.second][pos.first + 1] = '.';
                return true;
            }
            return false;
        }
        if (move == '>') { // Man, fuck edgecases
            if (attemptMove(otherNext, move)) {
                warehouse[next.second][next.first] = '[';
                warehouse[otherNext.second][otherNext.first] = ']';
                warehouse[pos.second][pos.first] = '.';
                return true;
            }
            return false;
        }

        if (attemptMove(next, move) && attemptMove(otherNext, move)) {
            warehouse[next.second][next.first] = '[';
            warehouse[otherNext.second][otherNext.first] = ']';
            warehouse[pos.second][pos.first] = '.';
            warehouse[pos.second][pos.first + 1] = '.';
            return true;
        }
        warehouse = copy;
        return false;
    }
    if (warehouse[pos.second][pos.first] == ']') {
        std::vector<std::string> copy = warehouse;
        std::pair<int, int> otherNext = {next.first - 1, next.second};

        if (move == '<') { // Man, fuck edgecases
            if (attemptMove(otherNext, move)) {
                warehouse[otherNext.second][otherNext.first] = '[';
                warehouse[next.second][next.first] = ']';
                warehouse[pos.second][pos.first] = '.';
                return true;
            }
            return false;
        }
        if (move == '>') { // Man, fuck edgecases
            if (attemptMove(next, move)) {
                warehouse[pos.second][pos.first] = '[';
                warehouse[next.second][next.first] = ']';
                warehouse[pos.second][pos.first - 1] = '.';
                return true;
            }
            return false;
        }

        if (attemptMove(next, move) && attemptMove(otherNext, move)) {
            warehouse[next.second][next.first] = ']';
            warehouse[otherNext.second][otherNext.first] = '[';
            warehouse[pos.second][pos.first] = '.';
            warehouse[pos.second][pos.first - 1] = '.';
            return true;
        }
        warehouse = copy;
        return false;
    }

    return false;
}

void run() {
    std::ifstream file("inputs/day15.txt");
    std::string line;
    bool warehouseInput = true;

    while (std::getline(file, line)) {
        if (line.empty()) {
            warehouseInput = false;
            continue;
        }

        if (warehouseInput) {
            std::string newInput;
            for (int x = 0; x < line.size(); x++) {
                if (line[x] == '#') {
                    newInput.push_back('#');
                    newInput.push_back('#');
                }
                if (line[x] == 'O') {
                    newInput.push_back('[');
                    newInput.push_back(']');
                }
                if (line[x] == '.') {
                    newInput.push_back('.');
                    newInput.push_back('.');
                }
                if (line[x] == '@') {
                    newInput.push_back('@');
                    newInput.push_back('.');
                }
            }
            warehouse.emplace_back(newInput);
        } else {
            moves.insert(moves.size(), line);
        }
    }

    std::pair<int, int> pos;
    for (int y = 0; y < warehouse.size(); y++) {
        std::cout << warehouse[y] << "\n";

        int maybe = warehouse[y].find('@');
        if (maybe != -1) {
            pos = {maybe, y};
        }
    }
    std::cout << "\n";
    std::cout << "Moves: " << moves << "\n\n";

    std::cout << "Position: (" << pos.first << ", " << pos.second << ")\n";

    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);

    std::string buffer;
    bool manual = true;
    for (int i = 0; i < moves.size(); i++) {
        if (manual) {
            uint8_t b1; 
            uint8_t b2; 
            uint8_t b3; 
            getinput:
            b1 = std::cin.get();
            b2 = std::cin.get();
            b3 = std::cin.get();
            printf("Raw bytes: %X %X %X\n", b1, b2, b3);
            if (b1 != 0x1B) goto getinput;
            if (b2 != 0x5B) goto getinput;
            if (b3 == 0x41) moves[i] = '^';
            else if (b3 == 0x42) moves[i] = 'v';
            else if (b3 == 0x43) moves[i] = '>';
            else if (b3 == 0x44) moves[i] = '<';
            else goto getinput;
        }

        buffer.clear();
        buffer.append("\033c");
        buffer.append("Move: " + moves[i] + '\n');
        attemptMove(pos, moves[i]);

        for (int y = 0; y < warehouse.size(); y++) {
            buffer.push_back('\n');
            buffer.append(warehouse[y]);
        }

        std::cout << buffer;
    }

    int total = 0;
    int boxCount = 0;
    for (int y = 0; y < warehouse.size(); y++) {
        for (int x = 0; x < warehouse[0].size(); x++) {
            if (warehouse[y][x] == '[') {
                total += 100 * y + x;
                boxCount++;
            }
        }
    }
    std::cout << "Total: " << total << "\n";
    std::cout << "Box count: " << boxCount << "\n";
}

}