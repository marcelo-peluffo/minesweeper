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
#include <string>
#include "Text.h"
#include "Tile.h"
#include "constants.h"
#include "State.h"

auto findNeighboringBombs(const std::vector<Tile>& grid, int tile_id) -> int;

struct GameContext
{
    GameContext() : grid_(static_cast<size_t>(constants::numRows * constants::numCols))
    {
        std::ranges::for_each(grid_.begin(), grid_.end(),
                              [this](auto& tile)
                              {
                                  tile.neighboringBombs_ = findNeighboringBombs(grid_, tile.id_);
                                  tile.textNeighboringBombs_.setString(std::to_string(tile.neighboringBombs_));
                              });
    }

    GameContext(std::vector<Tile>& grid, State state) : grid_(std::move(grid)), state_(state) {}

    std::vector<Tile> grid_;
    State state_{State::start};
};

auto render(sf::RenderWindow& window, GameContext& context) -> void;
auto input(sf::RenderWindow& window, GameContext& context) -> void;

int main()
{
    GameContext game_context{};
    sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}), Text::gameTitle);

    while (game_context.state_ != State::end)
    {
        render(window, game_context);
        input(window, game_context);
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

auto findNeighboringBombs(const std::vector<Tile>& grid, int tile_id) -> int
{
    const auto row{tile_id / constants::numCols};
    const auto col{tile_id % constants::numCols};
    auto count{0};

    for (int i{std::max(0, row - 1)}; i <= std::min(constants::numRows - 1, row + 1); ++i)
    {
        for (int j{std::max(0, col - 1)}; j <= std::min(constants::numCols - 1, col + 1); ++j)
        {
            if (i == row && j == col)
            {
                continue;
            }

            if (grid[(i * constants::numCols) + j].hasBomb_)
            {
                ++count;
            }
        }
    }

    return count;
}
