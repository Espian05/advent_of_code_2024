#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day9 {

std::string input;

std::vector<int> decompress(std::string line) {
    std::vector<int> output;

    for (int i = 0; i < input.size(); i++) {
        int num = line[i] - '0';
        for (int j = 0; j < num; j++) {
            if (i % 2 == 0) {
                output.push_back(i/2);
            } else {
                output.push_back(-1);
            }
        }
    }

    return output;
}

std::vector<int> shuffleOne(std::vector<int> line) {
    int last = line.size();
    for (int i = line.size() - 1; i > 0; i--) {
        if (line[i] != -1) {
            last = i;
            break;
        }
    }
    int first = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == -1) {
            first = i;
            break;
        }
    }
    if (first - last == 1) {
        return line;
    }
    line[first] = line[last];
    line[last] = -1;
    return line;
}

void part1() {
    std::vector<int> decompressed = decompress(input);
    for (int i = 0; i < decompressed.size(); i++) {
        std::cout << decompressed[i] << ", ";
    }
    std::cout << "\n";

    std::vector<int> after;
    while (true) {
        after = shuffleOne(decompressed);
        if (after != decompressed) {
            decompressed = after;
            //for (int i = 0; i < decompressed.size(); i++) {
            //    std::cout << decompressed[i] << ", ";
            //}
            std::cout << "\n";
        } else {
            break;
        }
    }
    std::cout << "\n";

    long total = 0;
    for (int i = 0; i < decompressed.size(); i++) {
        if (decompressed[i] == -1) continue;
        total += (long)decompressed[i] * (long)i;
        std::cout << decompressed[i] << " * " << i << " = " << decompressed[i] * i << "\n";
    }
    std::cout << "Total: " << total << "\n";
}

std::vector<int> attempt2(std::vector<int> line, int last) {
    // Find the first file you come across
    int fileNumber = -1;
    int fileStart = -1;
    int fileEnd = -1;
    int fileWidth = -1;
    for (int i = last; i >= 0; i--) {
        if (fileEnd == -1) { // Looking for the end of a file
            if (line[i] != -1) { // Found end of file
                fileNumber = line[i];
                fileEnd = i + 1; // For reasons
            }
        } else if (fileStart == -1) { // Looking for start of file
            if (line[i] != fileNumber) { // Found start of file
                fileStart = i + 1; // Because we actually found the first empty space
                break;
            }
        }
    }
    if (fileStart == -1) { // We didn't find the end of a file, so it's the end
        return line;
    }
    fileWidth = fileEnd - fileStart;

    // Iterate from 0 to the start of the file, looking for the first
    // black space big enough to fit the file found.
    int blockStart = -1;
    int blockEnd = -1;
    int blockWidth = -1;
    for (int i = 0; i <= fileStart; i++) {
        if (blockStart == -1) { // Looking for the start of an empty block
            if (line[i] == -1) { // Found the start of an empty block
                blockStart = i;
            }
        } else if (blockEnd == -1) { // Looking for end of a block
            if (line[i] != -1) { // Found end of block
                blockEnd = i;
            }
        }
        if (blockStart != -1 && blockEnd != -1) { // Block found
            blockWidth = blockEnd - blockStart;
            if (blockWidth < fileWidth) { // Block too small - continue search
                blockStart = -1;
                blockEnd = -1;
                blockWidth = -1;
            } else { // Block is big enough - break out and copy the file over
                break;
            }
        }
    }


    // If a block has been found, copy the file over
    if (blockWidth != -1) {
        for (int i = 0; i < fileWidth; i++) {
            line[blockStart + i] = fileNumber;
            line[fileStart + i] = -1;
        }
    }
    // Recursive call from the start of the file just attempted to move
    return attempt2(line, fileStart - 1);
}

void part2() {
    std::vector<int> decompressed = decompress(input);
    for (int i = 0; i < decompressed.size(); i++) {
        std::cout << decompressed[i] << ", ";
    }
    std::cout << "\n";

    decompressed = attempt2(decompressed, decompressed.size() - 1);
    std::cout << "\n";

    long total = 0;
    for (int i = 0; i < decompressed.size(); i++) {
        if (decompressed[i] == -1) continue;
        total += (long)decompressed[i] * (long)i;
        std::cout << decompressed[i] << " * " << i << " = " << decompressed[i] * i << "\n";
    }
    std::cout << "Total: " << total << "\n";
}

void run() {
    std::ifstream file("inputs/day9.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        input = line;
    }

    std::cout << input << "\n\n";

    part1();

    std::cout << "\n\n";

    part2();
}

}