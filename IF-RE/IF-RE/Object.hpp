#pragma once

#include <SFML/System.hpp>


class Object
{
protected:
	sf::Vector2i position;

public:
	inline static const sf::String name = "Object";

	Object() {};
	virtual ~Object() {};

	/// \brief Object make his step.
	virtual void update() {};

	void setPos(sf::Vector2i newPos) { position = newPos; }
	void setPos(int x, int y) { position = sf::Vector2i(x, y); }

	sf::Vector2i getPos() const { return position; }
};

