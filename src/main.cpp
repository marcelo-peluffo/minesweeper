#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}),
                          "Game");

  while (window.isOpen()) {
    while (std::optional<sf::Event> event{window.pollEvent()}) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear(sf::Color::White);
    window.display();
  }

  return constants::exit_code_success;
}
