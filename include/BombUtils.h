#pragma once
#include "Tile.h"
#include <algorithm>

namespace BombUtils
{
auto findNeighboringBombs(const std::vector<Tile>& grid, int tile_id) -> int
{
    const auto row{tile_id / constants::numCols};
    const auto col{tile_id % constants::numCols};
    auto count{0};

    for (int i{std::max(0, row - 1)}; i <= std::min(constants::numRows - 1, row + 1); ++i)
    {
        for (int j{std::max(0, col - 1)}; j <= std::min(constants::numCols - 1, col + 1); ++j)
        {
            if (i == row && j == col)
            {
                continue;
            }

            if (grid[(i * constants::numCols) + j].hasBomb_)
            {
                ++count;
            }
        }
    }

    return count;
}
}  // namespace BombUtils
