#include "GameContext.h"
#include "MSWindow.h"

auto main() -> int
{
    MSWindow window;
    GameContext gameContext;

    while (window.isOpen())
    {
        while (const auto event{window.pollEvent()})
        {
            window.handleLastEvent(gameContext);
        }

        window.render(gameContext);
    }

    return 0;
}
