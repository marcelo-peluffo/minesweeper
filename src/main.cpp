#include "GameContext.h"
#include "MSWindow.h"

auto main() -> int
{
    MSWindow window;
    GameContext gameContext;

    while (window.isOpen())
    {
        window.render(gameContext);
        window.pollEvent();
        window.handleLastEvent(gameContext);
    }

    return 0;
}
