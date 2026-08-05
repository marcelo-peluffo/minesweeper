#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

struct Tile {
  bool has_bomb_{};
  int neighboring_bombs_{};
};

struct GameState {
  std::vector<Tile> grid_;
  bool game_over_;
};

auto render(sf::RenderWindow &window, const GameState &state) -> void;

int main() {
  GameState game_state{};
  sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}),
                          "Minesweeper");

  while (!game_state.game_over_) {
    render(window, game_state);
  }

  window.close();

  return 0;
}

auto render(sf::RenderWindow &window, const GameState &state) -> void {

  window.clear(sf::Color::White);
  // draw here

  window.display();
}
