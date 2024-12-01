#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    std::vector<int> list1;
    std::vector<int> list2;

    int x1, x2;
    while (in >> x1 >> x2)
    {
        list1.push_back(x1);
        list2.push_back(x2);
    }

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    long long sum = 0;

    for (size_t i = 0; i < list1.size(); i++)
        sum += std::abs(list1[i] - list2[i]);

    out << sum;
}

void solve2() {
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    std::map<int, int> map;
    std::vector<int> list1;

    int x1, x2;
    while (in >> x1 >> x2) {
        list1.push_back(x1);
        map[x2]++;
    }

    long long sum = 0;
    for (int x : list1) {
        if (map[x]) {
            sum += x * map[x];
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