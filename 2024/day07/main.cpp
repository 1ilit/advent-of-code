#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

bool can_be_constructed(long long test, std::vector<long long> &values, int i, bool concat)
{
    if (i == 0)
        return test == values[i];

    if (test % values[i] == 0 && can_be_constructed(test / values[i], values, i - 1, concat))
    {
        return true;
    }

    if (test - values[i] > 0 && can_be_constructed(test - values[i], values, i - 1, concat))
    {
        return true;
    }

    std::string value_str = std::to_string(values[i]);
    std::string test_str = std::to_string(test);

    if (concat && test_str.length() > value_str.length())
    {
        std::string suffix = test_str.substr(test_str.length() - value_str.length());
        if (!value_str.compare(suffix) && can_be_constructed(std::stoll(test_str.substr(0, test_str.length() - value_str.length())), values, i - 1, concat))
            return true;
    }

    return false;
}

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    long long sum = 0;

    std::string line;
    while (std::getline(in, line))
    {
        int colon = line.find(':');

        long long test = std::stoll(line.substr(0, colon));
        std::vector<long long> values;

        std::stringstream ss(line.substr(colon + 2, line.length()));
        std::string num;
        while (std::getline(ss, num, ' '))
        {
            values.push_back(std::stoll(num));
        }

        if (can_be_constructed(test, values, values.size() - 1, false))
        {
            sum += test;
        }
    }

    out << sum;
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    long long sum = 0;

    std::string line;
    while (std::getline(in, line))
    {
        int colon = line.find(':');

        long long test = std::stoll(line.substr(0, colon));
        std::vector<long long> values;

        std::stringstream ss(line.substr(colon + 2, line.length()));
        std::string num;
        while (std::getline(ss, num, ' '))
        {
            values.push_back(std::stoll(num));
        }

        if (can_be_constructed(test, values, values.size() - 1, true))
        {
            sum += test;
        }
    }

    out << sum;
}

int main()
{
    solve1();
    solve2();
    return 0;
}