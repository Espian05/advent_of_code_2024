#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

namespace Day18 {

std::vector<std::string> memory;

const int maxX = 71;
const int maxY = 71;

struct Node {
    int x;
    int y;
    int dist;
};

std::vector<Node> graph;
std::vector<int> unvisited;

std::vector<std::pair<int, int>> bytesToFall;

void run() {
    std::ifstream file("inputs/day18.txt");
    std::string line;

    {
        std::string temp = "";
        for (int x = 0; x < maxX; x++) {
            temp.push_back('.');
        }

        for (int y = 0; y < maxY; y++) {
            memory.emplace_back(temp);
        }
    }

    int n = 0;
    while (std::getline(file, line)) {
        int firstComma = line.find(',');
        int x = std::stoi(line.substr(0, firstComma));
        int y = std::stoi(line.substr(firstComma+1));
        printf("%i, %i\n", x, y);
        if (n < 1024) {
            memory[y][x] = '#';
        } else {
            bytesToFall.emplace_back(x, y);
        }
        n++;
    }

    int i = 0;
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if (memory[y][x] == '#') continue;
            Node newNode;
            newNode.x = x;
            newNode.y = y;
            newNode.dist = 1000000000;
            graph.emplace_back(newNode);
            unvisited.emplace_back(i);
            i++;
        }
    }

    for (int y = 0; y < memory.size(); y++) {
        std::cout << memory[y] << "\n";
    }

    {
        graph[unvisited[0]].dist = 0;
        while(true) {
            int lowestDist = 1000000000;
            Node lowestNode;
            bool found = false;
            int index = 0;
            for (int i = 0; i < unvisited.size(); i++) {
                if (graph[unvisited[i]].dist < lowestDist) {
                    lowestDist = graph[unvisited[i]].dist;
                    lowestNode = graph[unvisited[i]];
                    found = true;
                    index = i;
                }
            }
            if (!found) break;

            printf("(%i, %i)\n", lowestNode.x, lowestNode.y);

            if (lowestNode.x > 0) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x - 1 && graph[unvisited[i]].y == lowestNode.y) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }
            if (lowestNode.y > 0) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x && graph[unvisited[i]].y == lowestNode.y - 1) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }
            if (lowestNode.x < maxX - 1) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x + 1 && graph[unvisited[i]].y == lowestNode.y) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }
            if (lowestNode.y < maxY - 1) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x && graph[unvisited[i]].y == lowestNode.y + 1) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }

            unvisited.erase(unvisited.begin() + index);
        }

    std::cout << "Shortest path is: " << graph[graph.size() - 1].dist << "\n";
    }

    int byteN = 0;
    while (true) {
        std::pair<int, int> nextByte = bytesToFall[byteN];
        byteN++;
        memory[nextByte.second][nextByte.first] = '#';
        printf("(%i, %i)\n", nextByte.first, nextByte.second);
        if (byteN == bytesToFall.size()) {
            std::cout << "What the fuck do you mean all the bytes fell.\n";
        }

        graph.clear();
        unvisited.clear();
        int i = 0;
        for (int y = 0; y < maxY; y++) {
            for (int x = 0; x < maxX; x++) {
                if (memory[y][x] == '#') continue;
                Node newNode;
                newNode.x = x;
                newNode.y = y;
                newNode.dist = 1000000000;
                graph.emplace_back(newNode);
                unvisited.emplace_back(i);
                i++;
            }
        }

        graph[unvisited[0]].dist = 0;
        while(true) {
            int lowestDist = 1000000000;
            Node lowestNode;
            bool found = false;
            int index = 0;
            for (int i = 0; i < unvisited.size(); i++) {
                if (graph[unvisited[i]].dist < lowestDist) {
                    lowestDist = graph[unvisited[i]].dist;
                    lowestNode = graph[unvisited[i]];
                    found = true;
                    index = i;
                }
            }
            if (!found) break;

            if (lowestNode.x > 0) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x - 1 && graph[unvisited[i]].y == lowestNode.y) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }
            if (lowestNode.y > 0) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x && graph[unvisited[i]].y == lowestNode.y - 1) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }
            if (lowestNode.x < maxX - 1) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x + 1 && graph[unvisited[i]].y == lowestNode.y) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }
            if (lowestNode.y < maxY - 1) {
                for (int i = 0; i < unvisited.size(); i++) {
                    if (graph[unvisited[i]].x == lowestNode.x && graph[unvisited[i]].y == lowestNode.y + 1) {
                        if (graph[unvisited[i]].dist > lowestNode.dist + 1) {
                            graph[unvisited[i]].dist = lowestNode.dist + 1;
                        }
                    }
                }
            }

            unvisited.erase(unvisited.begin() + index);
        }

        if (graph[graph.size() - 1].dist == 1000000000) break;
    }
}

}