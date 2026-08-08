#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <iostream>
#include <random>
#include "constants.h"

enum class State : uint8_t { start, end, died };

constexpr auto tile_position(int id, int cols, int tile_width, int tile_height) -> sf::Vector2f {
    const auto row{id / cols};
    const auto col{id % cols};
    return {static_cast<float>(col * tile_width), static_cast<float>(row * tile_height)};
}

struct Tile {
    Tile() : id_(counter++) {
        shape_.setFillColor(sf::Color::Green);
        shape_.setPosition(tile_position(id_, constants::num_cols, width, height));
        shape_.setSize(sf::Vector2f(width - constants::space_between_tiles, height - constants::space_between_tiles));
    }

    static auto should_have_bomb() -> bool {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> distrib(1, 100);

        const auto random_num{distrib(gen)};
        return random_num <= 15;  // 15% chance of a tile generating a bomb
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

auto find_neighboring_bombs(const std::vector<Tile>& grid, int tile_id) -> int;

struct GameContext {
    GameContext() : grid_(static_cast<size_t>(constants::num_rows * constants::num_cols)) {
        std::ranges::for_each(grid_.begin(), grid_.end(), [this](auto& tile) {
            tile.neighboring_bombs_ = find_neighboring_bombs(grid_, tile.id_);
        });
    }

    GameContext(std::vector<Tile>& grid, State state) : grid_(std::move(grid)), state_(state) {}

    std::vector<Tile> grid_;
    State state_{State::start};
};

auto render(sf::RenderWindow& window, GameContext& context) -> void;
auto input(sf::RenderWindow& window, GameContext& context) -> void;

int main() {
    GameContext game_context{};
    game_context.grid_[12].has_bomb_ = true;  // test
    sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}), "Minesweeper");

    while (game_context.state_ != State::end) {
        render(window, game_context);
        input(window, game_context);
    }

    window.close();

    return 0;
}

auto render(sf::RenderWindow& window, GameContext& context) -> void {
    window.clear(sf::Color::White);
    std::ranges::for_each(context.grid_, [&window](auto& tile) { window.draw(tile.shape_); });
    window.display();
}

// apply pattern of returning game context instead of just modifying reference
// (functional programming)
auto handle_clicked_tile(const Tile& tile, GameContext& context) -> GameContext {
    if (tile.has_bomb_) {
        std::cout << "You have clicked a bomb!\n";
        return GameContext{context.grid_, State::end};
    }

    // if no bomb, show the surrounding free spaces

    return context;
}

// ugly formatting also i dont like context& everywhere

auto input(sf::RenderWindow& window, GameContext& context) -> void {
    while (auto event{window.pollEvent()}) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* mouse{event->getIf<sf::Event::MouseButtonPressed>()}) {
            if (mouse->button == sf::Mouse::Button::Left) {
                std::ranges::for_each(context.grid_, [mouse, &context](Tile& tile) {
                    if (tile.shape_.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse->position))) {
                        tile.shape_.setFillColor(sf::Color::Red);
                        tile.clicked_ = true;
                        context = handle_clicked_tile(tile, context);
                    }
                });
            }
        }
    }
}

auto find_neighboring_bombs(const std::vector<Tile>& grid, int tile_id) -> int {
    const auto row{tile_id / constants::num_cols};
    const auto col{tile_id % constants::num_cols};
    auto count{0};

    for (int i{std::max(0, row - 1)}; i <= std::min(constants::num_rows - 1, row + 1); ++i) {
        for (int j{std::max(0, col - 1)}; j <= std::min(constants::num_cols - 1, col + 1); ++j) {
            if (i == row && j == col) {
                continue;
            }

            if (grid[(i * constants::num_cols) + j].has_bomb_) {
                ++count;
            }
        }
    }

    return count;
}
