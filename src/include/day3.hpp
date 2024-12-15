#include <iostream>
#include <fstream> 
#include <vector>

namespace Day3 {

int parseLineFirst(std::string line) {
    std::string numbers = "0123456789";

    std::string command = "mul(";
    int total = 0;

    enum {COMMAND, FIRST, SECOND};
    int state = COMMAND;

    int index = 0;
    std::string buffer;

    int first;
    int second;

    for (char& c : line) {
        switch (state) {
            case COMMAND: {
                if (c == command[index]) {
                    index++;
                    std::cout << "Index: " << index << "\n";
                    if (index == command.size()) {
                        state = FIRST;
                    }
                } else {
                    state = COMMAND;
                    index = 0;
                    buffer = "";
                }
                break;
            }
            case FIRST: {
                if (numbers.contains(c)) {
                    buffer.push_back(c);
                    std::cout << "Buffer for first: " << buffer << "\n";
                } else if (c == ',' && buffer != "") {
                    std::cout << "Converting buffer for first into int\n";
                    first = std::stoi(buffer);
                    buffer = "";
                    state = SECOND;
                } else {
                    state = COMMAND;
                    index = 0;
                    buffer = "";
                }
                break;
            }
            case SECOND: {
                if (numbers.contains(c)) {
                    buffer.push_back(c);
                    std::cout << "Buffer for second: " << buffer << "\n";
                } else if (c == ')' && buffer != "") {
                    std::cout << "Converting buffer for second into int\n";
                    second = std::stoi(buffer);
                    buffer = "";
                    total += first * second;
                    std::cout << "Added: " << first * second << " total is now: " << total << "\n";
                    index = 0;
                    state = COMMAND;
                } else {
                    state = COMMAND;
                    index = 0;
                    buffer = "";
                }
                break;
            }
        }
    }

    return total;
}

int parseLineSecond(std::string line) {
    int total;

    std::string doCommand = "do()";
    std::string dontCommand = "don't()";

    int doIndex = 0;
    int dontIndex = 0;
    bool match = false;

    std::vector<int> starts;
    std::vector<int> stops;

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == doCommand[doIndex]) {
            std::cout << "Do: " << i << " : " << line[i] << "\n";
            doIndex++;
            if (doIndex == doCommand.size()) {
                std::cout << "Appending start " << i << "\n";
                starts.emplace_back(i);
                doIndex = 0;
            }
        } else {
            doIndex = 0;
        }
        if (line[i] == dontCommand[dontIndex]) {
            std::cout << "Don't: " << i << " : " << line[i] << "\n";
            dontIndex++;
            if (dontIndex == dontCommand.size()) {
                std::cout << "Appending stop " << i << "\n";
                stops.emplace_back(i);
                dontIndex = 0;
            }
        } else {
            dontIndex = 0;
        }
    }

    std::cout << "Start array: ";
    for (int& n : starts) {
        std::cout << n << ",";
    }
    std::cout << "\nStops array: ";
    for (int& n : stops) {
        std::cout << n << ",";
    }
    std::cout << "\n";

    bool doing = true;
    int startsIndex = 0;
    int stopsIndex = 0;
    std::string buffer = "";
    for (int i = 0; i < line.size(); i++) {
        if (i == stops[stopsIndex] && stopsIndex < stops.size()) {
            stopsIndex++;
            doing = false;
            if (buffer != "") {
                std::cout << "Parsing: " << buffer << "\n";
                std::cout << "Total before: " << total << "\n";
                total += parseLineFirst(buffer);
                std::cout << "Total is now: " << total << "\n";
                buffer = "";
            }
        }
        if (i == starts[startsIndex] && startsIndex < starts.size()) {
            startsIndex++;
            doing = true;
        }
        if (doing) {
            buffer.push_back(line[i]);
        }
    }
    if (doing) {
        std::cout << "Parsing: " << buffer << "\n";
        std::cout << "Total before: " << total << "\n";
        total += parseLineFirst(buffer);
        std::cout << "Total is now: " << total << "\n";
    }

    return total;
}

void run() {
    std::ifstream file("inputs/day3.txt");
    std::string input;
    
    int firstTotal = 0;
    int secondTotal = 0;
    while (std::getline(file, input)) {
        firstTotal += parseLineFirst(input);
        secondTotal += parseLineSecond(input);

    }
    std::cout << "First total: " << firstTotal << "\n";
    std::cout << "Second total: " << secondTotal << "\n";
}

}