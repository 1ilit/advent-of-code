#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    std::map<char, std::vector<std::pair<int, int>>> antennas;

    std::string line;
    int n = 0;
    int m = 0;
    while (std::getline(in, line))
    {
        for (size_t j = 0; j < line.length(); j++)
        {
            if (line[j] != '.')
            {
                antennas[line[j]].push_back({n, j});
            }
        }
        m = line.length();
        n++;
    }

    std::set<std::pair<int, int>> antinodes;

    for (auto const &[k, v] : antennas)
    {
        for (size_t i = 0; i < v.size() - 1; i++)
        {
            for (size_t j = i + 1; j < v.size(); j++)
            {
                int i_dist = v[j].first - v[i].first;
                int j_dist = v[j].second - v[i].second;

                std::pair<int, int> antinode1 = {v[i].first - i_dist, v[i].second - j_dist};
                std::pair<int, int> antinode2 = {v[j].first + i_dist, v[j].second + j_dist};

                if (0 <= antinode1.first && antinode1.first < n && 0 <= antinode1.second && antinode1.second < m)
                {
                    antinodes.insert(antinode1);
                }

                if (0 <= antinode2.first && antinode2.first < n && 0 <= antinode2.second && antinode2.second < m)
                {
                    antinodes.insert(antinode2);
                }
            }
        }
    }

    out << antinodes.size();
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    std::map<char, std::vector<std::pair<int, int>>> antennas;

    std::string line;
    int n = 0;
    int m = 0;
    while (std::getline(in, line))
    {
        for (size_t j = 0; j < line.length(); j++)
        {
            if (line[j] != '.')
            {
                antennas[line[j]].push_back({n, j});
            }
        }
        m = line.length();
        n++;
    }

    std::set<std::pair<int, int>> antinodes;

    for (auto const &[k, v] : antennas)
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            for (size_t j = 0; j < v.size(); j++)
            {
                if (i == j)
                    continue;

                int i_dist = v[j].first - v[i].first;
                int j_dist = v[j].second - v[i].second;

                int r = v[i].first;
                int c = v[i].second;

                while (0 <= r && r < n && 0 <= c && c < m)
                {
                    antinodes.insert({r, c});
                    r += i_dist;
                    c += j_dist;
                }
            }
        }
    }

    out << antinodes.size();
}

int main()
{
    solve1();
    solve2();
    return 0;
}