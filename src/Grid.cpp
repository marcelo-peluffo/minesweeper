#include "Grid.h"
#include "constants.h"
#include <algorithm>

Grid::Grid()
    : m_matrix(constants::number_of_tiles),
      m_active_bombs(
          static_cast<int>(std::ranges::count_if(m_matrix, &Tile::has_bomb))) {}

auto Grid::get_matrix() const -> const std::vector<Tile> & { return m_matrix; }
