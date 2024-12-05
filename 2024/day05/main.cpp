#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <set>

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    bool graph[100][100] = {false};
    std::vector<std::vector<int>> updates;

    std::string line;
    bool parsing_updates = false;
    while (std::getline(in, line))
    {
        if (!parsing_updates)
        {
            int pipe = line.find('|');
            if (pipe == std::string::npos)
            {
                parsing_updates = true;
                continue;
            }
            int x = std::stoi(line.substr(0, pipe));
            int y = std::stoi(line.substr(pipe + 1, line.length()));
            graph[x][y] = true;
        }
        else
        {
            std::vector<int> v;
            std::string num;
            std::stringstream ss(line);
            while (std::getline(ss, num, ','))
            {
                v.push_back(std::stoi(num));
            }

            updates.push_back(v);
        }
    }

    int sum = 0;
    for (auto &v : updates)
    {
        bool ok = true;
        for (int i = 0; i < v.size() - 1; i++)
        {
            for (int j = i + 1; j < v.size(); j++)
            {
                if (!graph[v[i]][v[j]])
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
                break;
        }

        if (ok)
            sum += v[int(v.size() / 2)];
    }
    out << sum;
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    bool graph[100][100] = {false};
    std::vector<std::vector<int>> updates;

    std::string line;
    bool parsing_updates = false;
    while (std::getline(in, line))
    {
        if (!parsing_updates)
        {
            int pipe = line.find('|');
            if (pipe == std::string::npos)
            {
                parsing_updates = true;
                continue;
            }
            int x = std::stoi(line.substr(0, pipe));
            int y = std::stoi(line.substr(pipe + 1, line.length()));
            graph[x][y] = true;
        }
        else
        {
            std::vector<int> v;
            std::string num;
            std::stringstream ss(line);
            while (std::getline(ss, num, ','))
            {
                v.push_back(std::stoi(num));
            }

            updates.push_back(v);
        }
    }

    int sum = 0;

    for (auto &v : updates)
    {
        bool ok = true;
        for (int i = 0; i < v.size() - 1; i++)
        {
            for (int j = i + 1; j < v.size(); j++)
            {
                if (!graph[v[i]][v[j]])
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
                break;
        }

        if (!ok)
        {
            std::sort(
                v.begin(),
                v.end(),
                [&graph](int a, int b)
                {
                    if (graph[a][b])
                        return true;
                    if (graph[b][a])
                        return false;
                    return false;
                });

            sum += v[int(v.size() / 2)];
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
