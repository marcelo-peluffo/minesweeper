
class Tile {
public:
  explicit Tile() = default;
  explicit Tile(int adjacent_bombs, bool has_bomb);
  explicit Tile(int adjacent_bombs);
  explicit Tile(bool has_bomb);

  [[nodiscard]] auto get_adjacent_bombs() const -> int;
  [[nodiscard]] auto has_bomb() const -> bool;

  auto set_adjacent_bombs(int adjacent_bombs) -> void;
  auto set_has_bomb(bool has_bomb) -> void;

private:
  int m_adjacent_bombs;
  bool m_has_bomb;
};
