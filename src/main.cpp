#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({constants::width, constants::height}),
                          "Minesweeper");

  while (window.isOpen()) {
    while (auto event{window.pollEvent()}) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      window.clear(sf::Color::White);
      // draw here

      window.display();
    }
  }

  return 0;
}
