#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

namespace Day17 {

long regA = -1;
long regB = 0;
long regC = 0;
int pc = 0;

long regBCopy;
long regCCopy;

std::vector<int> program;

long bruteForce = -1;
long start = 0;
long bestIter = 0;

int ticks = 0;

long base = 0;

void run() {
    std::ifstream file("inputs/day17.txt");
    std::string line;

    int reading = 0;
    while (std::getline(file, line)) {
        if (reading == 0) regA = std::stoi(line.substr(12));
        if (reading == 1) regB = std::stoi(line.substr(12));
        if (reading == 2) regC = std::stoi(line.substr(12));
        if (reading == 4) {
            for (int i = 9; i < line.size(); i+=2) {
                std::cout << line[i] - 48 << "\n";
                program.emplace_back(line[i] - 48);
            }
        }
        reading++;
    }

    std::cout << "RegA: " << regA << "\n";
    std::cout << "RegB: " << regB << "\n";
    std::cout << "RegC: " << regC << "\n";
    std::cout << "PC: " << pc << "\n";
    std::cout << "Program: ";
    for (int i = 0; i < program.size(); i++) {
        std::cout << program[i] << ",";
    }
    std::cout << "\b \b\n\n";

    regBCopy = regB;
    regCCopy = regC;

    std::cout << "\n\n";
    long total = 0;
    for (int i = 0; i < program.size(); i++) {
        long target = program[i];
        long asd = target ^ 0b110;
        asd = asd ^ 0b101;
        total |= (asd << (3 * i));
    }
    total = total << 5;
    printf("%b\n", total);
    std::cout << total << "\n";
    std::cout << "\n\n";

    int n = 0;
    long start = 0;
startBrute:
    bruteForce++;
    if (n > 3) {
        regA = start + (bruteForce << (n * 2));
    } else {
        regA = start + bruteForce;
    }
    long regACopy = regA;
    regB = regBCopy;
    regC = regCCopy;
    pc = 0;
    int iter = 0;

    if (regACopy % 100000000 == 0) std::cout << "Reached " << regACopy << "\n";

    std::string output = "";
    while(true) {
        ticks++;
        int instr = program[pc];
        int literal = program[pc+1];
        int combo = literal;
        if (combo == 4) combo = regA;
        else if (combo == 5) combo = regB;
        else if (combo == 6) combo = regC;
        //std::cout << "Instr: " << instr << "\t\tLiteral: " << literal << "\t\tCombo: " << combo << "\n";

        if (instr == 0) {
            regA = floor((double)regA / (double)pow(2, combo));
        }
        if (instr == 1) {
            regB = (regB ^ literal);
        }
        if (instr == 2) {
            regB = (combo & 0b111);
        }
        if (instr == 3) {
            if (regA != 0) {
                pc = literal - 2;
            }
        }
        if (instr == 4) {
            regB = (regB ^ regC);
        }
        if (instr == 5) {
            if ((combo & 0b111) != program[iter]) {
                goto startBrute;
            } else {
                if (iter == n) {
                    std::cout << "Digit " << program[iter] << " found! RegA was: " << regACopy << "\n";
                    if (iter != program.size() - 1) {
                        start = regACopy;
                        bruteForce = -1;
                        n++;
                        goto startBrute;
                    } else {
                        break;
                    }
                }
                iter++;
            }
            output += std::to_string(combo & 0b111) + ",";
        }
        if (instr == 6) {
            regB = floor((double)regA / pow(2, combo));
        }
        if (instr == 7) {
            regC = floor((double)regA / pow(2, combo));
        }

        pc += 2;

        if (pc > program.size() - 1) break;
    }
    std::cout << "RegA: " << regA << "\n";
    std::cout << "RegB: " << regB << "\n";
    std::cout << "RegC: " << regC << "\n";
    std::cout << "PC: " << pc << "\n";
    std::cout << "Output:\n";
    std::cout << output << "\b \b\n";
    if (iter != program.size() - 1) {
        goto startBrute;
    } else {
        std::cout << "Correct A found: " << regACopy << "\n";
        std::cout << "Ticks taken: " << ticks << "\n";
    }
}

}