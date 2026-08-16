#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "constants.h"

struct Tile
{
    Tile();

    [[nodiscard]] static auto shouldHaveBomb() -> bool
    {
        static std::random_device rand;
        static std::mt19937 gen(rand());
        static std::uniform_int_distribution<int> distrib(1, 100);

        const auto randomNum{distrib(gen)};
        return randomNum <= constants::chanceForBomb;
    }

    inline static auto counter{0};
    static constexpr auto width{100};
    static constexpr auto height{100};
    sf::RectangleShape shape_;
    sf::Text textNeighboringBombs_;
    bool clicked_{};
    bool hasBomb_{};
    int neighboringBombs_{};
    int id_{};

   private:
    constexpr auto calculateTilePosition(int tileId, int cols, int tileWidth, int tileHeight) -> sf::Vector2f;
};
