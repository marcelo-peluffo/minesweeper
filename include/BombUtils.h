#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <optional>
#include "Tile.h"

// should maybe move this to .cpp impl
namespace BombUtils
{
inline auto findNeighboringBombs(const std::vector<Tile>& grid, int tile_id) -> int
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

inline auto clickedTile(std::vector<Tile>& grid, const ::sf::Vector2f mousePos) -> std::optional<Tile>
{
    for (const auto& tile : grid)
    {
        if (tile.shape_.getGlobalBounds().contains(mousePos))
        {
            return tile;
        }
    }

    return std::nullopt;
}

// only setting state, not actually doing something with the new state
inline auto handleTileClick(Tile& chosenTile, ::sf::Mouse::Button mouseButton) -> void
{
    using enum ::sf::Mouse::Button;

    if (mouseButton == Left)
    {
        chosenTile.shape_.setFillColor(::sf::Color::Red);
        chosenTile.clicked_ = true;
    }
    // flag logic
    else if (mouseButton == Right)
    {
    }
}

}  // namespace BombUtils
