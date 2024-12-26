#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

#include <math.h>

//#define DEBUG

namespace Day22 {

std::vector<uint64_t> input;

std::vector<std::vector<int>> prices;
std::vector<std::vector<int>> changes;

std::vector<std::map<std::vector<int>, int>> pricesMaps;

void run() {
    std::ifstream file("inputs/day22.txt");
    std::string line;

    while (std::getline(file, line)) {
       input.emplace_back(std::stoi(line));
    }

    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i] << "\n";
        prices.emplace_back(std::vector<int>({input[i] % 10}));
        changes.emplace_back(std::vector<int>({0}));
    }
    std::cout << "\n";

    int iters = 2000;
    for (int i = 0; i < iters; i++) {
        for (int n = 0; n < input.size(); n++) {
            if (prices[n].size() > 1) {
                changes[n].emplace_back(prices[n][i] - prices[n][i - 1]);
                #ifdef DEBUG
                printf("%8li: %i (%i)\n", input[n], prices[n].back(), changes[n].back());
                #endif
            } else {
                #ifdef DEBUG
                printf("%8li\n", input[n]);
                #endif
            }

            input[n] ^= (input[n] * 64);
            input[n] %= 16777216;

            input[n] ^= (input[n] / 32);
            input[n] %= 16777216;

            input[n] ^= (input[n] * 2048);
            input[n] %= 16777216;

            prices[n].emplace_back(input[n] % 10);
        }
        #ifdef DEBUG
        std::cout << "\n";
        #endif
    }
    // Add one more price change to make it 2000 price changes
    for (int n = 0; n < input.size(); n++) {
        changes[n].emplace_back(prices[n][2000] - prices[n][1999]);

        input[n] ^= (input[n] * 64);
        input[n] %= 16777216;

        input[n] ^= (input[n] / 32);
        input[n] %= 16777216;

        input[n] ^= (input[n] * 2048);
        input[n] %= 16777216;

        prices[n].emplace_back(input[n] % 10);
    }

    uint64_t total = 0;
    for (uint64_t& n : input) {
        total += n;
    }
    std::cout << "Sum of secrets: " << total << "\n";

    
    // Brute force every possible combination of price changes xxx
    for (int n = 0; n < input.size(); n++) {
        pricesMaps.emplace_back(std::map<std::vector<int>, int>());
    }

    for (int n = 0; n < input.size(); n++) {
        for (int i = 4; i < changes[n].size(); i++) {
            std::vector<int> sequence = {changes[n][i-3], changes[n][i-2], changes[n][i-1], changes[n][i]};
            if (!pricesMaps[n].contains(sequence)) {
                pricesMaps[n].emplace(sequence, prices[n][i]);
            }
        }
    }

    int maxBananas = 0;
    std::vector<int> bestFour;
    for (int n1 = -9; n1 < 10; n1++) {
        for (int n2 = -9; n2 < 10; n2++) {
            for (int n3 = -9; n3 < 10; n3++) {
                for (int n4 = -9; n4 < 10; n4++) {
                    int total = 0;
                    for (int n = 0; n < input.size(); n++) {
                        if (pricesMaps[n].contains({n1, n2, n3, n4})) {
                            total += pricesMaps[n][{n1, n2, n3, n4}];
                        }
                    }
                    if (total > maxBananas) {
                        maxBananas = total;
                        bestFour = {n1, n2, n3, n4};
                        printf("Max bananas: %i\n", maxBananas);
                    }
                }
            }
        }
    }
    printf("\nBest four: %i, %i, %i, %i\n", bestFour[0], bestFour[1], bestFour[2], bestFour[3]);
    std::cout << "Max bananas: " << maxBananas << "\n";
}

}