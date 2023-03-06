#include "Button.h"

using namespace gui;

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    rectangle;
    states.transform *= getTransform();

    target.draw(, states);
}