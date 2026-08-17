#include "MSWindow.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include "GameContext.h"
#include "Text.h"
#include "BombUtils.h"

MSWindow::MSWindow() : underlyingWindow_(::sf::VideoMode({constants::width, constants::height}), Text::gameTitle) {}

auto MSWindow::render(const GameContext& context) -> void
{
    underlyingWindow_.clear(::sf::Color::White);

    /*
     * should double check if text pos = tile pos center
     */
    for (const auto& tile : context.grid_)
    {
        underlyingWindow_.draw(tile.shape_);

        if (tile.clicked_)
        {
            underlyingWindow_.draw(tile.textNeighboringBombs_);
        }
    }

    underlyingWindow_.display();
}

auto MSWindow::pollEvent() -> const std::optional<::sf::Event>&
{
    lastEvent_ = underlyingWindow_.pollEvent();
    return lastEvent_;
}

// should be equivalent to input, need to see about handle input fn as well
auto MSWindow::handleLastEvent(GameContext& context) -> void
{
    if (lastEvent_->is<::sf::Event::Closed>())
    {
        underlyingWindow_.close();
    }

    else if (const auto* mouse{lastEvent_->getIf<::sf::Event::MouseButtonPressed>()})
    {
        const auto mousePos{static_cast<::sf::Vector2f>(mouse->position)};

        if (auto tile{ BombUtils::clickedTile(context.grid_, mousePos) })
        {
            BombUtils::handleTileClick(*tile, mouse->button);
        }
    }
}
