#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day6 {

std::vector<std::string> firstMap;
std::vector<std::string> map;

int maxsHit = 0;

std::map<std::vector<std::pair<int, int>>, bool> foundTriples;

void simulateGuard() {
    for (int y = 0; y < map.size(); y++) {
        std::cout << map[y] << "\n";
    }
    std::cout << "\n";

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == '^') {
                // If at the top of the map, the guard has left. Return.
                if (y == 0) {
                    map[y][x] = 'X';
                    return;
                }
                if (map[y-1][x] != '#') { // If no obstacle, move
                    map[y-1][x] = '^';
                    map[y][x] = 'X';
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '>';
                }
                simulateGuard();
                return;
            }
            if (map[y][x] == '>') {
                // If at the right of the map, the guard has left. Return.
                if (x == map[0].size() - 1) {
                    map[y][x] = 'X';
                    return;
                }
                if (map[y][x+1] != '#') { // If no obstacle, move
                    map[y][x+1] = '>';
                    map[y][x] = 'X';
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = 'v';
                }
                simulateGuard();
                return;
            }
            if (map[y][x] == 'v') {
                // If at the bottom of the map, the guard has left. Return.
                if (y == map.size() - 1) {
                    map[y][x] = 'X';
                    return;
                }
                if (map[y+1][x] != '#') { // If no obstacle, move
                    map[y+1][x] = 'v';
                    map[y][x] = 'X';
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '<';
                }
                simulateGuard();
                return;
            }
            if (map[y][x] == '<') {
                // If at the left of the map, the guard has left. Return.
                if (x == 0) {
                    map[y][x] = 'X';
                    return;
                }
                if (map[y][x-1] != '#') { // If no obstacle, move
                    map[y][x-1] = '<';
                    map[y][x] = 'X';
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '^';
                }
                simulateGuard();
                return;
            }
        }
    }
}

