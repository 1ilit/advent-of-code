#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cmath>

const std::unordered_map<char, std::pair<int, int>> directions = {
    {'R', {0, 1}}, {'D', {1, 0}}, {'L', {0, -1}}, {'U', {-1, 0}}
};

char num_to_dir[4] = {'R', 'D', 'L', 'U'};

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::vector<std::pair<int, int>> points;
    points.push_back({0, 0});
    int b = 0;
    while(std::getline(in, line)){
        std::stringstream ss(line);
        char dir;
        int length;
        ss >> dir >> length;

        int y = points[points.size() - 1].first + directions.at(dir).first * length;
        int x = points[points.size() - 1].second + directions.at(dir).second * length;

        b += length;
        points.push_back({y, x});
    }

    int A = 0;

    for(size_t i = 1; i < points.size() - 1; i++) {
        A += points[i].second * (points[i + 1].first - points[i - 1].first);
    }

    A = A / 2;
    A = std::abs(A);

    out << A - b / 2 + 1 + b;

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
    std::vector<std::pair<long long, long long>> points;
    points.push_back({0, 0});
    long long b = 0;
    while(std::getline(in, line)){
        std::stringstream ss(line);
        std::string hex;
        ss >> hex >> hex >> hex;

        char dir = num_to_dir[hex[hex.length() - 2] - '0'];
        long long length = std::stoi(hex.substr(2, 5), nullptr, 16);

        long long y = points[points.size() - 1].first + directions.at(dir).first * length;
        long long x = points[points.size() - 1].second + directions.at(dir).second * length;

        b += length;
        points.push_back({y, x});
    }

    long long A = 0;

    for(size_t i = 1; i < points.size() - 1; i++) {
        A += points[i].second * (points[i + 1].first - points[i - 1].first);
    }

    A = A / 2;
    A = std::abs(A);

    out << A - b / 2 + 1 + b;

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
