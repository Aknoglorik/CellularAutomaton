#include "Button.h"
#include "ExtraColors.hpp"
#include "Label.h"
#include <iostream>

using namespace gui;

Button::Button(sf::FloatRect _size, const sf::Font &font, sf::String str) : size(_size)
{
    setPosition(sf::Vector2f(_size.left, _size.top));
    rectangle.setSize(sf::Vector2f(_size.width, _size.height));

    // Setting up label
    label = new Label;
    label->setPosition(this->getPosition());
    label->setString(sf::String(str));
    label->setCharSize(_size.height);
    label->setFont(font);
    
    setByStat(_status::_default);
}

void gui::Button::setString(sf::String str)
{
    label->setString(str);
}

void Button::setByStat(_status status)
{
    switch (status)
    {
    case _default:
        label->setColor(sf::Color::Black);
        rectangle.setFillColor(sf::Color::White);
        break;
    case _hovered:
        label->setColor(sf::Color::Magenta);
        rectangle.setFillColor(gui::Color::DullWhite);
        break;
    case _clicked:
        label->setColor(sf::Color::Red);
        rectangle.setFillColor(gui::Color::Green);
        break;
    default:
        break;
    }
};

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(rectangle, states);
    if (label)
        target.draw(*label, states);
}

void Button::update(sf::RenderWindow& target)
{
    sf::Vector2f pos = (sf::Vector2f) sf::Mouse::getPosition(target);
    label->update();
    bool isClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isPressed)
    {
        if (!isClick)
            isPressed = false;
        return;
    }

    if (size.contains(pos))
    {
        if (!isClick)
            isClickedOnThis = true;
        if (isClick && isClickedOnThis)
        {
            isPressed = true;
            setByStat(_status::_clicked);
            m_callback();
        }
        else
        {
            setByStat(_status::_hovered);
        }

    }
    else
    {
        if (isClick)
            isClickedOnThis = false;
        setByStat(_status::_default);
    }

}

void Button::bind(std::function<void(void)> new_callback)
{
    m_callback = new_callback;
}
