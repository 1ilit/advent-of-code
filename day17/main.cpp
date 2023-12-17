#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <climits>
#include <set>
#include <queue>
#include <cmath>

const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct Node {
    int hl, r, c, dr, dc, n;
};

struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.hl > b.hl;
    }
};

int get_min_path_p1(std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    std::set<std::tuple<int, int, int, int, int>> seen;
    std::priority_queue<Node, std::vector<Node>, Compare> pq;
    pq.push({0, 0, 0, 0, 0, 0});

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        int hl = node.hl;
        int r = node.r;
        int c = node.c;
        int dr = node.dr;
        int dc = node.dc;
        int n = node.n;

        if (r == rows - 1 && c == cols - 1) {
            return hl;
        }

        if (seen.count({r, c, dr, dc, n})) {
            continue;
        }

        seen.insert({r, c, dr, dc, n});

        if (n < 3 && (dc != 0 || dr != 0)) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                pq.push({hl + grid[nr][nc], nr, nc, dr, dc, n + 1});
            }
        }

        for (const auto& dir : directions) {
            int ndr = dir.first;
            int ndc = dir.second;

            if ((ndr != dr || ndc != dc) && (ndr != -dr || ndc != -dc)) {
                int nr = r + ndr;
                int nc = c + ndc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    pq.push({hl + grid[nr][nc], nr, nc, ndr, ndc, 1});
                }
            }
        }
    }

    return -1;
}

int get_min_path_p2(std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    std::set<std::tuple<int, int, int, int, int>> seen;
    std::priority_queue<Node, std::vector<Node>, Compare> pq;
    pq.push({0, 0, 0, 0, 0, 0});

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        int hl = node.hl;
        int r = node.r;
        int c = node.c;
        int dr = node.dr;
        int dc = node.dc;
        int n = node.n;

        if (r == rows - 1 && c == cols - 1 && n >= 4) {
            return hl;
        }

        if (seen.count({r, c, dr, dc, n})) {
            continue;
        }

        seen.insert({r, c, dr, dc, n});

        if (n < 10 && (dc != 0 || dr != 0)) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                pq.push({hl + grid[nr][nc], nr, nc, dr, dc, n + 1});
            }
        }

        if(n >= 4 || (dc == 0 && dr == 0)) {
            for (const auto& dir : directions) {
                int ndr = dir.first;
                int ndc = dir.second;

                if ((ndr != dr || ndc != dc) && (ndr != -dr || ndc != -dc)) {
                    int nr = r + ndr;
                    int nc = c + ndc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        pq.push({hl + grid[nr][nc], nr, nc, ndr, ndc, 1});
                    }
                }
            }
        }
    }

    return -1;
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::vector<std::vector<int>> grid;
    int i = 0;
    while(std::getline(in, line)) {
        grid.push_back(std::vector<int>());
        for(char c: line){
            grid[i].push_back(c - '0');
        }
        i++;
    }

    out << get_min_path_p1(grid);

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
    std::vector<std::vector<int>> grid;
    int i = 0;
    while(std::getline(in, line)) {
        grid.push_back(std::vector<int>());
        for(char c: line){
            grid[i].push_back(c - '0');
        }
        i++;
    }

    out << get_min_path_p2(grid);

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
