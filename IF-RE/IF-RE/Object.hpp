#pragma once

#include <SFML/System.hpp>

namespace cellType
{
	enum
	{
		Empiness,
		Bot,
		Food,
		Corpse,
		Object
	};
}

class Object
{
protected:
	sf::Vector2i position;

	inline static const int type = cellType::Object;

public:
	Object() {};
	virtual ~Object() {};

	/// \brief Object make his step.
	virtual void update() {};

	virtual int getType() { return type; };

	void setPos(sf::Vector2i newPos) { position = newPos; }
	void setPos(int x, int y) { position = sf::Vector2i(x, y); }

	sf::Vector2i getPos() const { return position; }
};

