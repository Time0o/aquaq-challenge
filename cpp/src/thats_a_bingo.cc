#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "stoi.h"


static int const board[][5] = {
    {6,  17, 34, 50, 68},
    {10, 21, 45, 53, 66},
    {5,  25, 36, 52, 69},
    {14, 30, 33, 54, 63},
    {15, 23, 41, 51, 62}
};

static int const board_dim = static_cast<int>(sizeof(board) / sizeof(board[0]));


static bool bingo(std::vector<std::vector<int>> const &game,
                  int x0, int x1, int y0, int y1)
{
    auto inc = [](int c, int c0, int c1) {
        if (c0 == c1)
            return c;

        return c + ((c0 < c1) ? 1 : -1);
    };

    bool is_bingo = true;

    int x = x0, y = y0;
    while ((x <= x0 || x <= x1) && (y <= y0 || y <= y1)) {
        if (game[y][x] == 0) {
            is_bingo = false;
            break;
        }

        x = inc(x, x0, x1);
        y = inc(y, y0, y1);
    }

    return is_bingo;
}


static bool game_over(
    std::vector<std::vector<int>> const &game, int last_x, int last_y)
{
    if (bingo(game, 0, board_dim - 1, last_y, last_y) ||
        bingo(game, last_x, last_x, 0, board_dim - 1)) {

        return true;
    }

    if (last_x == last_y)
        return bingo(game, 0, board_dim - 1, 0, board_dim -1);
    else if (last_x == board_dim - last_y - 1)
        return bingo(game, board_dim - 1, 0, 0, board_dim -1);

    return false;
}


static int turns_until_bingo(std::vector<int> numbers)
{
    static bool first_call = true;
    static std::map<int, std::pair<int, int>> indices;

    if (first_call) {
        for (auto y = 0u; y < board_dim; ++y) {
            for (auto x = 0u; x < board_dim; ++x)
                indices[board[y][x]] = {x, y};
        }

        first_call = false;
    }

    std::vector<std::vector<int>> game(board_dim, std::vector<int>(board_dim));

    int turns = 0u;
    for (int n : numbers) {
        ++turns;

        if (indices.find(n) == indices.end())
            continue;

        auto ind = indices[n];

        game[ind.second][ind.first] = 1;

        if (game_over(game, ind.first, ind.second))
            break;
    }

    return turns;
}


int main()
{
    int res = 0;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<int> numbers;

        std::string::size_type pos = 0u, next_pos;
        while ((next_pos = line.find(' ', pos)) != std::string::npos) {
            numbers.push_back(stoi_assert(line.substr(pos, next_pos - pos)));
            pos = next_pos + 1;
        }

        res += turns_until_bingo(numbers);
    }

    if (std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    std::cout << res << '\n';

    exit(EXIT_SUCCESS);
}
