#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>

struct Flag
{
   public:
    Flag();
    Flag(const ::sf::Vector2f& pos);

    [[nodiscard]] auto getSprite() const -> const ::sf::Sprite&;

    static constexpr std::string_view path{"assets/flag.png"};
    inline static auto count{0};
    ::sf::Texture texture_;
    ::sf::Sprite sprite_;
};
