#include "GameContext.h"
#include "BombUtils.h"
#include "constants.h"

GameContext::GameContext() : grid_(static_cast<std::size_t>(constants::numberOfTiles))
{
    for (auto& tile : grid_)
    {
        tile.neighboringBombs_ = BombUtils::findNeighboringBombs(grid_, tile.id_);
        tile.textNeighboringBombs_.setString(std::to_string(tile.neighboringBombs_));
    }
}

GameContext::GameContext(std::vector<Tile>& grid, State state) : grid_(std::move(grid)), state_(state) {}
