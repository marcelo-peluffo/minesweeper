#pragma once
#include "State.h"
#include "Tile.h"
#include <vector>

struct GameContext
{
    explicit GameContext();
    explicit GameContext(std::vector<Tile>& grid, State state);

    std::vector<Tile> grid_;
    State state_{State::start};
};
