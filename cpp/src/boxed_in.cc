#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "csv.h"
#include "stoi.h"


struct Tile {
    Tile(int lx, int ly, int ux, int uy) : lx(lx), ly(ly), ux(ux), uy(uy) {}

    bool overlaps(Tile const &other) {
        return lx <= (other.ux - 1) &&
               other.lx <= (ux - 1) &&
               ly <= (other.uy - 1) &&
               other.ly <= (uy - 1);
    }

    void place(std::vector<std::vector<int>> &tiling) const {
        for (int y = ly; y < uy; ++y) {
            for (int x = lx; x < ux; ++x)
                tiling[y][x] = 1;
        }
    }

    int lx, ly, ux, uy;

    bool valid = false;
};


int main()
{
    auto csv = read_csv(std::cin, {"lx", "ly", "ux", "uy"});

    std::vector<Tile> tiles;
    int x_max = 0, y_max = 0;

    for (auto const &row : csv) {
        int lx = stoi_assert(row[0]);
        int ly = stoi_assert(row[1]);
        int ux = stoi_assert(row[2]);
        int uy = stoi_assert(row[3]);

        Tile tile(lx, ly, ux, uy);

        for (auto &previous_tile : tiles) {
            if (tile.overlaps(previous_tile)) {
                if (!tile.valid)
                    tile.valid = true;

                if (!previous_tile.valid)
                    previous_tile.valid = true;
            }
        }

        x_max = std::max(x_max, lx + ux);
        y_max = std::max(y_max, ly + uy);

        tiles.push_back(tile);
    }

    std::vector<std::vector<int>> tiling(y_max + 1);
    for (auto i = 0u; i < tiling.size(); ++i)
        tiling[i] = std::vector<int>(x_max + 1);

    for (auto const &tile : tiles) {
        if (tile.valid)
            tile.place(tiling);
    }

    std::size_t res = 0;
    for (auto const &row : tiling)
        res += std::count(row.begin(), row.end(), 1);

    std::cout << res << '\n';

    exit(EXIT_SUCCESS);
}
