#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day16 {

std::vector<std::string> maze;
std::vector<std::string> trackedMaze;

std::map<std::vector<int>, int> previous;

std::map<std::pair<int, int>, bool> partOfPaths;

int bestPathScore = 147628;

int countSetBits(int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if ((1 << i) & n) total++;
    }
    return total;
}

uint8_t getDirectionsFromPoint(int x, int y) {
    uint8_t output = 0;

    if (maze[y-1][x] == '.') output |= 1;
    if (maze[y][x+1] == '.') output |= 2;
    if (maze[y+1][x] == '.') output |= 4;
    if (maze[y][x-1] == '.') output |= 8;

    return output;
}

std::pair<std::vector<int>, std::vector<std::pair<int, int>>> findNextIntersection(int x, int y, uint8_t direction, 
                                                        int total, std::vector<std::pair<int, int>> trackedPlaces) {
    uint8_t directions = getDirectionsFromPoint(x, y);
    trackedPlaces.emplace_back(std::pair(x, y));
    //printf("Directions from point (%i, %i): %04b\tCurrent total: %i\n", x, y, directions, total);
    int directionCount = countSetBits(directions);
    if (directionCount != 2) {
        //printf("Intersection located at (%i, %i)\n", x, y);
        trackedMaze[y][x] = '+';
        return std::pair(std::vector<int>{x, y, direction, total}, trackedPlaces);
    }

    // Iterate in that direction until an intersection is found
    if (direction == 1) {
        if (maze[y-1][x] != '#') {
            trackedMaze[y][x] = '^';
            return findNextIntersection(x, y-1, 1, total + 1, trackedPlaces);
        }
        if (directions & 2) {
            trackedMaze[y][x] = '>';
            return findNextIntersection(x+1, y, 2, total + 1001, trackedPlaces);
        }
        if (directions & 8) {
            trackedMaze[y][x] = '<';
            return findNextIntersection(x-1, y, 8, total + 1001, trackedPlaces);
        }
    }
    if (direction == 2) {
        if (maze[y][x+1] != '#') {
            trackedMaze[y][x] = '>';
            return findNextIntersection(x+1, y, 2, total + 1, trackedPlaces);
        }
        if (directions & 1) {
            trackedMaze[y][x] = '^';
            return findNextIntersection(x, y-1, 1, total + 1001, trackedPlaces);
        }
        if (directions & 4) {
            trackedMaze[y][x] = 'v';
            return findNextIntersection(x, y+1, 4, total + 1001, trackedPlaces);
        }
    }
    if (direction == 4) {
        if (maze[y+1][x] != '#') {
            trackedMaze[y][x] = 'v';
            return findNextIntersection(x, y+1, 4, total + 1, trackedPlaces);
        }
        if (directions & 2) {
            trackedMaze[y][x] = '>';
            return findNextIntersection(x+1, y, 2, total + 1001, trackedPlaces);
        }
        if (directions & 8) {
            trackedMaze[y][x] = '<';
            return findNextIntersection(x-1, y, 8, total + 1001, trackedPlaces);
        }
    }
    if (direction == 8) {
        if (maze[y][x-1] != '#') {
            trackedMaze[y][x] = '<';
            return findNextIntersection(x-1, y, 8, total + 1, trackedPlaces);
        }
        if (directions & 1) {
            trackedMaze[y][x] = '^';
            return findNextIntersection(x, y-1, 1, total + 1001, trackedPlaces);
        }
        if (directions & 4) {
            trackedMaze[y][x] = 'v';
            return findNextIntersection(x, y+1, 4, total + 1001, trackedPlaces);
        }
    }
    return std::pair(std::vector<int>{x, y, direction, total}, trackedPlaces);
}

