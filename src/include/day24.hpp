#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

#include <memory>

#include <bitset>
#include <unordered_set>

namespace Day24 {

std::map<std::string, bool> initialStates;

std::vector<std::string> ids;
std::vector<std::vector<std::string>> ANDS;
std::vector<std::vector<std::string>> XORS;
std::vector<std::vector<std::string>> ORS;

struct Node {
    std::string id;
    bool state = false;

    int tick = 0;

    enum gate { NONE, AND, OR, XOR };

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> parents;
    gate operation = NONE;

    Node (std::string id, bool s = false) : id(id), state(s) {}

    void propagateState(std::unordered_set<std::string>& visited) {
        if (!(parents.first && parents.second)) return;
        if (visited.count(id)) return; // Prevent revisiting the same node
        visited.insert(id);

        if (parents.first->tick == tick) parents.first->propagateState(visited);
        if (parents.second->tick == tick) parents.second->propagateState(visited);

        if (operation == AND) {
            state = parents.first->state & parents.second->state;
        } else if (operation == XOR) {
            state = parents.first->state ^ parents.second->state;
        } else if (operation == OR) {
            state = parents.first->state | parents.second->state;
        } else {
            // Operation == NONE and we do fuck all lol
        }

        tick++;
    }
};

void run() {
    srand(time(NULL));

    std::ifstream file("inputs/day24.txt");
    std::string line;
    bool initialState = true;

    while (std::getline(file, line)) {
        if (line.empty()) {
            initialState = false;
            continue;
        }
        if (initialState) {
            std::string str = line.substr(0, 3);
            bool value = (line[5] == '1');
            initialStates.emplace(str, value);
            ids.emplace_back(str);
        } else {
            std::string str1 = line.substr(0, 3);
            if (line[4] == 'X') {
                std::string str2 = line.substr(8, 3);
                std::string str3 = line.substr(15);
                ids.emplace_back(str3);
                XORS.emplace_back(std::vector<std::string>{str1, str2, str3});
            } else if (line[4] == 'A') {
                std::string str2 = line.substr(8, 3);
                std::string str3 = line.substr(15);
                ids.emplace_back(str3);
                ANDS.emplace_back(std::vector<std::string>{str1, str2, str3});
            } else if (line[4] == 'O') {
                std::string str2 = line.substr(7, 3);
                std::string str3 = line.substr(14);
                ids.emplace_back(str3);
                ORS.emplace_back(std::vector<std::string>{str1, str2, str3});
            }
        }
    }

    std::vector<std::shared_ptr<Node>> tree;
    for (auto& s : ids) {
        if (initialStates.contains(s)) {
            tree.emplace_back(std::make_shared<Node>(s, initialStates[s]));
        } else {
            tree.emplace_back(std::make_shared<Node>(s));
        }
    }
    std::vector<std::shared_ptr<Node>> treeCopy = tree;

    std::vector<std::shared_ptr<Node>> outputNodes;
    for (auto& node : tree) {
        if (node->id.starts_with('z')) {
            outputNodes.emplace_back(node);
        }
    }

    for (auto& gate : ANDS) {
        std::shared_ptr<Node> parent1;
        std::shared_ptr<Node> parent2;
        int count = 2;
        for (auto& node : tree) {
            if (node->id == gate[0]) {
                parent1 = node;
                count--;
            }
            if (node->id == gate[1]) {
                parent2 = node;
                count--;
            }
            if (!count) break;
        }

        for (auto& node : tree) {
            if (node->id == gate[2]) {
                node->parents.first = parent1;
                node->parents.second = parent2;
                node->operation = Node::AND;
            }
        }
    }
    for (auto& gate : ORS) {
        std::shared_ptr<Node> parent1;
        std::shared_ptr<Node> parent2;
        int count = 2;
        for (auto& node : tree) {
            if (node->id == gate[0]) {
                parent1 = node;
                count--;
            }
            if (node->id == gate[1]) {
                parent2 = node;
                count--;
            }
            if (!count) break;
        }

        for (auto& node : tree) {
            if (node->id == gate[2]) {
                node->parents.first = parent1;
                node->parents.second = parent2;
                node->operation = Node::OR;
            }
        }
    }
    for (auto& gate : XORS) {
        std::shared_ptr<Node> parent1;
        std::shared_ptr<Node> parent2;
        int count = 2;
        for (auto& node : tree) {
            if (node->id == gate[0]) {
                parent1 = node;
                count--;
            }
            if (node->id == gate[1]) {
                parent2 = node;
                count--;
            }
            if (!count) break;
        }

        for (auto& node : tree) {
            if (node->id == gate[2]) {
                node->parents.first = parent1;
                node->parents.second = parent2;
                node->operation = Node::XOR;
            }
        }
    }

    for (auto& node : tree) {
        std::cout << node->id << " : " << node->state << "\n";
    }

    long output = 0;
    std::unordered_set<std::string> visited;
    for (auto& node : outputNodes) {
        node->propagateState(visited);
        if (node->state) {
            output |= (1L << std::stoi(node->id.substr(1, 2)));
        }
    }

    for (auto& node : tree) {
        std::cout << node->id << " : " << node->state << "\n";
    }

    std::cout << "Output: " << output << "\n\n";

    long x = 0;
    long y = 0;
    for (auto& node : tree) {
        if (node->id.starts_with('x')) {
            if (node->state) {
                x |= (1L << std::stoi(node->id.substr(1, 2)));
            }
        } else 
        if (node->id.starts_with('y')) {
            if (node->state) {
                y |= (1L << std::stoi(node->id.substr(1, 2)));
            }
        }
    }
    long z = x + y;
    std::cout << "Input X: " << x << "\n";
    std::cout << "Input Y: " << y << "\n";
    std::cout << "Correct output: " << z << "\n\n";

    std::cout << "Part 2 shenanigans:\n";

    for (int i = 0; i < initialStates.size() / 2; i++) {
        for (auto& str : XORS) {
            if ((str[0][0] == 'x' || str[0][0] == 'y') && std::stoi(str[0].substr(1, 2)) == i) {
                std::cout << str[0] << " XOR " << str[1] << " -> " << str[2] << "\n";
                for (auto& str2 : XORS) {
                    if ((str2[0] == str[2]) || (str2[1] == str[2])) {
                        std::cout << str2[0] << " XOR " << str2[1] << " -> " << str2[2] << "\n";
                    }
                }
                for (auto& str2 : ANDS) {
                    if ((str2[0] == str[2]) || (str2[1] == str[2])) {
                        std::cout << str2[0] << " AND " << str2[1] << " -> " << str2[2] << "\n";
                    }
                }
            }
        }

        for (auto& str : ANDS) {
            if ((str[0][0] == 'x' || str[0][0] == 'y') && std::stoi(str[0].substr(1, 2)) == i) {
                std::cout << str[0] << " AND " << str[1] << " -> " << str[2] << "\n";
            }
        }

        std::cout << "\n";
    }

    return;

    // Actually fuck it, randomly swap until it gets there lmao
    std::vector<std::shared_ptr<Node>> bestTree = treeCopy;
    long bestDistance = abs(output - z);
    while(true) {
        tree = bestTree;

        std::vector<std::string> swaps;
        for (int i = 0; i < 4; i++) {
            int i1 = rand() % tree.size(); // Which node
            int i2 = rand() % tree.size(); // Which other node

            if (!(tree[i1]->parents.first && tree[i1]->parents.second && tree[i2]->parents.first && tree[i2]->parents.second)) {
                continue;
            }

            if (tree[i1]->id == tree[i2]->parents.first->id || 
                tree[i1]->id == tree[i2]->parents.second->id ||
                tree[i2]->id == tree[i1]->parents.first->id || 
                tree[i2]->id == tree[i1]->parents.second->id) {
                continue;
            }

            auto buffer = tree[i1]->parents.first;
            tree[i1]->parents.first = tree[i2]->parents.first;
            tree[i2]->parents.first = buffer;

            buffer = tree[i1]->parents.second;
            tree[i1]->parents.second = tree[i2]->parents.second;
            tree[i2]->parents.second = buffer;

            swaps.emplace_back(tree[i1]->id);
            swaps.emplace_back(tree[i2]->id);
        }

        std::vector<std::shared_ptr<Node>> randomTree = tree;

        output = 0;
        std::unordered_set<std::string> visited;
        for (auto& node : outputNodes) {
            node->propagateState(visited);
            if (node->state) {
                output |= (1L << std::stoi(node->id.substr(1, 2)));
            }
        }

        long distance = abs(output - z);
        if (distance < bestDistance) {
            std::cout << "New closest distance: " << distance << "\n";
            bestTree = randomTree;
            bestDistance = distance;
        }
        if (distance == 0) {
            std::cout << "Yo wut\n";

            for (std::string s : swaps) std::cout << s << ", ";
            std::cout << "\n";

            return;
        }
    }
}

}