#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

int get_calibration_value_p1(std::ifstream& in) {
    int sum = 0;
    std::string line;
    while (in >> line) {
        int first = 0;
        int last = 0;
        for(size_t i = 0; i < line.length(); i++) {
            if(isdigit(line[i])) {
                first = line[i] - '0';
                break;
            }
        }
        for(size_t i = line.length() - 1; i >= 0; i--) {
            if(isdigit(line[i])) {
                last = line[i] - '0';
                break;
            }
        }
        sum += first * 10 + last;
    }
    return sum;
}

int get_calibration_value_p2(std::ifstream& in) {
    int sum = 0;
    std::unordered_map<std::string, int> string_to_digit = {
        {"zero"  , 0},
        {"one"   , 1},
        {"two"   , 2},
        {"three" , 3},
        {"four"  , 4},
        {"five"  , 5},
        {"six"   , 6},
        {"seven" , 7},
        {"eight" , 8},
        {"nine"  , 9}
    };
    std::string line;
    while(in >> line) {
        int first = 0;
        int last = 0;
        for(size_t i = 0; i < line.length(); i++) {
            if(isdigit(line[i])) {
                first = line[i] - '0';
                break;
            }
            bool found = false;
            for(const auto& pair: string_to_digit){
                if(i + pair.first.length() > line.length()) 
                    continue;
                
                if(line.substr(i, pair.first.length()).compare(pair.first) == 0){
                    first = string_to_digit[pair.first];
                    found = true;
                    break;
                }
            }

            if(found) break;
        }
        for(size_t i = line.length() - 1; i >= 0; i--) {
            if(isdigit(line[i])) {
                last = line[i] - '0';
                break;
            } 
            bool found = false;
            for(const auto& pair: string_to_digit) {
                if(i < pair.first.length() - 1) 
                    continue;
                
                if(line.substr(i - pair.first.length() + 1, pair.first.length()).compare(pair.first) == 0){
                    last = string_to_digit[pair.first];
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
        sum += first * 10 + last;
    }
    return sum;
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    out << get_calibration_value_p1(in);

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

    out << get_calibration_value_p2(in);

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
