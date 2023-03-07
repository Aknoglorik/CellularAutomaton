#include "Button.h"
#include "ExtraColors.hpp"
#include <iostream>

using namespace gui;

enum _status
{
    _default = 0,
    _hovered = 1,
    _clicked = 2
};

Button::Button(sf::FloatRect _size) : size(_size)
{
    m_callback = [](){};
    myStatus = _status::_default;

    rectangle.setPosition(sf::Vector2f(_size.left, _size.top));
    rectangle.setSize(sf::Vector2f(_size.width, _size.height));
    rectangle.setFillColor(sf::Color::Black);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(rectangle, states);
}

void gui::Button::update(sf::RenderWindow& target)
{
    sf::Vector2f pos = (sf::Vector2f) sf::Mouse::getPosition(target);

    if (size.contains(pos))
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            rectangle.setFillColor(gui::Color::Green);
            m_callback();
        }
        else
        {
            rectangle.setFillColor(gui::Color::DullWhite);
        }

}

void gui::Button::bind(std::function<void(void)> new_callback)
{
    m_callback = new_callback;
}
