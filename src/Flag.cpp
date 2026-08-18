#include "Flag.h"

Flag::Flag() : texture_(Flag::path), sprite_(texture_)
{
    ++Flag::count;
}

Flag::Flag(const ::sf::Vector2f& pos)
    : Flag::Flag()
{
    sprite_.setPosition(pos);
    sprite_.setScale({0.3f, 0.3f});
}

auto Flag::getSprite() const -> const ::sf::Sprite&
{
    return sprite_;
}
