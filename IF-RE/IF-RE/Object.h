#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Object : public sf::Drawable, public sf::Transform
{
protected:
	sf::Vector2i position;

public:

	virtual void update() = 0;

	void setPos(sf::Vector2i);
	void setPos(int, int);

	sf::Vector2i getPos();

};

