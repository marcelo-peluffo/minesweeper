#pragma once

#include <SFML/Graphics/Color.hpp>
namespace constants
{
inline constexpr auto width{1920};
inline constexpr auto height{1080};
inline constexpr auto exitCodeSuccess{0};
inline constexpr auto percentChanceForBomb{25};
inline constexpr auto spaceBetweenTiles{10};
inline constexpr auto numRows{5};
inline constexpr auto numCols{5};
inline constexpr auto numberOfTiles{numRows * numCols};
inline constexpr auto chanceForBomb{15};
inline constexpr auto exposedTileColor{::sf::Color::Red};
}  // namespace constants