std::pair<int, std::vector<std::pair<int, int>>> searchMaze(int x, int y, int direction, int total, std::vector<std::pair<int, int>> trackedPlaces) {
    if (total > bestPathScore) return std::pair(-1, trackedPlaces);

    uint8_t directions = getDirectionsFromPoint(x, y);
    //printf("Directions from point (%i, %i): %04b\tCurrent total: %i\n", x, y, directions, total);

    //for (int y = 0; y < trackedMaze.size(); y++) {
    //    std::cout << trackedMaze[y] << "\n";
    //}

    // Just in case an adjacent square is the end
    if (maze[y-1][x] == 'E') {
        printf("End found at (%i, %i)! Total points: %i\n", x, y, total + 1);
        if (total + 1 < bestPathScore) {
            partOfPaths.clear();
            bestPathScore = total + 1;
        }
        trackedPlaces.emplace_back(std::pair(x, y-1));
        if ((total + 1) == bestPathScore) {
            std::cout << "Adding shit to shit\n";
            for (int i = 0; i < trackedPlaces.size(); i++) {
                partOfPaths.emplace(trackedPlaces[i], true);
            }
        }
        return std::pair(total + 1, trackedPlaces);
    }
    if (maze[y][x+1] == 'E') {
        printf("End found at (%i, %i)! Total points: %i\n", x, y, total + 1);
        if (total + 1 < bestPathScore) {
            partOfPaths.clear();
            bestPathScore = total + 1;
        }
        trackedPlaces.emplace_back(std::pair(x+1, y));
        if ((total + 1) == bestPathScore) {
            std::cout << "Adding shit to shit\n";
            for (int i = 0; i < trackedPlaces.size(); i++) {
                partOfPaths.emplace(trackedPlaces[i], true);
            }
        }
        return std::pair(total + 1, trackedPlaces);
    }
    // If only one direction found, dead end :(
    if (directions == 1 || directions == 2 || directions == 4 || directions == 8) {
        //std::cout << "Dead end located at: (" << x << ", " << y << ")\n";
        return std::pair(-1, trackedPlaces);
    }

    // If identical state seen previously, also return -1 bc you must be in a loop
    if (previous.contains(std::vector<int>{x, y, direction})) {
        if (previous[std::vector<int>{x, y, direction}] < total) {
            //std::cout << "Looped at: (" << x << ", " << y << "), direction: " << direction << "\n";
            return std::pair(-1, trackedPlaces);
        } else {
            previous[std::vector<int>{x, y, direction}] = total;
        }
    }
    previous.emplace(std::vector<int>{x, y, direction}, total);

    // Otherwise, continue in all directions from point, finding the next intersection each time
    int smallestTotal = 1000000000;
    std::vector<std::pair<int, int>> partOfShortest;
    if (directions & 1) {
        std::pair<std::vector<int>, std::vector<std::pair<int, int>>> result = findNextIntersection(x, y-1, 1, total + 1, trackedPlaces);
        std::vector<int> next = result.first;
        if (direction != 1) next[3] += 1000;
        std::pair<int, std::vector<std::pair<int, int>>> output = searchMaze(next[0], next[1], next[2], next[3], result.second);
        if (output.first != -1) {
            if (output.first < smallestTotal) {
                smallestTotal = output.first;
                partOfShortest = output.second;
            }
        }
    }
    if (directions & 2) {
        std::pair<std::vector<int>, std::vector<std::pair<int, int>>> result = findNextIntersection(x+1, y, 2, total + 1, trackedPlaces);
        std::vector<int> next = result.first;
        if (direction != 2) next[3] += 1000;
        std::pair<int, std::vector<std::pair<int, int>>> output = searchMaze(next[0], next[1], next[2], next[3], result.second);
        if (output.first != -1) {
            if (output.first < smallestTotal) {
                smallestTotal = output.first;
                partOfShortest = output.second;
            }
        }
    }
    if (directions & 4) {
        std::pair<std::vector<int>, std::vector<std::pair<int, int>>> result = findNextIntersection(x, y+1, 4, total + 1, trackedPlaces);
        std::vector<int> next = result.first;
        if (direction != 4) next[3] += 1000;
        std::pair<int, std::vector<std::pair<int, int>>> output = searchMaze(next[0], next[1], next[2], next[3], result.second);
        if (output.first != -1) {
            if (output.first < smallestTotal) {
                smallestTotal = output.first;
                partOfShortest = output.second;
            }
        }
    }
    if (directions & 8) {
        std::pair<std::vector<int>, std::vector<std::pair<int, int>>> result = findNextIntersection(x-1, y, 8, total + 1, trackedPlaces);
        std::vector<int> next = result.first;
        if (direction != 8) next[3] += 1000;
        std::pair<int, std::vector<std::pair<int, int>>> output = searchMaze(next[0], next[1], next[2], next[3], result.second);
        if (output.first != -1) {
            if (output.first < smallestTotal) {
                smallestTotal = output.first;
                partOfShortest = output.second;
            }
        }
    }
    if (smallestTotal == 1000000000) smallestTotal = -1;

    return std::pair(smallestTotal, partOfShortest);
}

void run() {
    std::ifstream file("inputs/day16.txt");
    std::string line;

    while (std::getline(file, line)) {
        maze.emplace_back(line);
    }

    // Fuck it, recursion
    std::pair<int, std::vector<std::pair<int, int>>> output;
    std::vector<std::pair<int, int>> partOfShortest;
    for (int y = 0; y < maze.size(); y++) {
        int result = maze[y].find('S');

        if (result != -1) {
            std::cout << "Start found at: (" << result << ", " << y << ")\n";
            maze[y][result] = '.';
            trackedMaze = maze;
            output = searchMaze(result, y, 2, 0, partOfShortest);
            maze[y][result] = 'S';
        }
    }
    std::cout << "Output: " << output.first << "\n";
    std::cout << "Output (Part 2): " << partOfPaths.size() + 2 << "\n";
}

}