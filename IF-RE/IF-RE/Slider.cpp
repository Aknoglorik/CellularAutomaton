#include "Slider.h"
#include "ExtraColors.hpp"


using namespace gui;

enum _status
{
    _default = 0,
    _hovered = 1,
    _clicked = 2
};


Slider::Slider(sf::Vector2f p1, sf::Vector2f p2, float height, int start_value, int _max_value) : value(start_value), max_value(_max_value)
{
    circle_radius = height / 2;

    float factor = (float)value / max_value;
    float width = p2.x - p1.x;

    sf::Vector2f midle_point(p1.x + (width) * factor,
                              p1.y + (p2.y - p1.y) * factor);

    line1.setPosition(p1);
    line2.setPosition(p1);
    circle.setPosition(midle_point.x - circle_radius, midle_point.y);

    line1.setSize(sf::Vector2f(midle_point.x - p1.x, 2 * circle_radius));
    line2.setSize(sf::Vector2f(p2.x - p1.x, 2 * circle_radius));
    circle.setRadius(circle_radius);

    hitbox = sf::FloatRect(p1, sf::Vector2f(width, 2* circle_radius));

    setByStat(_status::_default);
}

gui::Slider::~Slider()
{
}

void Slider::setByStat(int status)
{
    switch (status)
    {
    case _default:
        line1.setFillColor(gui::Color::Clay);
        line2.setFillColor(gui::Color::Gray);
        circle.setFillColor(sf::Color::White);
        break;
    case _hovered:
        circle.setFillColor(gui::Color::DullWhite);
        break;
    case _clicked:
        circle.setFillColor(gui::Color::Green);
        break;
    default:
        break;
    }
}

void Slider::setupByPos(sf::Vector2f pos)
{
    float width = pos.x - hitbox.left;

    // check if mouse out of hitbox
    if (width < 0)
        pos.x = hitbox.left;
    else if (width > hitbox.width)
        pos.x = hitbox.left + hitbox.width;

    // new width = (pos.x - hitbox.left)
    value = (pos.x - hitbox.left) / hitbox.width * max_value;

    line1.setSize(sf::Vector2f(pos.x - line1.getPosition().x, 2 * circle_radius));
    circle.setPosition(pos.x - circle_radius, hitbox.top);
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(line2, states);
    target.draw(line1, states);
    target.draw(circle, states);
}

void gui::Slider::update(sf::RenderWindow& target)
{
    // sf::View target_view = target.getView();
    sf::Vector2i m_pos = sf::Mouse::getPosition(target);

    bool isClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    sf::Vector2f pos = target.mapPixelToCoords(m_pos);

    if (isPressed)
    {
        setupByPos(pos);
        if (!isClick)
            isPressed = false;
        return;
    }

    if (hitbox.contains(pos))
    {
        if (!isClick)
            isClickedOnThis = true;

        if (isClick && isClickedOnThis)
        {
            setupByPos(pos);
            isPressed = true;
            setByStat(::_clicked);
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

void Slider::setValue(int val)
{
    sf::Vector2f pos(hitbox.left + (float)val/max_value * hitbox.width, 0);

    setupByPos(pos);
}

