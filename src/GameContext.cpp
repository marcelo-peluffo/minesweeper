#include "GameContext.h"
#include "constants.h"

GameContext::GameContext() : grid_(static_cast<std::size_t>(constants::numberOfTiles))
{
    for (auto& tile : grid_.getUnderlyingGrid())
    {
        tile.neighboringBombs_ = grid_.findNeighboringBombs(tile);
        if (!tile.hasBomb_)
        {
            tile.textNeighboringBombs_.setString(std::to_string(tile.neighboringBombs_));
        }
    }
}

GameContext::GameContext(Grid grid, State state) : grid_(std::move(grid)), state_(state) {}
