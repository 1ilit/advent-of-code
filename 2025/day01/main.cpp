#include <iostream>
#include <fstream>
#include <string>

int part1()
{
    std::ifstream in("input.txt");

    std::string line;

    int dial = 50;
    int count = 0;

    while (in >> line)
    {
        char direction = line[0];

        int amount = std::stoi(line.substr(1));

        if (direction == 'L')
        {
            dial = (dial - amount) % 100;
            if (dial < 0)
                dial += 100;

            if (dial == 0)
            {
                count++;
            }
        }
        else
        {
            dial = (dial + amount) % 100;
            if (dial == 0)
            {
                count++;
            }
        }
    }

    return count;
}

int part2()
{
    std::ifstream in("input.txt");

    std::string line;

    int dial = 50;
    int count = 0;

    while (in >> line)
    {
        char direction = line[0];
        int amount = std::stoi(line.substr(1));

        count += amount / 100;
        int remaining = amount % 100;
        if (direction == 'L')
        {
            if (dial - remaining < 0)
            {
                count++;
            }

            dial = (dial - amount) % 100;
            if (dial < 0)
                dial += 100;
        }
        else
        {
            if (dial + remaining >= 100)
            {
                count++;
            }

            dial = (dial + amount) % 100;
        }
    }

    return count;
}

int main()
{
    std::cout << part1() << '\n';
    std::cout << part2() << '\n';

    return 0;
}