#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cmath>

std::pair<int, int> up = {-1, 0};
std::pair<int, int> right = {0, 1};
std::pair<int, int> down = {1, 0};
std::pair<int, int> left = {0, -1};

std::unordered_map<char, std::pair<std::pair<int, int>, std::pair<int, int>>> pipe_to_dir = {
    {'|', {up, down}}, {'-', {right, left}}, {'L', {up, right}},
    {'J', {up, left}}, {'7', {down, left}},  {'F', {right, down}}
};

std::vector<std::pair<int, int>> dirs = {up, down, left, right};

bool operator==(const std::pair<std::pair<int, int>, std::pair<int, int>>& lhs,
                const std::pair<std::pair<int, int>, std::pair<int, int>>& rhs) {
    return (lhs.first == rhs.first && lhs.second == rhs.second) || (lhs.second == rhs.first && lhs.first == rhs.second);
}

void recover_start_pos(int startx, int starty, std::vector<std::string>& map){
    std::vector<std::pair<int, int>> edges;
    for (const auto& d : dirs) {
        if (starty + d.first < 0 || startx + d.second < 0 || 
            starty + d.first >= (int)map.size() || startx + d.second >= (int)map[starty].length()) {
            continue;
        }

        char pipe = map[starty + d.first][startx + d.second];
        if (pipe == '.') {
          continue;
        }

        std::pair<int, int> required_edge = {-d.first, -d.second};
        if (pipe_to_dir[pipe].first == required_edge || pipe_to_dir[pipe].second == required_edge) {
          edges.push_back(d);
        }
    }

    if (edges.size() != 2) {
      return;
    }

    std::pair<std::pair<int, int>, std::pair<int, int>> needed = {edges[0], edges[1]};
    for(const auto& p: pipe_to_dir) {
        if(p.second == needed) {
            map[starty][startx] = p.first;
            return;
        }
    }

    return;
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

    int startx = -1, starty = -1;
    for(size_t i = 0; i < map.size(); i++) {
        bool found = false;
        for(size_t j = 0; j < map[i].length(); j++) {
            if(map[i][j] == 'S') {
                found = true;
                starty = i;
                startx = j;
                break;
            }
        }

        if(found) break;
    }

    recover_start_pos(startx, starty, map);

    int count = 0;
    int currentx = startx, currenty = starty;
    int prevx = -1, prevy = -1;

    do {
        char c = map[currenty][currentx];

        std::pair<int, int> dir1 = pipe_to_dir[c].first;
        std::pair<int, int> dir2 = pipe_to_dir[c].second;

        prevx = currentx;
        prevy = currenty;

        if(!(currenty + dir1.first == prevy && currentx + dir1.second == prevx)) {
            currenty += dir1.first;
            currentx += dir1.second;
        } else {
            currenty += dir2.first;
            currentx += dir2.second;
        }

        count++;
    } while(!(currentx == startx && currenty == starty));

    out << count / 2;

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

    int startx = -1, starty = -1;
    for(size_t i = 0; i < map.size(); i++) {
        bool found = false;
        for(size_t j = 0; j < map[i].length(); j++) {
            if(map[i][j] == 'S') {
                found = true;
                starty = i;
                startx = j;
                break;
            }
        }

        if(found) break;
    }

    recover_start_pos(startx, starty, map);

    int count = 0;
    int currentx = startx, currenty = starty;
    int prevx = -1, prevy = -1;

    std::vector<std::pair<int, int>> loop;

    do {
        char c = map[currenty][currentx];
        loop.push_back({currenty, currentx});

        std::pair<int, int> dir1 = pipe_to_dir[c].first;
        std::pair<int, int> dir2 = pipe_to_dir[c].second;

        prevx = currentx;
        prevy = currenty;
    
        if(!(currenty + dir1.first == prevy && currentx + dir1.second == prevx)) {
            currenty += dir1.first;
            currentx += dir1.second;
        } else {
            currenty += dir2.first;
            currentx += dir2.second;
        }
    } while(!(currentx == startx && currenty == starty));

    for (size_t i = 0; i < map.size(); i++) {
        int parity = 0;
        char entering_pipe = 0;
        for (size_t j = 0; j < map[i].length(); ++j) {
            auto loop_pos = std::find(loop.begin(), loop.end(), std::pair<int, int>(i, j));
            bool in_loop = loop_pos != loop.end();

            if (!in_loop) {
                if (parity % 2) {
                  count++;
                }
                continue;
            } else {
                loop.erase(loop_pos);
                char pipe = map[i][j];
                switch (pipe) {
                  case '|':
                    parity++;
                    break;
                  case 'F':
                  case 'L':
                    entering_pipe = pipe;
                    break;
                  case '7':
                    parity += entering_pipe == 'L';
                    break;
                  case 'J':
                    parity += entering_pipe == 'F';
                    break;
                }
            }
        }
    }

    out << count;

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
