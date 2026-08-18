#include "Tile.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <optional>
#include "Game.h"
#include "Text.h"
#include "constants.h"

Tile::Tile() : textNeighboringBombs_(Text::font, Text::noBombs), hasBomb_(Tile::shouldHaveBomb()), id_(sCounter++)
{
    if (hasBomb_)
    {
        textNeighboringBombs_.setString("Bomb");
    }

    shape_.setFillColor(sf::Color::Green);
    shape_.setPosition(calculateTilePosition(constants::numCols));
    shape_.setSize(sf::Vector2f(sWidth - constants::spaceBetweenTiles, sHeight - constants::spaceBetweenTiles));

    textNeighboringBombs_.setPosition(shape_.getPosition());
}

auto Tile::processClick(::sf::Mouse::Button mouseButton) -> void
{
    using enum ::sf::Mouse::Button;

    if (mouseButton == Left)
    {
        shape_.setFillColor(constants::exposedTileColor);
        clicked_ = true;

        if (hasBomb_)
        {
            shape_.setFillColor(::sf::Color::Blue);
            Game::getInstance().updateState(State::end);
        }
    }
    // flag logic
    else if (mouseButton == Right)
    {
        flagged_ = !flagged_;

        if (flagged_)
        {
            flag_ = {};
            --Flag::count;
        }
        else
        {
            flag_.emplace(shape_.getPosition());
        }
    }
}

constexpr auto Tile::calculateTilePosition(int cols) const -> sf::Vector2f
{
    const auto row{id_ / cols};
    const auto col{id_ % cols};
    return {static_cast<float>(col * sWidth), static_cast<float>(row * sHeight)};
}
