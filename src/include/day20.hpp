#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

namespace Day20 {

std::vector<std::string> input;

std::vector<std::vector<int>> distances;

void floodFill(int x, int y, int dist) {
    if (input[y][x] == '#') return;

    if (distances[y][x] != -1) return;
    distances[y][x] = dist;

    floodFill(x-1, y, dist+1);
    floodFill(x+1, y, dist+1);
    floodFill(x, y-1, dist+1);
    floodFill(x, y+1, dist+1);
}

void run() {
    std::ifstream file("inputs/day20.txt");
    std::string line;

    while (std::getline(file, line)) {
        input.emplace_back(line);
    }

    for (int y = 0; y < input.size(); y++) {
        std::cout << input[y] << "\n";
    }
    std::cout << "\n\n";

    // Traverse from start and find distances at every point
    int startX = 0;
    int startY = 0;
    for (int y = 0; y < input.size(); y++) {
        std::vector<int> blah;
        for (int x = 0; x < input.size(); x++) {
            if (input[y][x] == 'S') {
                startX = x;
                startY = y;
            }
            blah.emplace_back(-1);
        }
        distances.emplace_back(blah);
    }

    floodFill(startX, startY, 0);
    for (int y = 0; y < distances.size(); y++) {
        for (int x = 0; x < distances[0].size(); x++) {
            printf("%02i ", distances[y][x]);
        }
        std::cout << "\n";
    }


    // Go through and for every wall try and see if the difference between the two numbers is 102
    int total = 0;
    int goalDistance = 100;
    for (int y = 1; y < input.size() - 1; y++) {
        for (int x = 1; x < input[0].size() - 1; x++) {
            if (input[y][x] != '#') continue;

            int top = distances[y-1][x];
            int bottom = distances[y+1][x];
            int left = distances[y][x-1];
            int right = distances[y][x+1];

            if (abs(top - bottom) >= goalDistance + 2 && top != -1 && bottom != -1) total++;
            if (abs(left - right) >= goalDistance + 2 && left != -1 && right != -1) total++;
        }
    }
    std::cout << "Total shortcuts: " << total << "\n";

    // Go through pairs of points rather than adjecencys like part 1
    int maxDist = 20;
    total = 0;
    for (int y1 = 1; y1 < input.size(); y1++) {
        for (int x1 = 1; x1 < input[0].size(); x1++) {
            for (int y2 = 1; y2 < input.size(); y2++) {
                for (int x2 = 1; x2 < input[0].size(); x2++) {
                    // First check that both are '.'
                    if (input[y1][x1] == '#') continue;
                    if (input[y2][x2] == '#') continue;

                    // Then check they're the right distance
                    int dist = abs(x1 - x2) + abs(y1 - y2);
                    if (dist > maxDist || dist == 0) continue;

                    int cheat = abs(distances[y1][x1] - distances[y2][x2]);
                    if (cheat > goalDistance + dist - 2) {
                        total++;
                    }
                }
            }
        }
    }
    total /= 2; // Because this double counts lol
    std::cout << "Total shortcuts (part 2): " << total << "\n";
}

}