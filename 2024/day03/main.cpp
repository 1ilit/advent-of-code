#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cmath>

enum class State
{
    NONE = 0,
    IN_MUL,
    IN_NUM,
};

size_t cursor = 0;
std::string input;

bool next_characters_are(std::string str)
{
    size_t n = str.length();
    for (size_t i = cursor, j = 0; i < cursor + n, j < n; i++, j++)
    {
        if (input[i] != str[j])
        {
            return false;
        }
    }

    return true;
}

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    cursor = 0;
    input = "";

    std::string line;
    while (std::getline(in, line))
        input += line;

    long long sum = 0;
    std::vector<std::pair<int, int>> tokens;

    State state = State::NONE;
    std::string current_token = "";
    std::pair<int, int> current_pair = {};

    for (;;)
    {
        if (cursor >= input.size())
            break;

        char c = input[cursor];

        switch (state)
        {
        case State::NONE:
            if (c == 'm')
            {
                state = State::IN_MUL;
                cursor--;
                break;
            }
            break;
        case State::IN_MUL:
            if (next_characters_are("mul("))
            {
                state = State::IN_NUM;
                cursor += 3;
                break;
            }
        case State::IN_NUM:
            if (std::isdigit(c))
            {
                current_token += c;
                break;
            }
            if (c == ',')
            {
                current_pair.first = std::stoi(current_token);
                current_token = "";
                break;
            }
            if (c == ')')
            {
                current_pair.second = std::stoi(current_token);
                tokens.push_back(current_pair);

                current_pair = {};
                current_token = "";
            }
            state = State::NONE;
            current_token = "";
            current_pair = {};
            break;
        default:
            break;
        }
        cursor++;
    }

    for (auto const &x : tokens)
    {
        sum += x.first * x.second;
    }

    out << sum;
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    cursor = 0;
    input = "";

    std::string line;
    while (std::getline(in, line))
        input += line;

    long long sum = 0;
    std::vector<std::pair<int, int>> tokens;

    State state = State::NONE;
    std::string current_token = "";
    std::pair<int, int> current_pair = {};

    bool halt = false;

    for (;;)
    {
        if (cursor >= input.size())
            break;

        if (next_characters_are("do()"))
        {
            halt = false;
            cursor += 4;
            continue;
        }

        if (next_characters_are("don't()"))
        {
            halt = true;
            cursor += 7;
            continue;
        }

        char c = input[cursor];

        switch (state)
        {
        case State::NONE:
            if (c == 'm')
            {
                state = State::IN_MUL;
                cursor--;
                break;
            }
            break;
        case State::IN_MUL:
            if (next_characters_are("mul("))
            {
                state = State::IN_NUM;
                cursor += 3;
                break;
            }
        case State::IN_NUM:
            if (std::isdigit(c))
            {
                current_token += c;
                break;
            }
            if (c == ',')
            {
                current_pair.first = std::stoi(current_token);
                current_token = "";
                break;
            }
            if (c == ')')
            {
                current_pair.second = std::stoi(current_token);
                if (!halt)
                    tokens.push_back(current_pair);

                current_pair = {};
                current_token = "";
            }
            state = State::NONE;
            current_token = "";
            current_pair = {};
            break;
        default:
            break;
        }
        cursor++;
    }

    for (auto const &x : tokens)
    {
        sum += x.first * x.second;
    }

    out << sum;
}

int main()
{
    solve1();
    solve2();
    return 0;
}
