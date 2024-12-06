#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>

enum class Direction
{
    UP = 'U',
    DOWN = 'D',
    LEFT = 'L',
    RIGHT = 'R'
};

const std::map<Direction, std::pair<int, int>> directions = {
    {Direction::RIGHT, {0, 1}}, {Direction::DOWN, {1, 0}}, {Direction::LEFT, {0, -1}}, {Direction::UP, {-1, 0}}};

void solve1()
{
    std::ifstream in("input.txt");
    std::ofstream out("output1.txt");

    std::set<std::pair<int, int>> visited;
    std::pair<int, int> starting_pos = {};
    Direction starting_dir;
    std::vector<std::string> grid;

    std::string line;
    while (std::getline(in, line))
    {
        grid.push_back(line);

        for (size_t j = 0; j < line.length(); j++)
        {
            switch (line[j])
            {
            case 'v':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::DOWN;
                break;

            case '^':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::UP;
                break;

            case '>':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::RIGHT;
                break;

            case '<':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::LEFT;
                break;

            default:
                break;
            }
        }
    }

    int i = starting_pos.first;
    int j = starting_pos.second;
    Direction curr_dir = starting_dir;

    while (true)
    {
        visited.insert({i, j});
        int next_i = i + directions.at(curr_dir).first;
        int next_j = j + directions.at(curr_dir).second;

        if (next_i >= grid.size() || next_j >= grid[0].length() || next_i < 0 || next_j < 0)
            break;

        if (grid[next_i][next_j] == '#')
        {
            switch (curr_dir)
            {
            case Direction::UP:
                curr_dir = Direction::RIGHT;
                break;

            case Direction::RIGHT:
                curr_dir = Direction::DOWN;
                break;

            case Direction::DOWN:
                curr_dir = Direction::LEFT;
                break;

            case Direction::LEFT:
                curr_dir = Direction::UP;
                break;

            default:
                break;
            }
        }
        else
        {
            i = next_i;
            j = next_j;
        }
    }

    out << visited.size();
}

bool hasLoop(std::pair<int, int> start_pos, Direction start_dir, std::vector<std::string> &grid)
{
    std::set<std::tuple<int, int, Direction>> visited;

    int i = start_pos.first;
    int j = start_pos.second;
    Direction curr_dir = start_dir;

    while (true)
    {
        auto state = std::make_tuple(i, j, curr_dir);

        if (visited.find(state) != visited.end())
            return true;

        visited.insert(state);

        int next_i = i + directions.at(curr_dir).first;
        int next_j = j + directions.at(curr_dir).second;

        if (next_i < 0 || next_j < 0 || next_i >= grid.size() || next_j >= grid[0].size())
            return false;

        if (grid[next_i][next_j] == '#')
        {
            switch (curr_dir)
            {
            case Direction::UP:
                curr_dir = Direction::RIGHT;
                break;
            case Direction::RIGHT:
                curr_dir = Direction::DOWN;
                break;
            case Direction::DOWN:
                curr_dir = Direction::LEFT;
                break;
            case Direction::LEFT:
                curr_dir = Direction::UP;
                break;
            }
        }
        else
        {
            i = next_i;
            j = next_j;
        }
    }
    return false;
}

void solve2()
{
    std::ifstream in("input.txt");
    std::ofstream out("output2.txt");

    std::pair<int, int> starting_pos = {};
    Direction starting_dir;
    std::vector<std::string> grid;

    std::string line;
    while (std::getline(in, line))
    {
        grid.push_back(line);

        for (size_t j = 0; j < line.length(); j++)
        {
            switch (line[j])
            {
            case 'v':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::DOWN;
                break;

            case '^':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::UP;
                break;

            case '>':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::RIGHT;
                break;

            case '<':
                starting_pos.first = grid.size() - 1;
                starting_pos.second = j;
                starting_dir = Direction::LEFT;
                break;

            default:
                break;
            }
        }
    }

    int answer = 0;

    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[i].length(); j++)
        {
            if (i == starting_pos.first && j == starting_pos.second)
                continue;

            if (grid[i][j] != '.')
                continue;

            char prev = grid[i][j];
            grid[i][j] = '#';

            if (hasLoop(starting_pos, starting_dir, grid))
                answer++;

            grid[i][j] = prev;
        }
    }

    out << answer;
}

int main()
{
    solve1();
    solve2();
    return 0;
}