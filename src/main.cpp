#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>

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
    shape_.setPosition(tile_position(id_, constants::num_cols, width, height));
    shape_.setSize(sf::Vector2f(width - constants::space_between_tiles,
                                height - constants::space_between_tiles));
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
  GameContext()
      : grid_(static_cast<size_t>(constants::num_rows * constants::num_cols)) {}
  std::vector<Tile> grid_;
  State state_{State::start};
  bool game_over_{};
};

auto render(sf::RenderWindow &window, GameContext &context) -> void;
auto input(sf::RenderWindow &window, GameContext &context) -> void;

int main() {
  GameContext game_context{};
  sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}),
                          "Minesweeper");

  while (window.isOpen()) {
    render(window, game_context);
    input(window, game_context);
  }

  window.close();

  return 0;
}

auto render(sf::RenderWindow &window, GameContext &context) -> void {

  window.clear(sf::Color::White);
  std::ranges::for_each(context.grid_,
                        [&window](auto &tile) { window.draw(tile.shape_); });
  window.display();
}

auto input(sf::RenderWindow &window, GameContext &context) -> void {
  while (auto event{window.pollEvent()}) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (const auto *mouse{
                   event->getIf<sf::Event::MouseButtonPressed>()}) {
      if (mouse->button == sf::Mouse::Button::Left) {
        std::ranges::for_each(context.grid_, [mouse](Tile &tile) {
          if (tile.shape_.getGlobalBounds().contains(
                  static_cast<sf::Vector2f>(mouse->position))) {
            tile.shape_.setFillColor(sf::Color::Red);
            tile.clicked_ = true;
          }
        });
      }
    }
  }
}
