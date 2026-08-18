#pragma once

#include "MSWindow.h"
#include "GameContext.h"

class Game
{
public:
    static auto getInstance() -> Game&;

    auto start() -> void;
    auto updateState(State newState) -> void;


private:
    MSWindow window_;
    GameContext gameContext_;

    Game() = default;
};
