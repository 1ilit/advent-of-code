#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <tuple>

const std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

long long bfs(const std::vector<std::string>& map, int start_row, int start_col, int step_count) {
    std::set<std::pair<int, int>> seen;
    std::queue<std::tuple<int, int, int>> q;
    q.push({start_row, start_col, 0});

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int row = std::get<0>(p);
        int col = std::get<1>(p);
        int steps = std::get<2>(p);

        if (steps > step_count) {
            continue;
        }

        for (const auto& d : directions) {
            int new_row = row + d.first;
            int new_col = col + d.second;

            if(new_row < 0 || new_row >= (int)map.size() || new_col < 0 || new_col >= (int)map[0].length()) {
                continue;
            }

            if (map[new_row][new_col] != '#' && !seen.count({new_row, new_col})) {
                seen.insert({new_row, new_col});
                q.push({new_row, new_col, steps + 1});
            }
        }
    }

    long long count = 0;
    for (const auto& p : seen) {
        if ((p.first + p.second) % 2 == step_count % 2) {
            count++;
        }
    }
    return count;
}

std::vector<std::string> expand(const std::vector<std::string>& map, int factor) {
    std::vector<std::string> res;

    for (size_t i = 0; i < factor * map.size(); i++) {
        std::string new_row = "";
        for (size_t j = 0; j < factor * map[0].size(); j++) {
            new_row += (map[i % map.size()][j % map[0].size()]);
        }
        res.push_back(new_row);
    }

    return res;
}

std::vector<long long> lagrange(std::vector<long long> values) {
    long long a = values[0] / 2 - values[1] + values[2] / 2;
    long long b = -3 * (values[0] / 2) + 2 * values[1] - values[2] / 2;
    long long c = values[0];

    return {a, b, c};
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::vector<std::string> map;
    std::string line;

    while(std::getline(in, line)) {
        map.push_back(line);
    }

    int start_col = 0, start_row = 0;

    for(size_t i = 0; i < map.size(); i++) {
        bool found = false;
        for(size_t j = 0; j < map[i].length(); j++) {
            if(map[i][j] == 'S') {
                start_col = j;
                start_row = i;
                found = true;
                break;
            }
        }
        if(found) break;
    }

    out << bfs(map, start_row, start_col, 64);

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
    
    std::vector<std::string> map;
    std::string line;

    while(std::getline(in, line)) {
        map.push_back(line);
    }

    long long steps = 26501365;
    long long size = map.size();

    std::vector<std::string> expanded_map = expand(map, 7);

    int start_row = expanded_map.size() / 2;
    int start_col = expanded_map[0].size() / 2;

    long long a0 = bfs(expanded_map, start_row, start_col, size / 2);
    long long a1 = bfs(expanded_map, start_row, start_col, size / 2 + size);
    long long a2 = bfs(expanded_map, start_row, start_col, size / 2 + 2 * size);

    std::vector<long long> l = lagrange({a0, a1, a2});

    long long target = (steps - size / 2) / size;
    out << l[0] * target * target + l[1] * target + l[2];

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
