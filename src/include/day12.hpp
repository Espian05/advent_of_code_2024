#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day12 {

std::vector<std::vector<std::pair<char, bool>>> input;

std::pair<int, int> recurse(int y, int x, char previous) {
    input[y][x].second = true;
    std::cout << "(" << x << ", " << y << "), " << previous << "\n";

    if (input[y][x].first == previous) {
        int perimeter = 4;
        std::pair<int, int> total = {1, 0};
        if (y > 0) {
            if (input[y-1][x].first == previous) {
                if (input[y-1][x].second == false) {
                    std::pair<int, int> temp = recurse(y-1, x, previous);
                    total.first += temp.first;
                    total.second += temp.second;
                }
                perimeter--;
            }
        }
        if (x > 0) {
            if (input[y][x-1].first == previous) {
                if (input[y][x-1].second == false) {
                    std::pair<int, int> temp = recurse(y, x-1, previous);
                    total.first += temp.first;
                    total.second += temp.second;
                }
                perimeter--;
            }
        }
        if (y < input.size()-1) {
            if (input[y+1][x].first == previous) {
                if (input[y+1][x].second == false) {
                    std::pair<int, int> temp = recurse(y+1, x, previous);
                    total.first += temp.first;
                    total.second += temp.second;
                }
                perimeter--;
            }
        }
        if (x < input[0].size()-1) {
            if (input[y][x+1].first == previous) {
                if (input[y][x+1].second == false) {
                    std::pair<int, int> temp = recurse(y, x+1, previous);
                    total.first += temp.first;
                    total.second += temp.second;
                }
                perimeter--;
            }
        }
        total.second += perimeter;
        return total;
    }
}

