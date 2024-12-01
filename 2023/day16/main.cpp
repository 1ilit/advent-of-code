#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <deque>
#include <tuple>
#include <cmath>

const int i_row = 0;
const int i_col = 1;
const int i_dr = 2;
const int i_dc = 3;

int count_energized_tiles(const std::vector<std::string>& pattern, std::tuple<int, int, int, int> start) {
    std::set<std::tuple<int, int, int, int>> seen;
    std::deque<std::tuple<int, int, int, int>> queue;

    queue.push_back(start);

    while(queue.size() != 0) {
        std::tuple<int, int, int, int> next = queue.front();
        queue.pop_front();
        
        int dr = std::get<i_dr>(next);
        std::get<i_row>(next) += dr;
        int row = std::get<i_row>(next);

        int dc = std::get<i_dc>(next);
        std::get<i_col>(next) += dc;
        int col = std::get<i_col>(next);

        if(row >= (int)pattern.size() || row < 0 || col < 0 || col >= (int)pattern[0].length())
            continue;

        char c = pattern[row][col];

        if(c == '.' || (c == '-' && dc != 0) || (c == '|' && dr != 0)){
            if(!seen.count(next)) {
                seen.insert(next);
                queue.push_back(next);
            }
        } else if (c == '/') {
            int temp = dr;
            dr = -dc;
            dc = -temp;

            if(!seen.count({row, col, dr, dc})) {
                seen.insert({row, col, dr, dc});
                queue.push_back({row, col, dr, dc});
            }
        } else if (c == '\\') {
            int temp = dr;
            dr = dc;
            dc = temp;

            if(!seen.count({row, col, dr, dc})) {
                seen.insert({row, col, dr, dc});
                queue.push_back({row, col, dr, dc});
            }
        } else {
            if(c=='|') {
                if(!seen.count({row, col, 1, 0})) {
                    seen.insert({row, col, 1, 0});
                    queue.push_back({row, col, 1, 0});
                }

                if(!seen.count({row, col, -1, 0})) {
                    seen.insert({row, col, -1, 0});
                    queue.push_back({row, col, -1, 0});
                }
            } else {
                if(!seen.count({row, col, 0, -1})) {
                    seen.insert({row, col, 0, -1});
                    queue.push_back({row, col, 0, -1});
                }

                if(!seen.count({row, col, 0, 1})) {
                    seen.insert({row, col, 0, 1});
                    queue.push_back({row, col, 0, 1});
                }
            }
        }
    }

    std::set<std::pair<int, int>> coords;

    for(const auto& x: seen) {
        coords.insert({std::get<i_row>(x), std::get<i_col>(x)});
    }

    return (int)coords.size();
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

    out << count_energized_tiles(pattern, {0, -1, 0, 1});

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
    std::vector<std::string> pattern;
    while(std::getline(in, line)) {
        pattern.push_back(line);
    }

    int max = 0;
    for(size_t i = 0; i < pattern.size(); i++) {
        max = std::max(max, count_energized_tiles(pattern, {i, -1, 0, 1}));
        max = std::max(max, count_energized_tiles(pattern, {i, pattern[0].length(), 0, -1}));
    }

    for(size_t j = 0; j < pattern[0].length(); j++) {
        max = std::max(max, count_energized_tiles(pattern, {-1, j, 1, 0}));
        max = std::max(max, count_energized_tiles(pattern, {pattern.size(), j, -1, 0}));
    }

    out << max;

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
