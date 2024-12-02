#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cmath>

bool are_levels_okay(int l1, int l2, bool is_increasing)
{
    int diff = std::abs(l1 - l2);
    if (diff < 1 || diff > 3)
    {
        return false;
    }

    return (is_increasing == (l1 < l2));
}

bool is_safe(const std::vector<int> &level)
{
    bool is_increasing = level[0] < level[1];

    for (size_t i = 1; i < level.size(); i++)
    {
        if (!are_levels_okay(level[i - 1], level[i], is_increasing))
        {
            return false;
        }
    }

    return true;
}

bool is_safe_with_dampener(const std::vector<int> &level)
{

    if (is_safe(level))
        return true;

    for (size_t i = 0; i < level.size(); i++)
    {
        std::vector<int> new_level = level;
        new_level.erase(new_level.begin() + i);

        if (is_safe(new_level))
            return true;
    }

    return false;
}

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    int count = 0;
    std::string line;
    while (std::getline(in, line))
    {
        int number;
        std::vector<int> level;
        std::stringstream ss(line);
        while (ss >> number)
        {
            level.push_back(number);
        }

        if (is_safe(level))
            count++;
    }

    out << count;
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    int count = 0;
    std::string line;
    while (std::getline(in, line))
    {
        int number;
        std::vector<int> level;
        std::stringstream ss(line);
        while (ss >> number)
        {
            level.push_back(number);
        }

        if (is_safe_with_dampener(level))
            count++;
    }

    out << count;
}

int main()
{
    solve1();
    solve2();
    return 0;
}
