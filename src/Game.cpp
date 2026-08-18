#include "Game.h"
#include "State.h"

auto Game::getInstance() -> Game&
{
    static Game instance;
    return instance;
}

auto Game::start() -> void
{
    while (gameContext_.state_ != State::end)
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
