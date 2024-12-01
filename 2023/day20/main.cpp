#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <algorithm>

long long lcm(long long a, long long b) {
    return a / std::__gcd(a, b) * b;
}

struct Module {
    std::string name;
    char type;
    std::vector<std::string> outputs;
    bool flip_flop_mem;
    std::unordered_map<std::string, bool> conj_mem;
};

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::vector<std::string> broadcasts;
    std::unordered_map<std::string, Module> modules;

    std::string line;
    while(std::getline(in, line)) {
        int arrow = line.find(" -> ");
        std::string name = line.substr(0, arrow);
        std::string rest = line.substr(arrow + 4, line.length() - arrow - 4);
        std::stringstream ss(rest);
        std::vector<std::string> outputs;
        std::string token;
        while(std::getline(ss, token, ',')) {
            if(token[0] == ' ') token = token.substr(1, token.length() - 1);
            outputs.push_back(token);
        }

        if(!name.compare("broadcaster")) {
            for(const auto& x : outputs) broadcasts.push_back(x);
        } else if(name[0] == '%') {
            name = name.substr(1, name.length() - 1);
            Module m = {
                name,
                '%',
                outputs,
                false,
                {}
            };
            modules[name] = m;
        } else if(name[0] == '&') {
            name = name.substr(1, name.length() - 1);
            Module m = {
                name,
                '&',
                outputs,
                false,
                {}
            };
            modules[name] = m;
        }
    }

    for(const auto& p: modules) {
        for(const auto& o: p.second.outputs) {
            if(modules.count(o) && modules[o].type=='&') {
                modules[o].conj_mem[p.first] = false;
            }
        }
    }

    int low_count = 0;
    int high_count = 0;

    for(int i = 0; i < 1000; i++) {
        low_count++;

        std::queue<std::tuple<std::string, std::string, bool>> q;

        for(const auto& s: broadcasts) {
            q.push({"broadcaster", s, false});
        }

        while(!q.empty()) {
            auto front = q.front();
            q.pop();

            std::string src = std::get<0>(front);
            std::string dest = std::get<1>(front);
            bool signal = std::get<2>(front);

            if(signal) {
                high_count++;
            } else {
                low_count++;
            }

            if(!modules.count(dest)) continue;

            if(modules[dest].type == '%') {
                if(!signal) {
                    modules[dest].flip_flop_mem = !modules[dest].flip_flop_mem;
                    bool next_signal = modules[dest].flip_flop_mem;
                    for(const auto& o: modules[dest].outputs) {
                        q.push({modules[dest].name, o, next_signal});
                    }
                }
            } else {
                modules[dest].conj_mem[src] = signal;
                bool all_high = true;
                for(const auto& x: modules[dest].conj_mem) {
                    if(!x.second) {
                        all_high = false;
                        break;
                    }
                }

                bool next_signal = !all_high;
                for(const auto& o: modules[dest].outputs) {
                    q.push({modules[dest].name, o, next_signal});
                }   
            }
        }
    }

    out << low_count * high_count;

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

    std::vector<std::string> broadcasts;
    std::unordered_map<std::string, Module> modules;

    std::string line;
    while(std::getline(in, line)) {
        int arrow = line.find(" -> ");
        std::string name = line.substr(0, arrow);
        std::string rest = line.substr(arrow + 4, line.length() - arrow - 4);
        std::stringstream ss(rest);
        std::vector<std::string> outputs;
        std::string token;
        while(std::getline(ss, token, ',')) {
            if(token[0] == ' ') token = token.substr(1, token.length() - 1);
            outputs.push_back(token);
        }

        if(!name.compare("broadcaster")) {
            for(const auto& x : outputs) broadcasts.push_back(x);
        } else if(name[0] == '%') {
            name = name.substr(1, name.length() - 1);
            Module m = {
                name,
                '%',
                outputs,
                false,
                {}
            };
            modules[name] = m;
        } else if(name[0] == '&') {
            name = name.substr(1, name.length() - 1);
            Module m = {
                name,
                '&',
                outputs,
                false,
                {}
            };
            modules[name] = m;
        }
    }

    for(const auto& p: modules) {
        for(const auto& o: p.second.outputs) {
            if(modules.count(o) && modules[o].type=='&') {
                modules[o].conj_mem[p.first] = false;
            }
        }
    }

    std::string target;
    for(const auto& p: modules) {
        bool found_rx = false;
        for(const auto& o: p.second.outputs) {
            if(!o.compare("rx")) {
                target = p.second.name;
                found_rx = true;
                break;
            }
        }
        if(found_rx) break;
    }

    std::unordered_map<std::string, int> seen;
    std::unordered_map<std::string, int> cycle_counts;
    for(const auto& p: modules) {
        for(const auto& o: p.second.outputs) {
            if(!o.compare(target)) {
                seen[p.second.name] = 0;
                break;
            }
        }
    }

    long long count = 0;
    long long presses = 1;
    while(true) {
        count++;
        bool enough = false;
        std::queue<std::tuple<std::string, std::string, bool>> q;

        for(const auto& s: broadcasts) {
            q.push({"broadcaster", s, false});
        }

        while(!q.empty()) {
            auto front = q.front();
            q.pop();

            std::string src = std::get<0>(front);
            std::string dest = std::get<1>(front);
            bool signal = std::get<2>(front);

            if(!modules.count(dest)) continue;

            if(!modules[dest].name.compare(target) && signal) {
                seen[src]++;

                if(!cycle_counts.count(src)) {
                    cycle_counts[src] = count;
                }
            
                bool all = true;
                for(const auto& x : seen){
                    if(!x.second) {
                        all = false;
                        break;
                    }
                }

                if(all) {
                    for(const auto& x : cycle_counts) {
                        presses = lcm(x.second, presses);
                    }
                    enough = true;
                }
            }

            if(modules[dest].type == '%') {
                if(!signal) {
                    modules[dest].flip_flop_mem = !modules[dest].flip_flop_mem;
                    bool next_signal = modules[dest].flip_flop_mem;
                    for(const auto& o: modules[dest].outputs) {
                        q.push({modules[dest].name, o, next_signal});
                    }
                }
            } else {
                modules[dest].conj_mem[src] = signal;
                bool all_high = true;
                for(const auto& x: modules[dest].conj_mem) {
                    if(!x.second) {
                        all_high = false;
                        break;
                    }
                }

                bool next_signal = !all_high;
                for(const auto& o: modules[dest].outputs) {
                    q.push({modules[dest].name, o, next_signal});
                }   
            }
        }

        if(enough) break;
    }

    out << presses;

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
