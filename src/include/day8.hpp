#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day8 {

std::vector<std::string> input;
std::vector<char> antennas;

void findAntennas() {
    // Identify how many unique antenna types there are
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            if (input[y][x] == '.') continue;
            if (std::find(antennas.begin(), antennas.end(), input[y][x]) == antennas.end()) {
                antennas.emplace_back(input[y][x]);
            }
        }
    }
}

void run() {
    std::ifstream file("inputs/day8.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        input.emplace_back(line);
    }

    findAntennas();

    std::cout << antennas.size() << "\n";

    // For each antenna type, create a completely separate map for antinodes
    std::vector<std::vector<std::vector<bool>>> allAntinodes;
    for (char& ch : antennas) {
        std::vector<std::vector<bool>> antinodes;


        std::vector<std::pair<int, int>> positions;

        for (int y = 0; y < input.size(); y++) {
            std::vector<bool> antis;
            for (int x = 0; x < input[y].size(); x++) {
                antis.emplace_back(false);
                if (input[y][x] != ch) continue;
                positions.emplace_back(x, y);
            }
            antinodes.emplace_back(antis);
        }

        // For every pair of antennas, find their offset, and attempt to create an antinode at that point
        for (int a = 0; a < positions.size(); a++) {
            for (int b = a+1; b < positions.size(); b++) {
                // a - 2b
                // b - 2a

                std::pair<int, int> pos1 = positions[a], pos2 = positions[b];

                int dx = pos1.first - pos2.first;
                int dy = pos1.second - pos2.second;

                // Put this offset at a, then the negative at b
                if (pos1.second + dy >= 0 && pos1.second + dy < antinodes.size() && pos1.first + dx >= 0 && pos1.first + dx < antinodes[0].size()) {
                    antinodes[pos1.second + dy][pos1.first + dx] = true;
                }
                if (pos2.second - dy >= 0 && pos2.second - dy < antinodes.size() && pos2.first - dx >= 0 && pos2.first - dx < antinodes[0].size()) {
                    antinodes[pos2.second - dy][pos2.first - dx] = true;
                }
            }
        }

        std::cout << "\n";
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[y].size(); x++) {
                std::cout << antinodes[y][x];
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        allAntinodes.emplace_back(antinodes);
    }

    // Combine all antinode maps
    std::vector<std::vector<bool>> combined;
    for (int y = 0; y < input.size(); y++) {
        std::vector<bool> antis;
        for (int x = 0; x < input[y].size(); x++) {
            bool state = false;
            for (int i = 0; i < allAntinodes.size(); i++) {
                if (allAntinodes[i][y][x]) {
                    state = true;
                    break;
                }
            }
            antis.emplace_back(state);
        }
        combined.emplace_back(antis);
    }

    int total = 0;
    std::cout << "\n";
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            std::cout << combined[y][x];
            if (combined[y][x]) total++;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "Total antinodes: " << total << "\n";

    allAntinodes.clear();

    for (char& ch : antennas) {
        std::vector<std::vector<bool>> antinodes;


        std::vector<std::pair<int, int>> positions;

        for (int y = 0; y < input.size(); y++) {
            std::vector<bool> antis;
            for (int x = 0; x < input[y].size(); x++) {
                antis.emplace_back(false);
                if (input[y][x] != ch) continue;
                positions.emplace_back(x, y);
            }
            antinodes.emplace_back(antis);
        }

        // For every pair of antennas, find their offset, and attempt to create an antinode at that point
        for (int a = 0; a < positions.size(); a++) {
            for (int b = 0; b < positions.size(); b++) {
                // a - 2b
                // b - 2a

                std::pair<int, int> pos1 = positions[a], pos2 = positions[b];

                int dx = pos1.first - pos2.first;
                int dy = pos1.second - pos2.second;

                int ddx = pos1.first - pos2.first;
                int ddy = pos1.second - pos2.second;

                // Put this offset at a, then the negative at b
                bool placing = true;
                while (placing) {
                    placing = false;
                    if (pos1.second + dy >= 0 && pos1.second + dy < antinodes.size() && pos1.first + dx >= 0 && pos1.first + dx < antinodes[0].size()) {
                        antinodes[pos1.second + dy][pos1.first + dx] = true;
                        placing = true;
                    }
                    if (pos2.second - dy >= 0 && pos2.second - dy < antinodes.size() && pos2.first - dx >= 0 && pos2.first - dx < antinodes[0].size()) {
                        antinodes[pos2.second - dy][pos2.first - dx] = true;
                        placing = true;
                    }
                    dx += ddx;
                    dy += ddy;
                    if (ddx == 0 && ddy == 0) placing = false;
                }
            }
        }

        std::cout << "\n";
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[y].size(); x++) {
                std::cout << antinodes[y][x];
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        allAntinodes.emplace_back(antinodes);
    }

    // Combine all antinode maps
    combined.clear();
    for (int y = 0; y < input.size(); y++) {
        std::vector<bool> antis;
        for (int x = 0; x < input[y].size(); x++) {
            bool state = false;
            for (int i = 0; i < allAntinodes.size(); i++) {
                if (allAntinodes[i][y][x]) {
                    state = true;
                    break;
                }
            }
            antis.emplace_back(state);
        }
        combined.emplace_back(antis);
    }

    total = 0;
    std::cout << "\n";
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            std::cout << combined[y][x];
            if (combined[y][x]) total++;
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    
    std::cout << "Total antinodes part2: " << total << "\n";
}

}