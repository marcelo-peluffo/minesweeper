#include "Tile.h"
#include "constants.h"
#include <random>

Tile::Tile() : m_has_bomb(random_should_have_bomb()) {}

// getters

[[nodiscard]] auto Tile::get_adjacent_bombs() const -> int {
  return m_adjacent_bombs;
}

[[nodiscard]] auto Tile::has_bomb() const -> bool { return m_has_bomb; }

[[nodiscard]] auto Tile::has_flag() const -> bool { return m_has_flag; }

// setters

auto Tile::set_adjacent_bombs(int adjacent_bombs) -> void {
  m_adjacent_bombs = adjacent_bombs;
}

auto Tile::set_has_bomb(bool has_bomb) -> void { m_has_bomb = has_bomb; }

auto Tile::set_has_flag(bool has_flag) -> void { m_has_flag = has_flag; }

auto Tile::random_should_have_bomb() -> bool {
  constexpr auto bottom_range{1};
  constexpr auto top_range{100};

  std::random_device rand_d;
  std::mt19937 gen(rand_d());
  std::uniform_int_distribution<int> distrib(bottom_range, top_range);

  return distrib(gen) <= constants::percent_chance_for_bomb;
}
