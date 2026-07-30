#include "Tile.h"
#include <vector>

class Grid {
public:
  Grid();
  [[nodiscard]] auto get_matrix() const -> const std::vector<Tile> &;

private:
  std::vector<Tile> m_matrix;
};
