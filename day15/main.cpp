#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

long long hash(std::string str) {
    long long current = 0;
    for(const char c: str) {
        current += c;
        current *= 17;
        current = current % 256;
    }
    return current;
} 

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    long long sum = 0;

    std::string str;
    while(std::getline(in, str, ',')){
        sum += hash(str);
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

    std::vector<std::vector<std::pair<std::string, int>>> hashmap(256, std::vector<std::pair<std::string, int>>());

    std::string str;
    while(std::getline(in, str, ',')){
        int equal = str.find('=');
        if(equal != -1) {
            std::string key = str.substr(0, equal);
            int lens = std::stoi(str.substr(equal + 1));
            long long h = hash(key);
            int found = -1;
            for(size_t i = 0; i < hashmap[h].size(); i++) {
                if(!key.compare(hashmap[h][i].first)) {
                    found = i;
                    break;
                }
            }
            if(found == -1){
                hashmap[h].push_back({ key, lens });
            } else {
                hashmap[h][found].second = lens;
            }
        } else {
            std::string key = str.substr(0, str.length() - 1);
            long long h = hash(key);
            int found = -1;
            for(size_t i = 0; i < hashmap[h].size(); i++) {
                if(!key.compare(hashmap[h][i].first)) {
                    found = i;
                    break;
                }
            }

            if(found != -1) {
                hashmap[h].erase(hashmap[h].begin() + found);
            }
        }
    }

    for(size_t i = 0; i < hashmap.size(); i++) {
        if(hashmap[i].size() == 0) continue;
        for(size_t j = 0; j < hashmap[i].size(); j++) {
            sum += (i + 1) * (j + 1) * hashmap[i][j].second;
        } 
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
