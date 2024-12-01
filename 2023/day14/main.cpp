#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void north(std::vector<std::string>& pattern) {
    for(size_t j = 0; j < pattern[0].length(); j++) {
        for(size_t i = 1; i < pattern.size(); i++) {
            if(pattern[i][j] == 'O') {
                int k = i - 1;
                while(k >= 0) {
                    if(pattern[k][j] == '.') {
                        pattern[k][j] = 'O';
                        pattern[k + 1][j] = '.';
                    }
                    else break;
                    k--;
                }
            }
        }
    }
}

void west(std::vector<std::string>& pattern) {
    for(size_t i = 0; i < pattern.size(); i++) {
        for(size_t j = 0; j < pattern[0].size(); j++) {
            if(pattern[i][j] == 'O') {
                size_t k = j - 1;
                while(k >= 0) {
                    if(pattern[i][k] == '.') {
                        pattern[i][k] = 'O';
                        pattern[i][k + 1] = '.';
                    }
                    else break;
                    k--;
                }
            }
        }
    }
}

void south(std::vector<std::string>& pattern) {
    for(size_t j = 0; j < pattern[0].length(); j++) {
        for(int i = pattern.size() - 1; i >= 0; i--) {
            if(pattern[i][j] == 'O') {
                size_t k = i + 1;
                while(k < pattern.size()) {
                    if(pattern[k][j] == '.') {
                        pattern[k][j] = 'O';
                        pattern[k - 1][j] = '.';
                    }
                    else break;
                    k++;
                }
            }
        }
    }
}

void east(std::vector<std::string>& pattern) {
    for(size_t i = 0; i < pattern.size(); i++) {
        for(int j = pattern[0].length() - 1; j >= 0; j--) {
            if(pattern[i][j] == 'O') {
                size_t k = j + 1;
                while(k < pattern[0].length()) {
                    if(pattern[i][k] == '.') {
                        pattern[i][k] = 'O';
                        pattern[i][k - 1] = '.';
                    }
                    else break;
                    k++;
                }
            }
        }
    }
}

int get_load(std::vector<std::string>& pattern) {
    int sum = 0;
    for(size_t i = 0; i < pattern.size(); i++) {
        int count = 0;
        for(const char c: pattern[i]) {
            count += (c == 'O');
        }
        sum += count * (pattern.size() - i);
    }
    return sum;
}

std::string get_key(std::vector<std::string>& pattern) {
    std::string key;

    for(const auto& s: pattern) key += (s + ' ');

    return key;
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> pattern;
    while(std::getline(in, line)) {
        pattern.push_back(line);
    }

    north(pattern);

    out << get_load(pattern);

    out.close();
    in.close();
}

std::unordered_map<std::string, std::pair<int, int>> memo;

void solve_p2() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p2.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> pattern;
    while(std::getline(in, line)) {
        pattern.push_back(line);
    }

    int cycles = 1000000000;
    int cycle_len = 0;
    int cycle_start = -1;
    for(int i = 0; i < cycles; i++) {
        std::string key = get_key(pattern);
        if(!cycle_len) {
            if(memo.count(key)) {
                cycle_start = i;
                cycle_len = i - memo[key].first;
                break;
            }
        }
        
        north(pattern);
        west(pattern);
        south(pattern);
        east(pattern);

        memo[key] = {i, get_load(pattern)};
    }

    int offset = cycle_start - cycle_len;
    int index = (cycles - 1 - offset) % cycle_len + offset;
    for(const auto& p: memo) {
        if(p.second.first == index) {
            out << p.second.second;
        }
    }

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
