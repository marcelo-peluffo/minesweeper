#pragma once

class Tile {
public:
  explicit Tile();
  explicit Tile(int adjacent_bombs, bool has_bomb);
  explicit Tile(int adjacent_bombs);
  explicit Tile(bool has_bomb);

  [[nodiscard]] auto get_adjacent_bombs() const -> int;
  [[nodiscard]] auto has_bomb() const -> bool;
  [[nodiscard]] auto has_flag() const -> bool;

  auto set_adjacent_bombs(int adjacent_bombs) -> void;
  auto set_has_bomb(bool has_bomb) -> void;
  auto set_has_flag(bool has_flag) -> void;

private:
  int m_adjacent_bombs;
  bool m_has_bomb;
  bool m_has_flag;

  auto random_should_have_bomb() -> bool;
};
