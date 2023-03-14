#pragma once

#include <SFML/System.hpp>

namespace cellType
{
	enum
	{
		Emptiness,
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
	bool is_die = false;
	unsigned int energy = 0;

public:
	Object() {};
	virtual ~Object() {};

	/// \brief Object make his step.
	virtual void update() {};

	virtual int getType() { return type; };

	void setPos(sf::Vector2i newPos) { position = newPos; }
	void setPos(int x, int y) { position = sf::Vector2i(x, y); }

	sf::Vector2i getPos() const { return position; }
	unsigned int getEnergy() const { return energy; }


	virtual void addEnergy(unsigned int value) { energy += value; }

	bool isDie() const { return is_die; }
};

