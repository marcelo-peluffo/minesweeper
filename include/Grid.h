#pragma once

#include <vector>
#include "Tile.h"

class Grid
{
   public:
    Grid(std::size_t numberOfTiles);
    auto findNeighboringBombs(const Tile& tile) -> int;
    auto clickedTile(::sf::Vector2f mousePos) -> Tile*;

    [[nodiscard]] auto getUnderlyingGrid() -> std::vector<Tile>&;
    [[nodiscard]] auto getUnderlyingGrid() const -> const std::vector<Tile>&;

   private:
    std::vector<Tile> underlyingGrid_;
};
