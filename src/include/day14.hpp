#include <iostream>
#include <fstream> 
#include <vector>

#include <map>

namespace Day14 {

struct Robot {
    int posX = 0;
    int posY = 0;
    int velX = 0;
    int velY = 0;

    int maxX;
    int maxY;

    Robot(int x, int y, int vx, int vy, int mx, int my) :
        posX(x), posY(y), velX(vx), velY(vy), maxX(mx), maxY(my) {}
    
    void update() {
        posX += velX;
        posY += velY;

        if (posX >= maxX) {
            posX -= maxX;
        }
        if (posY >= maxY) {
            posY -= maxY;
        }
        if (posX < 0) {
            posX += maxX;
        }
        if (posY < 0) {
            posY += maxY;
        }
    }

    bool operator<(Robot r) const {
        return r.posX < posX;
    }
};

std::map<std::vector<Robot>, bool> seen;

std::vector<Robot> robots;

void run() {
    std::ifstream file("inputs/day14.txt");
    std::string line;

    int maxX = 101;
    int maxY = 103;

    while (std::getline(file, line)) {
        int space = line.find_first_of(' ');
        int firstComma = line.find_first_of(',');
        int secondComma = line.find_first_of(',', space);

        int x = std::stoi(line.substr(2, firstComma - 2));
        int y = std::stoi(line.substr(firstComma + 1, space - firstComma));
        int vx = std::stoi(line.substr(space + 3, secondComma - space - 3));
        int vy = std::stoi(line.substr(secondComma + 1));

        std::cout << x << ", " << y << ", " << vx << ", " << vy << "\n";

        robots.emplace_back(x, y, vx, vy, maxX, maxY);
    }
    
    std::vector<std::string> picture;

    for (int y = 0; y < maxY; y++) {
        std::string row;
        for (int x = 0; x < maxX; x++) {
            row.push_back(' ');
        }        
        picture.emplace_back(row);
    }

    int stepsNeeded = -1;
    for (int i = 0; i < 100; i++) {
        for (Robot& r : robots) {
            picture[r.posY][r.posX] = ' ';
            r.update();
            picture[r.posY][r.posX] = '#';
        }

        if (seen.contains(robots) && stepsNeeded == -1) {
            stepsNeeded = i;
        } 
        seen.emplace(robots, true);

        for (int y = 0; y < maxY; y++) {
            std::cout << picture[y] << "\n";
        }
        std::cout << "Step: " << i + 1 << "\n\n";

        std::cin.get();

        /* Clears the screen and finds the width and height of the terminal. Pretty neat.
        printf("\033c");
        auto const w(WEXITSTATUS(std::system("exit `tput cols`")));
        auto const h(WEXITSTATUS(std::system("exit `tput lines`")));
        std::cout << "Width: " << w << "\tHeight: " << h << "\n";
        */
    }

    int middleX = (maxX - 1) / 2;
    int middleY = (maxY - 1) / 2;
    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;
    std::cout << "\n";
    std::cout << middleX << ", " << middleY << "\n\n";
    for (Robot& r : robots) {
        if (r.posX == middleX || r.posY == middleY) continue;
        std::cout << r.posX << ", " << r.posY << "\n";
        if (r.posX < middleX && r.posY < middleY) q1++;
        if (r.posX < middleX && r.posY > middleY) q2++;
        if (r.posX > middleX && r.posY < middleY) q3++;
        if (r.posX > middleX && r.posY > middleY) q4++;
    }
    std::cout << "q1: " << q1 << "\tq2: " << q2 << "\tq3: " << q3 << "\tq4: " << q4 << "\n";
    int safetyFactor = q1 * q2 * q3 * q4;

    for (int i = 100; i < 100000; i++) {
        for (Robot& r : robots) {
            picture[r.posY][r.posX] = ' ';
            r.update();
            picture[r.posY][r.posX] = '#';
        }

        if (seen.contains(robots) && stepsNeeded == -1) {
            stepsNeeded = i;
        } 
        seen.emplace(robots, true);

        for (int y = 0; y < maxY; y++) {
            std::cout << picture[y] << "\n";
        }
        std::cout << "Step: " << i + 1 << "\n\n";

        std::cin.get();
    }

    std::cout << "Safety Factor: " << safetyFactor << "\n";
    std::cout << "Steps for tree: " << stepsNeeded << "\n";
}

}