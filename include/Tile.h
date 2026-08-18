#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
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

    auto processClick(::sf::Mouse::Button mouseButton) -> void;

    inline static auto sCounter{0};
    static constexpr auto sWidth{100};
    static constexpr auto sHeight{100};
    sf::RectangleShape shape_;
    sf::Text textNeighboringBombs_;
    bool clicked_{};
    bool hasBomb_{};
    int neighboringBombs_{};
    int id_{};

   private:
    constexpr auto calculateTilePosition(int cols) const -> sf::Vector2f;
};
