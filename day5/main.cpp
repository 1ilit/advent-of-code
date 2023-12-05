#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <climits>
#include <cmath>

typedef struct {
    unsigned long dest;
    unsigned long src;
    unsigned long len;
} range;

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    int next = 0;
    std::string line;
    std::getline(in, line);

    std::stringstream ss(line);
    std::vector<unsigned long> seeds;
    std::string token;
    ss >> token;

    while(ss >> token) {
        seeds.push_back(std::stoul(token));
    }

    std::vector<std::vector<range>> maps;

    while(std::getline(in, line)) {
        if(!line.compare("")) {
            maps.push_back(std::vector<range>());
            next++;
            continue;
        }

        if(!line.compare("seed-to-soil map:")) {
            continue;
        } else if(!line.compare("soil-to-fertilizer map:")) {
            continue;
        } else if(!line.compare("fertilizer-to-water map:")) {
            continue;
        } else if(!line.compare("water-to-light map:")) {
            continue;
        } else if(!line.compare("light-to-temperature map:")) {
            continue;
        } else if(!line.compare("temperature-to-humidity map:")) {
            continue;
        } else if(!line.compare("humidity-to-location map:")) {
            continue;
        }

        std::stringstream s(line);
        unsigned long dest, src, len;
        s >> dest >> src >> len;

        maps[next - 1].push_back({dest, src, len});
    }

    unsigned long min = INT_MAX;
    for(unsigned long seed: seeds) {
        unsigned long key = seed;
        for(const auto& map: maps) {
            for(const range& r: map) {
                if(r.src <= key && key < r.src + r.len) {
                    key = r.dest + (key - r.src);
                    break;
                }
            }
        }
        if(key < min) {
            min = key;
        }
    }

    out << min;

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
    
    int next = 0;
    std::string line;
    std::getline(in, line);

    std::stringstream ss(line);
    std::vector<unsigned long> seeds;
    std::string token;
    ss >> token;

    while(ss >> token) {
        seeds.push_back(std::stoul(token));
    }

    std::vector<std::vector<range>> maps;

    while(std::getline(in, line)) {
        if(!line.compare("")) {
            maps.push_back(std::vector<range>());
            next++;
            continue;
        }

        if(!line.compare("seed-to-soil map:")) {
            continue;
        } else if(!line.compare("soil-to-fertilizer map:")) {
            continue;
        } else if(!line.compare("fertilizer-to-water map:")) {
            continue;
        } else if(!line.compare("water-to-light map:")) {
            continue;
        } else if(!line.compare("light-to-temperature map:")) {
            continue;
        } else if(!line.compare("temperature-to-humidity map:")) {
            continue;
        } else if(!line.compare("humidity-to-location map:")) {
            continue;
        }

        std::stringstream s(line);
        unsigned long dest, src, len;
        s >> dest >> src >> len;

        maps[next - 1].push_back({dest, src, len});
    }

    unsigned long min = INT_MAX;

    for(size_t i = 0; i < seeds.size(); i += 2) {
        for(size_t seed = seeds[i]; seed < seeds[i] + seeds[i + 1]; seed++) {   
            unsigned long key = seed;
            for(const auto& map: maps) {
                for(const range& r: map) {
                    if(r.src <= key && key < r.src + r.len) {
                        key = r.dest + (key - r.src);
                        break;
                    }
                }
            }
            if(key < min) {
                min = key;
            }
        }
    }

    out << min;

    out.close();
    in.close();
}


int main() {
    solve_p2();
    return 0;
}
