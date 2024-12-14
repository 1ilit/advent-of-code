#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    std::string input;
    in >> input;

    long long id = 0;
    int dot_count = 0;

    std::vector<int> v;

    for (size_t i = 0; i < input.length(); i++)
    {
        for (int j = 0; j < input[i] - '0'; j++)
        {
            if (i % 2 == 1)
            {
                v.push_back(-1);
                dot_count++;
            }
            else
            {
                v.push_back(id);
            }
        }

        if (i % 2 == 0)
            id++;
    }

    size_t i = 0, j = v.size() - 1;
    while (i < v.size() - dot_count && j >= 0)
    {
        if (v[i] != -1)
        {
            i++;
            continue;
        }

        if (v[j] == -1)
        {
            j--;
            continue;
        }

        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
        j--;
        i++;
    }

    long long checksum = 0;

    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] != -1)
            checksum += i * v[i];
        else
            break;
    }

    out << checksum;
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    std::string input;
    in >> input;

    long long id = 0;
    int dot_count = 0;

    std::vector<std::pair<int, int>> v;

    for (size_t i = 0; i < input.length(); i++)
    {
        int num = input[i] - '0';
        if (i % 2 == 0)
        {
            v.push_back({id, num});
            id++;
        }
        else
        {
            v.push_back({-1, num});
            dot_count += 1;
        }
    }

    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i].first != -1)
        {
            for (int j = 0; j < i; j++)
            {
                if (v[j].first == -1 && v[j].second >= v[i].second)
                {
                    v.emplace(v.begin() + j, v[i]);
                    v[j + 1].second -= v[i + 1].second;
                    v[i + 1].first = -1;
                    break;
                }
            }
        }
    }

    std::vector<int> res;

    for (const auto &x : v)
    {
        for (int k = 0; k < x.second; k++)
        {
            if (x.first == -1)
                res.push_back(0);
            else
                res.push_back(x.first);
        }
    }

    long long checksum = 0;
    for (size_t i = 0; i < res.size(); i++)
    {
        if (res[i] != -1)
            checksum += i * res[i];
        else
            break;
    }

    out << checksum;
}

int main()
{
    solve1();
    solve2();
    return 0;
}