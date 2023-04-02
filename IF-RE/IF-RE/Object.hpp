#pragma once

#include <SFML/System.hpp>
#include "consts.h"

extern class Environment;

class Object
{
protected:
	sf::Vector2i position;
	Environment* env = nullptr;

	inline static const int type = cellType::Object;
	bool is_die = false;
	unsigned int energy = 0;

public:
	Object() {}
	Object(Environment* _env) : env(_env) {}
	virtual ~Object() {}

	/// \brief Object make his step.
	virtual void update() {};

	void setIsDie(bool flag) { is_die = flag; }
	void setPos(sf::Vector2i newPos) { position = newPos; }
	void setPos(int x, int y) { position = sf::Vector2i(x, y); }
	void setEnergy(int _energy) { energy = _energy; }

	virtual int getType() { return type; };
	sf::Vector2i getPos() const { return position; }
	unsigned int getEnergy() const { return energy; }


	virtual void addEnergy(unsigned int value) { energy += value; }

	bool isDie() const { return is_die; }

protected:
	// \return false - if cant rudece energy, else true
	bool reduceEnergy(int value)
	{
		if (energy <= value)
		{
			energy = 0;
			is_die = true;
			return false;
		}
		energy -= value;
		return true;
	}
};

