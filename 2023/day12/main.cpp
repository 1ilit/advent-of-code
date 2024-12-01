#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <cmath>

std::unordered_map<std::string, long long> memo;

long long match(const std::string& s, const std::string& p, size_t i, size_t j) {
    std::string key = std::to_string(i) + '-' + std::to_string(j) + '-' + p;
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    if (i == s.length() && j == p.length()) {
        return 1;
    } else if (j == p.length()) {
        return 0;
    } else if (i == s.length()) {
        if (p[j] == '*') {
            return match(s, p, i, j + 1);
        }
        return 0;
    }

    long long res = 0;
    if ((s[i] == '#' || s[i] == '?') && p[j] == '#') {
        res += match(s, p, i + 1, j + 1);
    } else if ((s[i] == '?' || s[i] == '.') && p[j] == '*') {
        res += match(s, p, i + 1, j);
        res += match(s, p, i, j + 1);
    } else if (s[i] == '#' && p[j] == '*') {
        res += match(s, p, i, j + 1);
    } else if ((s[i] == '?' || s[i] == '.') && p[j] == '+') {
        res += match(s, p.substr(0, j) + '*' + p.substr(j + 1), i + 1, j);
    }
    memo[key] = res;
    return res;
}

long long count(const std::string& s, const std::string& p, size_t i, size_t j) {
    memo.clear();
    return match(s, p, i, j);
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    long long sum = 0;
    std::string line;
    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string springs;
        ss >> springs;
        std::string nums;
        ss >> nums;
        std::string num;
        std::stringstream ss1(nums);
        std::vector<int> counts;
        while(std::getline(ss1, num, ',')){
            counts.push_back(std::stoi(num));
        }

        std::string pattern = "*";
        for(size_t i = 0; i < counts.size(); i++) {
            for(int j = 0; j < counts[i]; j++){
                pattern+='#';
            }
            pattern += (i == counts.size() - 1 ? "*" : "+");
        }

        sum += count(springs, pattern, 0, 0);
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
    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string springs;
        ss >> springs;
        std::string nums;
        ss >> nums;
        std::string num;
        std::stringstream ss1(nums);
        std::vector<int> counts;
        while(std::getline(ss1, num, ',')){
            counts.push_back(std::stoi(num));
        }

        std::string unfolded_springs = springs;
        std::vector<int> unfolded_counts;

        for(int i = 0; i < 4; i++){
            unfolded_springs += '?' + springs;
        }

        for (int i = 0; i < 5; i++){
            for (auto x : counts) {
              unfolded_counts.push_back(x);
            }
        }

        std::string pattern = "*";
        for(size_t i = 0; i < unfolded_counts.size(); i++) {
            for(int j = 0; j < unfolded_counts[i]; j++){
                pattern+='#';
            }
            pattern += (i == unfolded_counts.size() - 1 ? "*" : "+");
        }

        sum += count(unfolded_springs, pattern, 0, 0);
    }

    out << sum;

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
