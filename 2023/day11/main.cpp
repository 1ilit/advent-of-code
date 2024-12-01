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

    long long sum = 0;
    std::string line;
    std::vector<std::pair<int, int>> positions;
    int i = 0;
    int rows = 0, cols = 0;
    while(std::getline(in, line)) {
        if(!cols) cols = line.length();

        for(size_t j = 0; j < line.length(); j++) {
            if(line[j] == '#') {
                positions.push_back({i, j});
            }
        }
        i++;
    }

    rows = i;

    int expansion = 2;
    for(i = rows - 1; i >= 0; i--) {
        bool empty = true;
        for(const auto& p: positions) {
            if(p.first == i) {
                empty = false;
                break;
            }
        }

        if(!empty) continue;

        for(auto& p: positions) {
            if(p.first > i) {
                p.first += expansion - 1;
            }
        }
    }

    for(i = cols - 1; i >= 0; i--) {
        bool empty = true;
        for(const auto& p: positions) {
            if(p.second == i) {
                empty = false;
                break;
            }
        }

        if(!empty) continue;

        for(auto& p: positions) {
            if(p.second > i) {
                p.second += expansion - 1;
            }
        }
    }

    for(size_t j = 0; j < positions.size(); j++){
        for(size_t k = j + 1; k < positions.size(); k++){
            sum += std::abs(positions[k].first - positions[j].first) + std::abs(positions[k].second - positions[j].second);
        }
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

    
    long long sum = 0;
    std::string line;
    std::vector<std::pair<int, int>> positions;
    int i = 0;
    int rows = 0, cols = 0;
    while(std::getline(in, line)) {
        if(!cols) cols = line.length();

        for(size_t j = 0; j < line.length(); j++) {
            if(line[j] == '#') {
                positions.push_back({i, j});
            }
        }
        i++;
    }

    rows = i;

    int expansion = 1000000;
    for(i = rows - 1; i >= 0; i--) {
        bool empty = true;
        for(const auto& p: positions) {
            if(p.first == i) {
                empty = false;
                break;
            }
        }

        if(!empty) continue;

        for(auto& p: positions) {
            if(p.first > i) {
                p.first += expansion - 1;
            }
        }
    }

    for(i = cols - 1; i >= 0; i--) {
        bool empty = true;
        for(const auto& p: positions) {
            if(p.second == i) {
                empty = false;
                break;
            }
        }

        if(!empty) continue;

        for(auto& p: positions) {
            if(p.second > i) {
                p.second += expansion - 1;
            }
        }
    }

    for(size_t j = 0; j < positions.size(); j++){
        for(size_t k = j + 1; k < positions.size(); k++){
            sum += std::abs(positions[k].first - positions[j].first) + std::abs(positions[k].second - positions[j].second);
        }
    }
    
    out << sum;

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
