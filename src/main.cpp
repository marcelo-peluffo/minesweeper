#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>

inline constexpr auto num_rows{5};
inline constexpr auto num_cols{5};

enum class State : uint8_t { start, end, died };

constexpr auto tile_position(int id, int cols, int tile_width, int tile_height)
    -> sf::Vector2f {
  const auto row{id / cols};
  const auto col{id % cols};
  return {static_cast<float>(col * tile_width),
          static_cast<float>(row * tile_height)};
}

struct Tile {
  Tile() : id_(counter++) {
    shape_.setFillColor(sf::Color::Green);
    shape_.setPosition(tile_position(id_, num_cols, width, height));
  }

  inline static auto counter{0};
  static constexpr auto width{100};
  static constexpr auto height{100};
  sf::RectangleShape shape_;
  bool clicked_{};
  bool has_bomb_{};
  int neighboring_bombs_{};
  int id_{};
};

struct GameContext {
  std::vector<Tile> grid_;
  State state_{State::start};
  bool game_over_{};
};

auto render(sf::RenderWindow &window, const GameContext &context) -> void;
auto input(sf::RenderWindow &window, const GameContext &context) -> void;

int main() {

  GameContext game_context{};
  sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}),
                          "Minesweeper");

  while (!game_context.game_over_) {
    render(window, game_context);
    input(window, game_context);
  }

  window.close();

  return 0;
}

auto render(sf::RenderWindow &window, const GameContext &context) -> void {

  window.clear(sf::Color::White);
  std::ranges::for_each(context.grid_, [](auto &tile) {});
  window.display();
}

auto input(sf::RenderWindow &window, const GameContext &context) -> void {
  while (auto event{window.pollEvent()}) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
  }
}
