#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <cmath>

struct Rule {
    char label;
    char op;
    int value;
    std::string next;
};

struct Part {
    int x;
    int m;
    int a;
    int s;
};

struct PartWithRange {
    std::pair<int, int> x;
    std::pair<int, int> m;
    std::pair<int, int> a;
    std::pair<int, int> s;
};

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    bool p = false;
    std::vector<Part> parts;
    std::unordered_map<std::string, std::vector<Rule>> workflows;
    while(std::getline(in, line)) {
        if(!line.compare("") && !p) { 
            p = true; 
            continue;
        }
        if(!p) {
            int brace = line.find('{');
            std::string workflow = line.substr(0, brace);
            std::string rest = line.substr(brace + 1, line.length() - brace - 2);
            std::stringstream ss(rest);
            std::string token;
            std::vector<Rule> rules;
            while(std::getline(ss, token, ',')) {
                int colon = token.find(':');
                if(colon == -1) {
                    rules.push_back({'f', 'f', -1, token});
                } else {
                    rules.push_back({
                        token[0],
                        token[1],
                        std::stoi(token.substr(2, colon - 2)),
                        token.substr(colon + 1, token.length() - colon - 1)
                    });
                }
            }
            workflows[workflow] = rules;
        } else {
            std::string part = line.substr(1, line.length()-1);
            int x = -1, m = -1, a = -1, s = -1;
            std::stringstream ss(part);
            std::string token;
            while(std::getline(ss, token, ',')){
                char label = token[0];
                int value = std::stoi(token.substr(2, token.length() - 2));
                switch (label) {
                    case 'x':
                        x = value;
                        break;
                    case 'm':
                        m = value;
                        break;                    
                    case 'a':
                        a = value;
                        break;                    
                    case 's':
                        s = value;
                        break;
                    default: break;
                }  
            }

            parts.push_back({x, m, a, s});
        }
    }

    int sum = 0;
    for(const auto& p: parts) {
        std::string state = "in";
        while(true) {
            std::vector<Rule> current = workflows[state];

            for(const auto& r: current){
                if(r.label == 'f') {
                    state = r.next;
                    break;
                }

                int value = -1;
                switch(r.label) {
                    case 'x':
                        value = p.x;
                        break;
                    case 'm':
                        value = p.m;
                        break;
                    case 'a':
                        value = p.a;
                        break;
                    case 's':
                        value = p.s;
                        break;
                    default: break;
                }

                if(r.op == '<'){
                    if(value < r.value){
                        state = r.next;
                        break;
                    }
                } else {
                    if(value > r.value){
                        state = r.next;
                        break;
                    }
                }
            }

            if(!state.compare("A")) {
                sum += (p.x + p.m + p.a + p.s);
                break;
            }

            if(!state.compare("R")) {
                break;
            }
        }
    }

    out << sum;

    out.close();
    in.close();
}

std::pair<PartWithRange, PartWithRange> split_range(PartWithRange p, Rule r) {
    std::pair<int, int> range = {-1, -1};
    std::pair<int, int> t, f;
    switch(r.label) {
        case 'x':
            range = p.x;
            break;
        case 'm':
            range = p.m;
            break;
        case 'a':
            range = p.a;
            break;
        case 's':
            range = p.s;
            break;
        default: break;
    }

    if(r.op == '<'){
        t = {range.first, r.value - 1};
        f = {r.value, range.second};
    } else {
        t = {r.value + 1, range.second};
        f = {range.first, r.value};
    }

    PartWithRange t_part = p;
    PartWithRange f_part = p;
    
    switch(r.label) {
        case 'x':
            t_part.x = t;
            f_part.x = f;
            break;
        case 'm':
            t_part.m = t;
            f_part.m = f;
            break;
        case 'a':
            t_part.a = t;
            f_part.a = f;
            break;
        case 's':
            t_part.s = t;
            f_part.s = f;
            break;
        default: break;
    }
    return {t_part, f_part};
}

void solve_p2() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p2.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }
    
    std::string line;
    std::unordered_map<std::string, std::vector<Rule>> workflows;
    while(std::getline(in, line)) {
        if(!line.compare("")) { 
            break;
        }

        int brace = line.find('{');
        std::string workflow = line.substr(0, brace);
        std::string rest = line.substr(brace + 1, line.length() - brace - 2);
        std::stringstream ss(rest);
        std::string token;
        std::vector<Rule> rules;
        while(std::getline(ss, token, ',')) {
            int colon = token.find(':');
            if(colon == -1) {
                rules.push_back({'f', 'f', -1, token});
            } else {
                rules.push_back({
                    token[0],
                    token[1],
                    std::stoi(token.substr(2, colon - 2)),
                    token.substr(colon + 1, token.length() - colon - 1)
                });
            }
        }
        workflows[workflow] = rules;
    }

    long long count = 0;

    std::stack<std::pair<std::string, PartWithRange>> stack;
    stack.push({"in", {
        {1, 4000},
        {1, 4000},
        {1, 4000},
        {1, 4000}
    }});

    while(!stack.empty()) {
        std::string state = stack.top().first;
        PartWithRange part = stack.top().second;

        stack.pop();

        if(!state.compare("R")) continue;

        if(!state.compare("A")) {
            long long x = part.x.second - part.x.first + 1;
            long long m = part.m.second - part.m.first + 1;
            long long a = part.a.second - part.a.first + 1;
            long long s = part.s.second - part.s.first + 1;
            count += x * m * a * s;
        } else {
            std::vector<Rule> current = workflows[state];
            for(const auto& r: current) {
                if(r.label != 'f') {
                    std::pair<PartWithRange, PartWithRange> split = split_range(part, r);
                    stack.push({r.next, split.first});
                    part = split.second;
                }
            }
            stack.push({current[current.size() - 1].next, part});
        }
    }

    out << count;

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}
