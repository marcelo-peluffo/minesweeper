#include "Game.h"

auto Game::getInstance() -> Game&
{
    static Game instance;
    return instance;
}

auto Game::start() -> void
{
    while (window_.isOpen())
    {
        while (const auto event{window_.pollEvent()})
        {
            window_.handleLastEvent(gameContext_);
        }

        window_.render(gameContext_);
    }
}

auto Game::updateState(State newState) -> void
{
    gameContext_.state_ = newState;
}
