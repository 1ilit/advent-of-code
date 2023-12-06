#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::vector<int> time;
    std::vector<int> distance;

    std::string line;
    std::getline(in, line);
    std::stringstream ss(line);
    std::string token;

    ss >> token;
    while(ss >> token) {
        time.push_back(std::stoi(token));
    }

    std::getline(in, line);
    ss.clear();
    ss.str(line);

    ss >> token;
    while(ss >> token) {
        distance.push_back(std::stoi(token));
    }

    int product = 1;

    for(size_t i = 0; i < time.size(); i++) {
        // -x^2 + tx - d > 0
        int delta = time[i] * time[i] - 4 * distance[i];
        if(delta <= 0) {
            continue;
        }

        int x1 = std::ceil((-time[i] + std::sqrt(delta)) / -2);
        int x2 = std::floor((-time[i] - std::sqrt(delta)) / -2);

        if((time[i] - x1) * x1 == distance[i]) x1++;
        if((time[i] - x2) * x2 == distance[i]) x2--;

        product *= x2 - x1 + 1;
    }

    out << product;

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

    long long time = 0;
    long long distance = 0;

    std::string line;
    std::getline(in, line);
    std::stringstream ss(line);
    std::string token;

    ss >> token;
    while(ss >> token) {
        time = time * std::pow(10, token.length()) + std::stoi(token);
    }

    std::getline(in, line);
    ss.clear();
    ss.str(line);

    ss >> token;
    while(ss >> token) {
        distance = distance * std::pow(10, token.length()) + std::stoi(token);
    }

    long long delta = time * time - 4 * distance;
    if(delta > 0) {
        long long x1 = std::ceil((-time + std::sqrt(delta)) / -2);
        long long x2 = std::floor((-time - std::sqrt(delta)) / -2);  

        if((time - x1) * x1 == distance) x1++;
        if((time - x2) * x2 == distance) x2--;

        out << x2 - x1 + 1;
    } else if(delta == 0) {
        long long x = time / 2;
        if((time - x) * x == distance) out << 0;
        else out << 1;
    } else {
        out << 0;
    }

    out.close();
    in.close();
}


int main() {
    solve_p2();
    return 0;
}
