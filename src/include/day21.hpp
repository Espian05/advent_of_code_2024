#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

namespace Day21 {

std::vector<std::string> input;

std::map<std::pair<std::pair<char, char>, int>, unsigned long long> memoiy;

struct Node;

struct Edge {
    int head;
    char direction;

    Edge(int h, char d) :
        head(h), direction(d) {}
};

struct Node {
    char value;
    std::vector<Edge> edges;

    Node() {}
    Node(char v) : value(v) {}
};

struct Graph {
    std::vector<Node> nodes;

    std::vector<std::string> getPaths(char s, char e) {
        int start = 0;
        int end = 0;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].value == s) start = i;
            if (nodes[i].value == e) end = i;
        }

        std::vector<std::string> paths = bfs(start, end, {});

        return paths;
    }

    std::vector<std::string> bfs(int current, int target, std::vector<int> visited) {
        if (current == target) return {"A"};
        visited.emplace_back(current);

        std::vector<std::string> paths = {};

        for (Edge& e : nodes[current].edges) {
            if (std::find(visited.begin(), visited.end(), e.head) != visited.end()) continue;

            std::vector<std::string> result = bfs(e.head, target, visited);
            for (std::string& path : result) {
                if (path.back() == 'A') {
                    paths.emplace_back(e.direction + path);
                }
            }
        }

        return paths;
    }
};

Graph keypad;
Graph dpad;

Graph initKeypad() {
    Graph keypad;
    keypad.nodes.emplace_back('0');
    keypad.nodes.emplace_back('1');
    keypad.nodes.emplace_back('2');
    keypad.nodes.emplace_back('3');
    keypad.nodes.emplace_back('4');
    keypad.nodes.emplace_back('5');
    keypad.nodes.emplace_back('6');
    keypad.nodes.emplace_back('7');
    keypad.nodes.emplace_back('8');
    keypad.nodes.emplace_back('9');
    keypad.nodes.emplace_back('A');

    keypad.nodes[0].edges.emplace_back(2, '^');
    keypad.nodes[0].edges.emplace_back(10, '>');

    keypad.nodes[1].edges.emplace_back(4, '^');
    keypad.nodes[1].edges.emplace_back(2, '>');

    keypad.nodes[2].edges.emplace_back(1, '<');
    keypad.nodes[2].edges.emplace_back(5, '^');
    keypad.nodes[2].edges.emplace_back(3, '>');
    keypad.nodes[2].edges.emplace_back(0, 'v');

    keypad.nodes[3].edges.emplace_back(6, '^');
    keypad.nodes[3].edges.emplace_back(2, '<');
    keypad.nodes[3].edges.emplace_back(10, 'v');

    keypad.nodes[4].edges.emplace_back(7, '^');
    keypad.nodes[4].edges.emplace_back(5, '>');
    keypad.nodes[4].edges.emplace_back(1, 'v');

    keypad.nodes[5].edges.emplace_back(4, '<');
    keypad.nodes[5].edges.emplace_back(8, '^');
    keypad.nodes[5].edges.emplace_back(6, '>');
    keypad.nodes[5].edges.emplace_back(2, 'v');

    keypad.nodes[6].edges.emplace_back(9, '^');
    keypad.nodes[6].edges.emplace_back(5, '<');
    keypad.nodes[6].edges.emplace_back(3, 'v');

    keypad.nodes[7].edges.emplace_back(8, '>');
    keypad.nodes[7].edges.emplace_back(4, 'v');

    keypad.nodes[8].edges.emplace_back(7, '<');
    keypad.nodes[8].edges.emplace_back(5, 'v');
    keypad.nodes[8].edges.emplace_back(9, '>');

    keypad.nodes[9].edges.emplace_back(8, '<');
    keypad.nodes[9].edges.emplace_back(6, 'v');

    keypad.nodes[10].edges.emplace_back(0, '<');
    keypad.nodes[10].edges.emplace_back(3, '^');

    return keypad;
}

Graph initDpad() {
    Graph dpad;

    enum { UP, LEFT, DOWN, RIGHT, ACCEPT };

    dpad.nodes.emplace_back('^');
    dpad.nodes.emplace_back('<');
    dpad.nodes.emplace_back('v');
    dpad.nodes.emplace_back('>');
    dpad.nodes.emplace_back('A');

    dpad.nodes[UP].edges.emplace_back(ACCEPT, '>');
    dpad.nodes[UP].edges.emplace_back(DOWN, 'v');

    dpad.nodes[LEFT].edges.emplace_back(DOWN, '>');

    dpad.nodes[DOWN].edges.emplace_back(LEFT, '<');
    dpad.nodes[DOWN].edges.emplace_back(UP, '^');
    dpad.nodes[DOWN].edges.emplace_back(RIGHT, '>');

    dpad.nodes[RIGHT].edges.emplace_back(DOWN, '<');
    dpad.nodes[RIGHT].edges.emplace_back(ACCEPT, '^');

    dpad.nodes[ACCEPT].edges.emplace_back(UP, '<');
    dpad.nodes[ACCEPT].edges.emplace_back(RIGHT, 'v');

    return dpad;
}

unsigned long long shortest(std::string str, int depth) {
    if (depth == 0) return str.size();

    unsigned long long totalLength = 0;
    std::string totalPath = "";
    str.insert(str.begin(), 'A');
    for (int i = 0; i < str.size() - 1; i++) {
        if (memoiy.contains(std::pair(std::pair(str[i], str[i+1]), depth-1))) {
            totalLength += memoiy[std::pair(std::pair(str[i], str[i+1]), depth-1)];
            continue;
        }

        std::vector<std::string> paths = dpad.getPaths(str[i], str[i+1]);

        unsigned long long smallest = 9223372036854775807;
        int index = 0;
        for (int k = 0; k < paths.size(); k++) {
            unsigned long long temp = shortest(paths[k], depth-1);
            if (temp < smallest) {
                index = k;
                smallest = temp;
            }
        }
        totalPath += paths[index];
        totalLength += smallest;
        memoiy.emplace(std::pair(std::pair(str[i], str[i+1]), depth-1), smallest);
    }
    //std::cout << totalPath << "\n";

    return totalLength;
}

void run() {
    std::ifstream file("inputs/day21.txt");
    std::string line;

    while (std::getline(file, line)) {
        input.emplace_back(line);
    }

    keypad = initKeypad();
    dpad = initDpad();

    unsigned long long totalComplexity = 0;
    for (std::string& code : input) {
        unsigned long long totalLength = 0;
        std::string totalPath = "";
        code.insert(code.begin(), 'A');
        for (int c = 0; c < code.size() - 1; c++) { // Omg the real c++ (I'm going insane it's 11:03)
            std::vector<std::string> padpaths = keypad.getPaths(code[c], code[c+1]);

            unsigned long long smallest = 9223372036854775807;
            int index = 0;
            for (int i = 0; i < padpaths.size(); i++) {
                unsigned long long temp = shortest(padpaths[i], 25);
                if (temp < smallest) {
                    index = i;
                    smallest = temp;
                }
            }

            totalLength += smallest;
            totalPath += padpaths[index];
        }
        std::cout << totalPath << "\n";
        std::cout << "Shortest for " << code << ": " << totalLength << "\n\n";
        unsigned long long complexity = std::stoi(code.substr(1, code.size() - 1)) * totalLength;
        totalComplexity += complexity;
    }
    std::cout << "Total complexity: " << totalComplexity << "\n";
}

}