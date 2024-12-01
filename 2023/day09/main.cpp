#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

bool is_all_zeros(const std::vector<int>& v) {
    for(int x: v)
        if (x != 0) return false;
    return true;
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    int sum = 0;
    std::string line;

    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::vector<std::vector<int>> nums;

        int row = 0;
        nums.push_back(std::vector<int>());
        int num;
        while(ss >> num) nums[row].push_back(num);

        while(true) {
            if(is_all_zeros(nums[row])) break;

            row++;
            nums.push_back(std::vector<int>());
            
            for(size_t i = 1; i < nums[row - 1].size(); i++) {
                nums[row].push_back(nums[row - 1][i] - nums[row - 1][i - 1]);
            }
        }

        for(int i = nums.size() - 1; i >= 0; i--) {
            sum += nums[i][nums[i].size() - 1];
        }
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

    int sum = 0;
    std::string line;

    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::vector<std::vector<int>> nums;

        int row = 0;
        nums.push_back(std::vector<int>());
        int num;
        while(ss >> num) nums[row].push_back(num);

        while(true) {
            if(is_all_zeros(nums[row])) break;

            row++;
            nums.push_back(std::vector<int>());
            
            for(size_t i = 1; i < nums[row - 1].size(); i++) {
                nums[row].push_back(nums[row - 1][i] - nums[row - 1][i - 1]);
            }
        }

        int local_sum = 0;
        for(int i = nums.size() - 1; i >= 0; i--) {
            local_sum = nums[i][0] - local_sum;
        }

        sum += local_sum;
    }

    out << sum;

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}