std::vector<std::pair<int, int>> findShape(int y, int x, char type) {
    input[y][x].second = true;

    if (input[y][x].first == type) {
        std::vector<std::pair<int, int>> connectedTo;
        int surroundedBy = 0;
        if (y > 0) {
            if (input[y-1][x].first == type) {
                if (input[y-1][x].second == false) {
                    std::vector<std::pair<int, int>> temp = findShape(y-1, x, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        if (x > 0) {
            if (input[y][x-1].first == type) {
                if (input[y][x-1].second == false) {
                    std::vector<std::pair<int, int>> temp = findShape(y, x-1, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        if (y < input.size()-1) {
            if (input[y+1][x].first == type) {
                if (input[y+1][x].second == false) {
                    std::vector<std::pair<int, int>> temp = findShape(y+1, x, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        if (x < input[0].size()-1) {
            if (input[y][x+1].first == type) {
                if (input[y][x+1].second == false) {
                    std::vector<std::pair<int, int>> temp = findShape(y, x+1, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        if (surroundedBy < 4) {
            connectedTo.emplace_back(y, x);
        }
        return connectedTo;
    }
}

std::vector<std::pair<int, int>> findFullShape(int y, int x, char type) {
    input[y][x].second = true;

    if (input[y][x].first == type) {
        std::vector<std::pair<int, int>> connectedTo;
        int surroundedBy = 0;
        if (y > 0) {
            if (input[y-1][x].first == type) {
                if (input[y-1][x].second == false) {
                    std::vector<std::pair<int, int>> temp = findFullShape(y-1, x, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        if (x > 0) {
            if (input[y][x-1].first == type) {
                if (input[y][x-1].second == false) {
                    std::vector<std::pair<int, int>> temp = findFullShape(y, x-1, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        if (y < input.size()-1) {
            if (input[y+1][x].first == type) {
                if (input[y+1][x].second == false) {
                    std::vector<std::pair<int, int>> temp = findFullShape(y+1, x, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        if (x < input[0].size()-1) {
            if (input[y][x+1].first == type) {
                if (input[y][x+1].second == false) {
                    std::vector<std::pair<int, int>> temp = findFullShape(y, x+1, type);
                    for (auto s : temp) {
                        connectedTo.emplace_back(s);
                    }
                }
                surroundedBy++;
            }
        }
        connectedTo.emplace_back(y, x);
        return connectedTo;
    }
}

void run() {
    std::ifstream file("inputs/day12.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        std::vector<std::pair<char, bool>> row;
        for (char& c : line) row.emplace_back(c, false);
        input.emplace_back(row);
    }

    int total = 0;
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[0].size(); x++) {
            if (input[y][x].second == false) {
                std::pair<int, int> temp = recurse(y, x, input[y][x].first);
                total += temp.first * temp.second;
                std::cout << "Stats for " << input[y][x].first << " were Area: " << temp.first << "\tPerimeter: " << temp.second << "\n";
            }
        }
    }
    std::cout << "Total price: " << total << "\n";

    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[0].size(); x++) {
            input[y][x].second = false;
        }
    }

    total = 0;
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[0].size(); x++) {
            if (input[y][x].second == false) {
                std::vector<std::pair<int, int>> shape = findFullShape(y, x, input[y][x].first);
                std::cout << "\nShape for " << input[y][x].first << " found, consists of:\n";
                for (int i = 0; i < shape.size(); i++) {
                    std::cout << shape[i].first << ", " << shape[i].second << "\n";
                }

                // Find bounds of shape
                int minX = 1000;
                int minY = 1000;
                int maxX = -1;
                int maxY = -1;
                for (auto c : shape) {
                    if (c.second > maxX) maxX = c.second;
                    if (c.second < minX) minX = c.second;
                    if (c.first > maxY) maxY = c.first;
                    if (c.first < minY) minY = c.first;
                }
                // Increase both max values by 4 to add a padding layer so I don't have to worry about bounds
                int lengthX = (maxX - minX) * 3 + 7;
                int lengthY = (maxY - minY) * 3 + 7;
                std::vector<std::vector<char>> perimeter;
                for (int y = 0; y < lengthY; y++) {
                    std::vector<char> row;
                    for (int x = 0; x < lengthX; x++) {
                        row.emplace_back('.');
                    }
                    perimeter.emplace_back(row);
                }

                // Add hashes
                for (auto c : shape) {
                    int x = (c.second - minX) * 3 + 2;
                    int y = (c.first - minY) * 3 + 2;
                    for (int dy = 0; dy < 3; dy++) {
                        for (int dx = 0; dx < 3; dx++) {
                            perimeter[y + dy][x + dx] = '#';
                        }
                    }
                }

                // Add straight bits
                for (int y = 1; y < lengthY - 1; y++) {
                    for (int x = 1; x < lengthX - 1; x++) {
                        if (perimeter[y][x] == '#') {
                            if (perimeter[y][x-1] != '#') if (perimeter[y][x-1] != '.') perimeter[y][x-1] = '+'; else perimeter[y][x-1] = '|';
                            if (perimeter[y][x+1] != '#') if (perimeter[y][x+1] != '.') perimeter[y][x+1] = '+'; else perimeter[y][x+1] = '|';
                            if (perimeter[y-1][x] != '#') if (perimeter[y-1][x] != '.') perimeter[y-1][x] = '+'; else perimeter[y-1][x] = '-';
                            if (perimeter[y+1][x] != '#') if (perimeter[y+1][x] != '.') perimeter[y+1][x] = '+'; else perimeter[y+1][x] = '-';
                        }
                    }
                }

                // Add crosses where two sides intersect
                for (int y = 1; y < lengthY - 1; y++) {
                    for (int x = 1; x < lengthX - 1; x++) {
                        if (perimeter[y][x] == '.') {
                            int xInbound = 0;
                            int yInbound = 0;

                            if (perimeter[y][x-1] == '-' || perimeter[y][x-1] == '+') xInbound++;
                            if (perimeter[y][x+1] == '-' || perimeter[y][x+1] == '+') xInbound++;
                            if (perimeter[y-1][x] == '|' || perimeter[y-1][x] == '+') yInbound++;
                            if (perimeter[y+1][x] == '|' || perimeter[y+1][x] == '+') yInbound++;

                            if (xInbound * yInbound != 0) {
                                // Double check they do actually have a # nearby
                                if (perimeter[y-1][x-1] == '#') perimeter[y][x] = '+';
                                if (perimeter[y-1][x+1] == '#') perimeter[y][x] = '+';
                                if (perimeter[y+1][x-1] == '#') perimeter[y][x] = '+';
                                if (perimeter[y+1][x+1] == '#') perimeter[y][x] = '+';
                            }
                        }
                        if (perimeter[y][x] == '-') {
                            if (perimeter[y-1][x] == '|' || perimeter[y-1][x] == '+') perimeter[y][x] = '+';
                            if (perimeter[y+1][x] == '|' || perimeter[y+1][x] == '+') perimeter[y][x] = '+';
                        }
                        if (perimeter[y][x] == '|') {
                            if (perimeter[y][x-1] == '-' || perimeter[y][x-1] == '+') perimeter[y][x] = '+';
                            if (perimeter[y][x+1] == '-' || perimeter[y][x+1] == '+') perimeter[y][x] = '+';
                        }
                    }
                }

                int sides = 0;
                for (int y = 0; y < lengthY; y++) {
                    for (int x = 0; x < lengthX; x++) {
                        std::cout << perimeter[y][x];
                        if (perimeter[y][x] == '+') sides++;
                    }
                    std::cout << "\n";
                }
                total += sides * shape.size();
                std::cout << sides << " sides found.\n";
                std::cout << shape.size() << " area, " << sides << " sides, total cost: " << sides * shape.size() << "\n";
            }
        }
    }
    std::cout << "Cheaper price: " << total << "\n";
}

}