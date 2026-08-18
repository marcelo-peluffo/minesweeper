#include "Flag.h"

Flag::Flag() : texture_(Flag::path), sprite_(texture_)
{
    ++Flag::count;
}

auto Flag::getSprite() const -> const ::sf::Sprite&
{
    return sprite_;
}
