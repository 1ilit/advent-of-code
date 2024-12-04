#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cmath>

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(in, line))
    {
        grid.push_back(line);
    }

    int counter = 0;
    size_t n = grid.size();
    size_t m = grid[0].length();

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (grid[i][j] == 'X')
            {
                // horizontal
                if (j + 3 < m && grid[i][j + 1] == 'M' && grid[i][j + 2] == 'A' && grid[i][j + 3] == 'S')
                {
                    counter++;
                }

                if (j >= 3 && grid[i][j - 1] == 'M' && grid[i][j - 2] == 'A' && grid[i][j - 3] == 'S')
                {
                    counter++;
                }

                // vertical
                if (i + 3 < n && grid[i + 1][j] == 'M' && grid[i + 2][j] == 'A' && grid[i + 3][j] == 'S')
                {
                    counter++;
                }

                if (i >= 3 && grid[i - 1][j] == 'M' && grid[i - 2][j] == 'A' && grid[i - 3][j] == 'S')
                {
                    counter++;
                }

                // diagonal
                if (i >= 3 && j >= 3 && grid[i - 1][j - 1] == 'M' && grid[i - 2][j - 2] == 'A' && grid[i - 3][j - 3] == 'S')
                {
                    counter++;
                }

                if (i >= 3 && j + 3 < m && grid[i - 1][j + 1] == 'M' && grid[i - 2][j + 2] == 'A' && grid[i - 3][j + 3] == 'S')
                {
                    counter++;
                }

                if (i + 3 < n && j >= 3 && grid[i + 1][j - 1] == 'M' && grid[i + 2][j - 2] == 'A' && grid[i + 3][j - 3] == 'S')
                {
                    counter++;
                }

                if (i + 3 < n && j + 3 < m && grid[i + 1][j + 1] == 'M' && grid[i + 2][j + 2] == 'A' && grid[i + 3][j + 3] == 'S')
                {
                    counter++;
                }
            }
        }
    }

    out << counter;
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(in, line))
    {
        grid.push_back(line);
    }

    int counter = 0;
    size_t n = grid.size();
    size_t m = grid[0].length();

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (grid[i][j] == 'A')
            {
                bool d1 =
                    (i >= 1 && j >= 1 && grid[i - 1][j - 1] == 'S' && i + 1 < n && j + 1 < m && grid[i + 1][j + 1] == 'M') ||
                    (i >= 1 && j >= 1 && grid[i - 1][j - 1] == 'M' && i + 1 < n && j + 1 < m && grid[i + 1][j + 1] == 'S');
                bool d2 =
                    (i >= 1 && j + 1 < m && grid[i - 1][j + 1] == 'S' && i + 1 < n && j >= 1 && grid[i + 1][j - 1] == 'M') ||
                    (i >= 1 && j + 1 < m && grid[i - 1][j + 1] == 'M' && i + 1 < n && j >= 1 && grid[i + 1][j - 1] == 'S');

                if (d1 && d2)
                    counter++;
            }
        }
    }

    out << counter;
}

int main()
{
    solve1();
    solve2();
    return 0;
}
