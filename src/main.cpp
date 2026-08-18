#include "Game.h"

auto main() -> int
{
    auto& game{Game::getInstance()};

    game.start();
}
