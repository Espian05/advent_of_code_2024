#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

#include <memory>

#include <bitset>

namespace Day23 {

std::vector<std::pair<std::string, std::string>> input;

struct Node {
    std::string id;
    int index;

    std::vector<std::shared_ptr<Node>> connections;

    Node(std::string id, int i) : id(id), index(i) {}

    bool isConnectedTo(std::string targetId) {
        for (std::shared_ptr<Node> node : connections) {
            if (node->id == targetId) return true;
        }
        return false;
    }
};

struct Graph {
    std::vector<std::shared_ptr<Node>> nodes;

    bool hasNode(std::string id) {
        for (auto node : nodes) {
            if (node->id == id) return true;
        }
        return false;
    }

    void addNode(std::string id) {
        nodes.emplace_back(std::make_shared<Node>(id, nodes.size()));
    }

    std::shared_ptr<Node> getNode(std::string id) {
        for (auto node : nodes) {
            if (node->id == id) return node;
        }
        return nullptr;
    }

    bool hasConnection(std::string id1, std::string id2) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->id == id1) return nodes[i]->isConnectedTo(id2);
            if (nodes[i]->id == id2) return nodes[i]->isConnectedTo(id1);
        }
        return false;
    }

    bool addConnection(std::string id1, std::string id2) {
        std::shared_ptr<Node> node1 = getNode(id1);
        std::shared_ptr<Node> node2 = getNode(id2);

        if (!(node1 && node2)) return false; // If either is nullptr, invalid connection

        node1->connections.emplace_back(node2);
        node2->connections.emplace_back(node1);

        return true;
    }

    std::vector<std::vector<std::shared_ptr<Node>>> findCycles(int length) {
        std::vector<std::vector<std::shared_ptr<Node>>> result;

        // Get cycles, this also returns duplicates
        for (auto node : nodes) {
            std::vector<std::vector<std::shared_ptr<Node>>> temp = followCycle(node, length, {});
            if (!temp.empty()) result.insert(result.end(), temp.begin(), temp.end());
        }

        std::cout << "Nodes size: " << nodes.size() << "\n";
        std::cout << "Results size before: " << result.size() << "\n";

        // Need to prune permutations
        std::vector<std::bitset<1000>> bitmasks;
        std::vector<std::vector<std::shared_ptr<Node>>> output;
        for (auto& arr : result) {
            bool good = true;
            std::bitset<1000> bitmask = 0;

            for (int k = 0; k < arr.size(); k++) {
                bitmask |= (std::bitset<1000>(1) << (arr[k]->index));
            }

            for (std::bitset<1000> mask : bitmasks) {
                if ((mask & bitmask) == bitmask) {
                    good = false;
                    break;
                }
            }
            if (good) {
                output.emplace_back(arr);
                bitmasks.emplace_back(bitmask);
            }
        }

        std::cout << "Results size after: " << output.size() << "\n";

        return output;
    }

    std::vector<std::vector<std::shared_ptr<Node>>> followCycle(std::shared_ptr<Node> node, int length, std::vector<std::shared_ptr<Node>> trace) {
        if (length == 0) {
            if (node == trace[0]) return {trace};
            return {};
        }
        if (traceContains(trace, node)) return {};
        trace.emplace_back(node);

        std::vector<std::vector<std::shared_ptr<Node>>> result;
        for (auto conn : node->connections) {
            std::vector<std::vector<std::shared_ptr<Node>>> temp = followCycle(conn, length-1, trace);
            if (!temp.empty()) result.insert(result.end(), temp.begin(), temp.end());
        }
        return result;
    }

    bool traceContains(std::vector<std::shared_ptr<Node>> trace, std::shared_ptr<Node> node) {
        for (auto t : trace) {
            if (t->id == node->id) return true;
        }
        return false;
    }
};

void run() {
    std::ifstream file("inputs/day23.txt");
    std::string line;

    while (std::getline(file, line)) {
       input.emplace_back(std::pair<std::string, std::string>(line.substr(0, 2), line.substr(3, 5)));
    }

    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i].first << " : " << input[i].second << "\n";
    }

    Graph graph;

    for (int i = 0; i < input.size(); i++) {
        if (!graph.hasNode(input[i].first)) {
            graph.addNode(input[i].first);
        }
        if (!graph.hasNode(input[i].second)) {
            graph.addNode(input[i].second);
        }
        graph.addConnection(input[i].first, input[i].second);
    }

    for (int i = 0; i < graph.nodes.size(); i++) {
        std::cout << "\n";
        for (std::shared_ptr<Node> node : graph.nodes[i]->connections) {
            std::cout << graph.nodes[i]->id << " -> " << node->id << "\n";
        }
        std::cout << "\n";
    }

    std::vector<std::vector<std::shared_ptr<Node>>> result = graph.findCycles(3);

    for (std::vector<std::shared_ptr<Node>> nodes : result) {
        std::cout << nodes[0]->id << " -> ";
        std::cout << nodes[1]->id << " -> ";
        std::cout << nodes[2]->id << "\n";
    }

    // Count at least 1 starting with a t
    int total = 0;
    for (auto nodes : result) {
        if (nodes[0]->id[0] == 't') {
            total++;
            continue;
        }
        if (nodes[1]->id[0] == 't') {
            total++;
            continue;
        }
        if (nodes[2]->id[0] == 't') {
            total++;
            continue;
        }
    }
    std::cout << "Total: " << total << "\n\n";

    /*
    int largest = 2;
    while(true) {
        std::vector<std::vector<std::shared_ptr<Node>>> result = graph.findCycles(largest);
        if (result.size() == 1) {
            std::cout << "Largest network: ";
            for (int i = 0; i < result[0].size(); i++) {
                std::cout << result[0][i]->id << "\n";
            }
            std::cout << "\n";
            return;
        }
        largest++;
    }
    */

    // Maybe just find the computer connected to the most other computers?
    for (auto& node : graph.nodes) {
        std::cout << "Connections size: " << node->connections.size() << "\n";
    }
    std::cout << "\n\n";
    // Nvm this just says that all computers are connected to the same amount of other computers
    
    // So we go through all nodes, and for every node we check if it's connections are identical
    // to the firsts (minus itself plus the first of course)
    // and we return the first one where all nodes pass the check

    const int maskSize = 600;
    for (auto& node : graph.nodes) {
        std::bitset<maskSize> nodeMask = 0;
        std::bitset<maskSize> notit = 0;
        for (auto& temp : node->connections) {
            nodeMask |= (std::bitset<maskSize>(1) << (temp->index));
        }

        bool allConnected = true;
        int maxNot = 2;
        for (auto& conn : node->connections) {
            std::bitset<maskSize> connMask = 0;
            notit = 0;
            for (auto& temp : conn->connections) {
                connMask |= (std::bitset<maskSize>(1) << (temp->index));
            }

            if ((nodeMask & connMask).count() < node->connections.size() - maxNot) {
                notit |= (connMask ^ std::bitset<maskSize>(1) << (conn->index));
                if (maxNot-- == 0) {
                    allConnected = false;
                    break;
                }
            }
        }

        if (allConnected) {
            std::cout << node->id << "->";
            for (auto& conn : node->connections) {
                if (((std::bitset<maskSize>(1) << conn->index) & (nodeMask ^ notit)) != 0) {
                    std::cout << conn->id << "->";
                }
            }
            std::cout << "\n";
            return;
        }
    }
}

}