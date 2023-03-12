#pragma once
#include "Object.hpp"
#include <vector>

class Environment;

// Bioligical unit.
class Bot : public Object
{
	inline static const int type = cellType::Bot;
	std::vector<int> brain;

	Environment* env;

public:
	Bot(Environment *_env, sf::Vector2i pos, unsigned int _energy =  25) : env(_env)
	{
		this->energy = _energy;
		this->position = pos;
	}

	virtual int getType() { return type; };

	int getNextInstruction();

	void update() override;
};
