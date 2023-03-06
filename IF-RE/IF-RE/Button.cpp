#include "Button.h"

using namespace gui;

Button::Button(sf::FloatRect size)
{
    rectangle.setPosition(sf::Vector2f(size.left, size.top));
    rectangle.setSize(sf::Vector2f(size.width, size.height));
    rectangle.setFillColor(sf::Color::Black);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(rectangle, states);
}