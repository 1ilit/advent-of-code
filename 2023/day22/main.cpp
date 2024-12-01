#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cmath>

struct Brick {
    int start_x, start_y, start_z;
    int end_x, end_y, end_z;
};

Brick from_vector(std::vector<int>& v) {
    return Brick{
        v[0], v[1], v[2], v[3], v[4], v[5]
    };
}

bool overlap(const Brick& b1, const Brick& b2) {
    return std::max(b1.start_x, b2.start_x) <= std::min(b1.end_x, b2.end_x) && 
           std::max(b1.start_y, b2.start_y) <= std::min(b1.end_y, b2.end_y);
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::vector<Brick> bricks;

    while(std::getline(in, line)) {
        int tilde = line.find('~');
        line[tilde] = ',';
        std::stringstream ss(line);
        std::vector<int> brick;
        std::string token;
        while(std::getline(ss, token, ',')) {
            brick.push_back(std::stoi(token));
        }
        bricks.push_back(from_vector(brick));
    }

    std::sort(bricks.begin(), bricks.end(), [](const auto& a, const auto& b) {
        return a.start_z < b.start_z;
    });

    for(size_t i = 0; i < bricks.size(); i++) {
        int max_z = 1;
        for(size_t j = 0; j < i; j++) {
            if(overlap(bricks[i], bricks[j])) {
                max_z = std::max(max_z, bricks[j].end_z + 1);
            }
        }

        bricks[i].end_z -= bricks[i].start_z - max_z;
        bricks[i].start_z = max_z;
    }

    std::sort(bricks.begin(), bricks.end(), [](const auto& a, const auto& b) {
        return a.start_z < b.start_z;
    });

    std::unordered_map<int, std::unordered_set<int>> k_to_v; 
    std::unordered_map<int, std::unordered_set<int>> v_to_k; 

    for(size_t j = 0; j < bricks.size(); j++) {
        for(size_t i = 0; i < j; i++) {
            if(overlap(bricks[i], bricks[j]) && bricks[j].start_z == bricks[i].end_z + 1) {
                k_to_v[i].insert(j);
                v_to_k[j].insert(i);
            }
        }
    }

    int count = 0;
    for(size_t i = 0; i < bricks.size(); i++) {
        bool has_other_support = true;
        for(const auto& x: k_to_v[i]) {
            if(v_to_k.count(x) && v_to_k[x].size() < 2) {
                has_other_support = false;
                break;
            }
        }
         
        if(has_other_support) count++;
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

    std::string line;
    std::vector<Brick> bricks;

    while(std::getline(in, line)) {
        int tilde = line.find('~');
        line[tilde] = ',';
        std::stringstream ss(line);
        std::vector<int> brick;
        std::string token;
        while(std::getline(ss, token, ',')) {
            brick.push_back(std::stoi(token));
        }
        bricks.push_back(from_vector(brick));
    }

    std::sort(bricks.begin(), bricks.end(), [](const auto& a, const auto& b) {
        return a.start_z < b.start_z;
    });

    for(size_t i = 0; i < bricks.size(); i++) {
        int max_z = 1;
        for(size_t j = 0; j < i; j++) {
            if(overlap(bricks[i], bricks[j])) {
                max_z = std::max(max_z, bricks[j].end_z + 1);
            }
        }

        bricks[i].end_z -= bricks[i].start_z - max_z;
        bricks[i].start_z = max_z;
    }

    std::sort(bricks.begin(), bricks.end(), [](const auto& a, const auto& b) {
        return a.start_z < b.start_z;
    });

    std::unordered_map<int, std::unordered_set<int>> k_to_v; 
    std::unordered_map<int, std::unordered_set<int>> v_to_k; 

    for(size_t j = 0; j < bricks.size(); j++) {
        for(size_t i = 0; i < j; i++) {
            if(overlap(bricks[i], bricks[j]) && bricks[j].start_z == bricks[i].end_z + 1) {
                k_to_v[i].insert(j);
                v_to_k[j].insert(i);
            }
        }
    }

    int sum = 0;
    
    for(size_t i = 0; i < bricks.size(); i++) {
        std::queue<int> q;
        std::unordered_set<int> seen;
        for(const auto& x: k_to_v[i]) {
            if(v_to_k[x].size() == 1) {
                q.push(x);
                seen.insert(x);
            }
        }
        seen.insert(i);

        while(!q.empty()) {
            int j = q.front();
            q.pop();

            for(const auto& k: k_to_v[j]) {
                if(seen.count(k)) continue;

                bool all = true;
                for(const auto& l: v_to_k[k]) {
                    if(!seen.count(l)) {
                        all = false;
                        break;
                    }
                }

                if(all) {
                    q.push(k);
                    seen.insert(k);
                }
            }
        }

        sum += seen.size() - 1;
    }

    out << sum;

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
