#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>

const std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const std::map<char, std::vector<std::pair<int, int>>> dirs = {
    {'^', {{-1, 0}}},
    {'v', {{1, 0}}},
    {'<', {{0, -1}}},
    {'>', {{0, 1}}},
    {'.', directions},
};

std::vector<std::pair<int, int>> get_contracted_pts(const std::vector<std::string>& grid) {
    std::vector<std::pair<int, int>> points;
    for(size_t i = 0; i < grid.size(); i++) {
        for(size_t j = 0; j < grid[0].length(); j++) {
            if(grid[i][j] == '#') continue;

            int neighbors = 0;
            for(const auto& d: directions) {
                size_t next_r = i + d.first;
                size_t next_c = j + d.second;

                if(next_c < 0 || next_c >= grid[0].length() || next_r < 0 || next_r >= grid.size()) 
                    continue;

                if(grid[next_r][next_c] != '#') neighbors++;
            }

            if(neighbors >= 3) {
                points.push_back({i, j});
            }
        }
    }

    return points;
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::vector<std::string> grid;
    std::string line;
    while(std::getline(in, line)) {
        grid.push_back(line);
    }

    std::vector<std::pair<int, int>> points = get_contracted_pts(grid);

    std::pair<int, int> start = {0, grid[0].find('.')};
    std::pair<int, int> end = {grid.size() - 1, grid[grid.size() - 1].find('.')};

    points.push_back(start);
    points.push_back(end);

    std::map<std::pair<int, int>, std::set<std::tuple<int, int, int>>> graph;

    for(const auto& p: points) {
        std::stack<std::tuple<int, int, int>> stack;
        std::set<std::pair<int, int>> seen;
        stack.push({p.first, p.second, 0});
        seen.insert(p);

        while(!stack.empty()) {
            auto t = stack.top();
            stack.pop();

            int r = std::get<0>(t);
            int c = std::get<1>(t);
            int n = std::get<2>(t);

            if(n != 0 && std::find(points.begin(), points.end(), std::make_pair(r, c)) != points.end()) {
                graph[{p.first, p.second}].insert({r, c, n});
                continue;
            }

            for(const auto& d: dirs.at(grid[r][c])) {
                size_t next_r = r + d.first;
                size_t next_c = c + d.second;

                if(next_c < 0 || next_c >= grid[0].length() || next_r < 0 || next_r >= grid.size()) 
                    continue;
            
                if(grid[next_r][next_c]=='#') continue;
                if(seen.count({next_r, next_c})) continue;

                stack.push({next_r, next_c, n + 1});
                seen.insert({next_r, next_c});
            }
        }
    }

    std::set<std::pair<int, int>> seen;
    std::function<int(std::pair<int, int>)> dfs = [&](std::pair<int, int> pt) -> int {
        if (pt == end) {
            return 0;
        }

        int max = -1000000000;

        seen.insert(pt);
        for (const auto& n : graph[pt]) {
            if (!seen.count({std::get<0>(n), std::get<1>(n)})) {
                max = std::max(max, dfs({std::get<0>(n), std::get<1>(n)}) + std::get<2>(n));
            }
        }
        seen.erase(pt);

        return max;
    };

    out << dfs(start);

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

    std::vector<std::string> grid;
    std::string line;
    while(std::getline(in, line)) {
        grid.push_back(line);
    }

    std::vector<std::pair<int, int>> points = get_contracted_pts(grid);

    std::pair<int, int> start = {0, grid[0].find('.')};
    std::pair<int, int> end = {grid.size() - 1, grid[grid.size() - 1].find('.')};

    points.push_back(start);
    points.push_back(end);

    std::map<std::pair<int, int>, std::set<std::tuple<int, int, int>>> graph;

    for(const auto& p: points) {
        std::stack<std::tuple<int, int, int>> stack;
        std::set<std::pair<int, int>> seen;
        stack.push({p.first, p.second, 0});
        seen.insert(p);

        while(!stack.empty()) {
            auto t = stack.top();
            stack.pop();

            int r = std::get<0>(t);
            int c = std::get<1>(t);
            int n = std::get<2>(t);

            if(n != 0 && std::find(points.begin(), points.end(), std::make_pair(r, c)) != points.end()) {
                graph[{p.first, p.second}].insert({r, c, n});
                continue;
            }

            for(const auto& d: directions) {
                size_t next_r = r + d.first;
                size_t next_c = c + d.second;

                if(next_c < 0 || next_c >= grid[0].length() || next_r < 0 || next_r >= grid.size()) 
                    continue;
            
                if(grid[next_r][next_c]=='#') continue;
                if(seen.count({next_r, next_c})) continue;

                stack.push({next_r, next_c, n + 1});
                seen.insert({next_r, next_c});
            }
        }
    }

    std::set<std::pair<int, int>> seen;
    std::function<int(std::pair<int, int>)> dfs = [&](std::pair<int, int> pt) -> int {
        if (pt == end) {
            return 0;
        }

        int max = -1000000000;

        seen.insert(pt);
        for (const auto& n : graph[pt]) {
            if (!seen.count({std::get<0>(n), std::get<1>(n)})) {
                max = std::max(max, dfs({std::get<0>(n), std::get<1>(n)}) + std::get<2>(n));
            }
        }
        seen.erase(pt);

        return max;
    };

    out << dfs(start);

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
