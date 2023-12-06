#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <cmath>

std::vector<std::pair<int, int>> directions = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};

bool is_symbol(char c) {
    return !isdigit(c) && c != '.';
}

bool check_part_number(const std::vector<std::string>& schema, int row, int col) {
    int rows = schema.size();
    int cols = schema[0].length();

    for (const auto& direction : directions) {
        int new_row = row + direction.first;
        int new_col = col + direction.second;
        if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols && is_symbol(schema[new_row][new_col])) {
            return true;
        }
    }

    return false;
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    int sum = 0;
    std::vector<std::string> schema;
    std::string line;
    while(in >> line) {
        schema.push_back(line);
    }

    for(size_t i = 0; i < schema.size(); i++) {
        int num = 0;
        bool is_part_number = false;
        for(size_t j = 0; j < schema[i].length(); j++) {
            if(isdigit(schema[i][j])) {
                num = num * 10 + (schema[i][j] - '0');
                if(!is_part_number) {
                    is_part_number = check_part_number(schema, i, j);
                }
            } else {
                if(is_part_number) sum += num;
                num = 0;
                is_part_number = false;
            }

            if (j == schema.size() - 1 && is_part_number)
                sum += num;
        }
    }

    out << sum;

    out.close();
    in.close();
}

std::pair<int, std::pair<int, int>> get_num(const std::string& str, int i, int j) {
    int num = 0;
    while (j - 1 >= 0 && isdigit(str[j - 1]))
        j--;

    while (isdigit(str[j])) {
        num = num * 10 + (str[j] - '0');
        j++;
    }
    return {num, {i, j}};
}

void solve_p2() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p2.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    int sum = 0;
    std::vector<std::string> schema;
    std::string line;
    while(in >> line) {
        schema.push_back(line);
    }

    for(size_t i = 0; i < schema.size(); i++) {
        for(size_t j = 0; j < schema[i].length(); j++) {
            if(schema[i][j] == '*') {
                std::set<std::pair<int, std::pair<int, int>>> nums;
                for (const auto& direction : directions) {
                    int new_row = i + direction.first;
                    int new_col = j + direction.second;
                    if (new_row >= 0 && new_row <= (int)schema.size() && new_col >= 0 && new_col < (int)schema[i].length() && isdigit(schema[new_row][new_col])) {
                        nums.insert(get_num(schema[new_row], new_row, new_col));
                    }
                }
                if(nums.size() == 2) {
                    int ratio = 1;
                    for(const auto& p: nums) {
                        ratio *= p.first;
                    }
                    sum += ratio;
                }
            }
        }
    }

    out << sum;

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
