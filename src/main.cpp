#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <iostream>
#include "Text.h"
#include "Tile.h"
#include "constants.h"
#include "State.h"
#include "GameContext.h"

auto render(sf::RenderWindow& window, GameContext& context) -> void;
auto input(sf::RenderWindow& window, GameContext& context) -> void;

int main()
{
    GameContext gameContext{};
    sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}), Text::gameTitle);

    while (gameContext.state_ != State::end)
    {
        render(window, gameContext);
        input(window, gameContext);
    }

    window.close();

    return 0;
}

auto render(sf::RenderWindow& window, GameContext& context) -> void
{
    window.clear(sf::Color::White);
    std::ranges::for_each(context.grid_,
                          [&window](auto& tile)
                          {
                              window.draw(tile.shape_);
                              if (tile.clicked_)
                              {
                                  window.draw(tile.textNeighboringBombs_);
                              }
                          });
    window.display();
}

// apply pattern of returning game context instead of just modifying reference
// (functional programming)
auto handle_clicked_tile(const Tile& tile, GameContext& context) -> GameContext
{
    if (tile.hasBomb_)
    {
        std::cout << "You have clicked a bomb!\n";
        return GameContext{context.grid_, State::end};
    }

    // if no bomb, show the surrounding free spaces

    return context;
}

// ugly formatting also i dont like context& everywhere

auto input(sf::RenderWindow& window, GameContext& context) -> void
{
    while (auto event{window.pollEvent()})
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* mouse{event->getIf<sf::Event::MouseButtonPressed>()})
        {
            if (mouse->button == sf::Mouse::Button::Left)
            {
                std::ranges::for_each(
                    context.grid_,
                    [mouse, &context](Tile& tile)
                    {
                        if (tile.shape_.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse->position)))
                        {
                            tile.shape_.setFillColor(sf::Color::Red);
                            tile.clicked_ = true;
                            context = handle_clicked_tile(tile, context);
                        }
                    });
            }
        }
    }
}
