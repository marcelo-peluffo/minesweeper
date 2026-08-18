#include "Grid.h"
#include <vector>

Grid::Grid(std::size_t numberOfTiles) : underlyingGrid_(numberOfTiles) {}

auto Grid::findNeighboringBombs(const Tile& tile) -> int
{
    const auto tileId{tile.id_};
    const auto row{tileId / constants::numCols};
    const auto col{tileId % constants::numCols};
    auto count{0};

    for (int i{std::max(0, row - 1)}; i <= std::min(constants::numRows - 1, row + 1); ++i)
    {
        for (int j{std::max(0, col - 1)}; j <= std::min(constants::numCols - 1, col + 1); ++j)
        {
            if (i == row && j == col)
            {
                continue;
            }

            if (underlyingGrid_[(i * constants::numCols) + j].hasBomb_)
            {
                ++count;
            }
        }
    }

    return count;
}

auto Grid::clickedTile(::sf::Vector2f mousePos) -> Tile*
{
    for (auto& tile : underlyingGrid_)
    {
        if (tile.shape_.getGlobalBounds().contains(mousePos))
        {
            return std::addressof(tile);
        }
    }

    return nullptr;
}

auto Grid::getUnderlyingGrid() -> std::vector<Tile>&
{
    return underlyingGrid_;
}

auto Grid::getUnderlyingGrid() const -> const std::vector<Tile>&
{
    return underlyingGrid_;
}