void simulateGuard2withIntersections() {
    for (int y = 0; y < map.size(); y++) {
        std::cout << map[y] << "\n";
    }
    std::cout << "\n";

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == '^') {
                // If at the top of the map, the guard has left. Return.
                if (y == 0) {
                    map[y][x] = '|';
                    return;
                }
                if (map[y-1][x] != '#') { // If no obstacle, move
                    map[y-1][x] = '^';
                    if (map[y][x-1] == '#' || (map[y][x-1] != '.' && map[y][x+1] != '.' && map[y][x-1] != '|' && map[y][x+1] != '|')) { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '|';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '>';
                }
                simulateGuard2withIntersections();
            }
            if (map[y][x] == '>') {
                // If at the right of the map, the guard has left. Return.
                if (x == map[0].size() - 1) {
                    map[y][x] = '-';
                    return;
                }
                if (map[y][x+1] != '#') { // If no obstacle, move
                    map[y][x+1] = '>';
                    if (map[y-1][x] == '#' || (map[y-1][x] != '.' && map[y+1][x] != '.' && map[y-1][x] != '-' && map[y+1][x] != '-')) { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '-';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = 'v';
                }
                simulateGuard2withIntersections();
            }
            if (map[y][x] == 'v') {
                // If at the bottom of the map, the guard has left. Return.
                if (y == map.size() - 1) {
                    map[y][x] = '|';
                    return;
                }
                if (map[y+1][x] != '#') { // If no obstacle, move
                    map[y+1][x] = 'v';
                    if (map[y][x+1] == '#' || (map[y][x-1] != '.' && map[y][x+1] != '.' && map[y][x-1] != '|' && map[y][x+1] != '|')) { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '|';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '<';
                }
                simulateGuard2withIntersections();
            }
            if (map[y][x] == '<') {
                // If at the left of the map, the guard has left. Return.
                if (x == 0) {
                    map[y][x] = '-';
                    return;
                }
                if (map[y][x-1] != '#') { // If no obstacle, move
                    map[y][x-1] = '<';
                    if (map[y+1][x] == '#'|| (map[y-1][x] != '.' && map[y+1][x] != '.' && map[y-1][x] != '-' && map[y+1][x] != '-')) { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '-';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '^';
                }
                simulateGuard2withIntersections();
            }
        }
    }
}

void simulateGuard2(int n, int max) {
    if (n == max) {
        std::cout << "Infinite loop suspected, total suspected: " << maxsHit << "\n";
        maxsHit++;
        return;
    }

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == '^') {
                // If at the top of the map, the guard has left. Return.
                if (y == 0) {
                    map[y][x] = '|';
                    return;
                }
                if (map[y-1][x] != '#') { // If no obstacle, move
                    map[y-1][x] = '^';
                    if (map[y][x-1] == '#') { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '|';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '>';
                }
                simulateGuard2(++n, max);
                return;
            }
            if (map[y][x] == '>') {
                // If at the right of the map, the guard has left. Return.
                if (x == map[0].size() - 1) {
                    map[y][x] = '-';
                    return;
                }
                if (map[y][x+1] != '#') { // If no obstacle, move
                    map[y][x+1] = '>';
                    if (map[y-1][x] == '#') { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '-';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = 'v';
                }
                simulateGuard2(++n, max);
                return;
            }
            if (map[y][x] == 'v') {
                // If at the bottom of the map, the guard has left. Return.
                if (y == map.size() - 1) {
                    map[y][x] = '|';
                    return;
                }
                if (map[y+1][x] != '#') { // If no obstacle, move
                    map[y+1][x] = 'v';
                    if (map[y][x+1] == '#') { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '|';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '<';
                }
                simulateGuard2(++n, max);
                return;
            }
            if (map[y][x] == '<') {
                // If at the left of the map, the guard has left. Return.
                if (x == 0) {
                    map[y][x] = '-';
                    return;
                }
                if (map[y][x-1] != '#') { // If no obstacle, move
                    map[y][x-1] = '<';
                    if (map[y+1][x] == '#') { // Find obstruction or other paths and change symbol
                        map[y][x] = '+';
                    } else {
                        map[y][x] = '-';
                    }
                } else { // If there is an obstacle, turn 90 degrees
                    map[y][x] = '^';
                }
                simulateGuard2(++n, max);
                return;
            }
        }
    }
}

bool findLoop(int& total) {
    for (int y = 0; y < map.size(); y++) {
        std::cout << map[y] << "\n";
    }
    std::cout << "\n";

    // Loop through and find the turns - I will mark direction changes with a + and change the intersections to do nothing
    std::pair<int, int> initial;
    std::pair<int, int> columnTurn;
    std::pair<int, int> rowTurn;

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == '+') { // If we find a turn, try and find two others along the column and row
                initial = {x, y};
                columnTurn = {-1, -1};
                rowTurn = {-1, -1};
                std::vector<std::pair<int, int>> columns;
                std::vector<std::pair<int, int>> rows;
                for (int dy = 0; dy < map.size(); dy++) {
                    if (dy == y) continue;
                    if (map[dy][x] == '+') { // Found one other
                        columns.emplace_back(x, dy);
                    }
                }
                for (int dx = 0; dx < map[0].size(); dx++) {
                    if (dx == x) continue;
                    if (map[y][dx] == '+') { // Found one other
                        rows.emplace_back(dx, y);
                    }
                }
                for (int i = 0; i < columns.size(); i++) {
                    for (int j = 0; j < rows.size(); j++) {
                        if (!foundTriples[{initial, rows[j], columns[i]}]) {
                            foundTriples.emplace(std::vector{initial, rows[j], columns[i]}, true);
                            foundTriples.emplace(std::vector{columns[i], rows[j], initial}, true);
                            foundTriples.emplace(std::vector{rows[j], initial, columns[i]}, true);
                            foundTriples.emplace(std::vector{columns[i], initial, rows[j]}, true);
                            foundTriples.emplace(std::vector{rows[j], columns[i], initial}, true);
                            foundTriples.emplace(std::vector{initial, columns[i], rows[j]}, true);
                            total++;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void run() {
    std::ifstream file("inputs/day6.txt");
    std::string input;
    
    while (std::getline(file, input)) {
        map.emplace_back(input);
    }

    // Part 1

    std::vector<std::string> mapCopy = map;
    simulateGuard();

    int total = 0;
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == 'X') total++;
        }
    }
    std::cout << "Total travelled: " << total << "\n";
    
    // Part 2

    int max = 10000;
    // Nevermind I'm going to do this stupidly instead
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            map = mapCopy;
            if (map[y][x] == '^') continue;
            map[y][x] = '#';
            simulateGuard2(0, max);
        }
    }

    std::cout << "Total loops suspected: " << maxsHit << "\n";

    // Essentially what you do is find a triplet of blockers, all forming the corners of the same square (not quite but kinda)
    // You then place a blocker where the forth corner would be, and you get an infinate loop
    /*
    int totalLoops = 0;

    while (findLoop(totalLoops));

    std::cout << "Total loops: " << totalLoops << "\n";
    */
}

}