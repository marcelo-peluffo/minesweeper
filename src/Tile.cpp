#include "Tile.h"

Tile::Tile(int adjacent_bombs, bool has_bomb)
    : m_adjacent_bombs(adjacent_bombs), m_has_bomb(has_bomb) {}

Tile::Tile(int adjacent_bombs) : Tile(adjacent_bombs, false) {}

Tile::Tile(bool has_bomb) : Tile(0, has_bomb) {}

// getters

[[nodiscard]] auto Tile::get_adjacent_bombs() const -> int {
  return m_adjacent_bombs;
}

[[nodiscard]] auto Tile::has_bomb() const -> bool { return m_has_bomb; }

auto Tile::set_adjacent_bombs(int adjacent_bombs) -> void {
  m_adjacent_bombs = adjacent_bombs;
}

auto Tile::set_has_bomb(bool has_bomb) -> void { m_has_bomb = has_bomb; }
