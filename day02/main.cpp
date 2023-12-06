#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    int red_count = 12;
    int green_count = 13;
    int blue_count = 14;

    std::string line;
    int index = 1;
    int sum = 0;
    while(std::getline(in, line)) {
        bool ok = true;
        int colon = line.find(':');
        std::string games = line.substr(colon + 2);

        std::stringstream ss(games);
        std::string game;
        while(std::getline(ss, game, ';')){
            std::stringstream ss2(game);
            std::string cube;
            while(std::getline(ss2, cube, ',')){
                std::stringstream ss3(cube);
                int count;
                std::string color;
                ss3 >> count >> color;
                if(!color.compare("red")){
                    ok = count <= red_count;
                } else if(!color.compare("blue")){
                    ok = count <= blue_count;
                } else if(!color.compare("green")) {
                    ok = count <= green_count;
                }

                if(!ok) {
                    break;
                }
            }
            if(!ok) {
                break;
            }
        }

        if (ok) sum += index;
        index++;
    }

    out << sum;

    out.close();
    in.close();
}

void solve_p2() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p2.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    int index = 1;
    int sum = 0;
    while(std::getline(in, line)) {
        int colon = line.find(':');
        std::string games = line.substr(colon + 2);

        std::stringstream ss(games);
        std::string game;
        int max_red = 0, max_blue = 0, max_green = 0;
        while(std::getline(ss, game, ';')){
            std::stringstream ss2(game);
            std::string cube;
            while(std::getline(ss2, cube, ',')){
                std::stringstream ss3(cube);
                int count;
                std::string color;
                ss3 >> count >> color;
                if(!color.compare("red")){
                    max_red = std::max(max_red, count);
                } else if(!color.compare("blue")){
                    max_blue = std::max(max_blue, count);
                } else if(!color.compare("green")) {
                    max_green = std::max(max_green, count);
                }
            }
        }

        sum += max_red * max_blue * max_green;
        index++;
    }

    out << sum;

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
