#include "Tile.h"
#include <SFML/System/Vector2.hpp>
#include "Text.h"

Tile::Tile() : textNeighboringBombs_(Text::font, Text::noBombs), hasBomb_(Tile::shouldHaveBomb()), id_(counter++)
{
    shape_.setFillColor(sf::Color::Green);
    shape_.setPosition(calculateTilePosition(id_, constants::numCols, width, height));
    shape_.setSize(sf::Vector2f(width - constants::spaceBetweenTiles, height - constants::spaceBetweenTiles));

    textNeighboringBombs_.setPosition(shape_.getPosition());
}

constexpr auto Tile::calculateTilePosition(int tileId, int cols, int tileWidth, int tileHeight) -> sf::Vector2f
{
    const auto row{tileId / cols};
    const auto col{tileId % cols};
    return {static_cast<float>(col * tileWidth), static_cast<float>(row * tileHeight)};
}
