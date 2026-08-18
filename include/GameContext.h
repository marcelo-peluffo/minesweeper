#pragma once
#include "State.h"
#include "Grid.h"

struct GameContext
{
    explicit GameContext();
    explicit GameContext(Grid grid, State state);

    Grid grid_;
    State state_{State::start};
};
