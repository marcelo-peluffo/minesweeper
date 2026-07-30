#include "Tile.h"
#include <vector>

class Grid {
public:
  Grid();
  [[nodiscard]] auto get_matrix() const -> const std::vector<Tile> &;
  [[nodiscard]] auto get_neighbors_of(const Tile &tile) -> std::vector<Tile>;

private:
  std::vector<Tile> m_matrix;
  int m_active_bombs;
};
