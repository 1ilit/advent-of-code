#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

long long lcm(long long a, long long b) {
    return a / std::__gcd(a, b) * b;
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    int count = 0;
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;
    std::string dirs;
    in >> dirs;

    std::string line;
    std::string current_node = "AAA";
    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string node, left, right;
        in >> node >> left >> left >> right;
        map[node] = {left.substr(1, left.length() - 2), right.substr(0, right.length() - 1)};
    }

    int dir_index = 0;
    while(current_node.compare("ZZZ")) {
        if(dirs[dir_index]=='L') {
            current_node = map[current_node].first;
        } else {
            current_node = map[current_node].second;
        }

        count++;
        dir_index = (dir_index + 1) % dirs.length();
    }

    out << count;

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

    long long count = 1;
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;
    std::string dirs;
    in >> dirs;

    std::string line;
    std::vector<std::string> starts;

    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string node, left, right;
        in >> node >> left >> left >> right;
        map[node] = {left.substr(1, left.length() - 2), right.substr(0, right.length() - 1)};

        if(node[node.length() - 1] == 'A') starts.push_back(node);
    }

     for(const auto &node : starts) {
        std::string current_node = node;
        long long steps = 0;
        int dir_index = 0;

        while(current_node[current_node.size() - 1] != 'Z') {
            steps++;
            if(dirs[dir_index] == 'L')
                current_node = map[current_node].first;
            else if(dirs[dir_index] == 'R')
                current_node = map[current_node].second;

            dir_index = (dir_index + 1) % dirs.length();
        }

        count = lcm(count, steps);
    }

    out << count;

    out.close();
    in.close();
}


int main() {
    solve_p2();
    return 0;
}
