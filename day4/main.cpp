#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <cmath>

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    int sum = 0;
    std::string line;
    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string token;
        ss >> token >> token;

        std::vector<int> winning_nums;

        while(ss >> token) {
            if(!token.compare("|")) break;

            winning_nums.push_back(std::stoi(token));
        }

        int winning_num_count = 0;
        while(ss >> token) {
            if(std::find(winning_nums.begin(), winning_nums.end(), std::stoi(token)) != winning_nums.end()) {
                winning_num_count++;
            }
        }

        sum += std::pow(2, winning_num_count - 1);
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
    
    int sum = 0;
    std::string line;
    std::map<int, int> map;

    int index = 1;
    while(std::getline(in, line)) {
        if(!map[index]) {
            map[index] = 0;
        }
        map[index]++;
        std::stringstream ss(line);
        std::string token;
        ss >> token >> token;

        std::vector<int> winning_nums;

        while(ss >> token) {
            if(!token.compare("|")) break;

            winning_nums.push_back(std::stoi(token));
        }

        int winning_num_count = 0;
        while(ss >> token) {
            if(std::find(winning_nums.begin(), winning_nums.end(), std::stoi(token)) != winning_nums.end()) {
                winning_num_count++;
            }
        }

        for(int j = 0; j<map[index]; j++) {
            for(int i = 1; i <= winning_num_count; i++) {
                map[index + i]++;
            }
        }
        index++;
    }

    for(const auto& p: map) {
        sum += p.second;
    }

    out << sum;
    out.close();
    in.close();
}


int main() {
    solve_p1();
    return 0;
}
