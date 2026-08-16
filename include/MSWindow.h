#pragma once
#include <SFML/Graphics.hpp>
#include "GameContext.h"

class MSWindow
{
   public:
    MSWindow();

    auto render(const GameContext& context) -> void;
    auto pollEvent() -> const std::optional<sf::Event>&;
    auto handleLastEvent(GameContext& context) -> void;

   private:
    sf::RenderWindow underlyingWindow_;
    std::optional<sf::Event> lastEvent_;
};
