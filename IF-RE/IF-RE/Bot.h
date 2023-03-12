#pragma once
#include "Object.hpp"
#include <vector>

class Environment;

// Bioligical unit.
class Bot : public Object
{
	inline static const int type = cellType::Bot;

	unsigned int energy;
	std::vector<int> brain;

	Environment* env;

public:
	Bot(Environment *_env, sf::Vector2i pos, int _energy =  100) : env(_env), energy(_energy)
	{
		this->position = pos;
	}

	virtual int getType() { return type; };

	int getNextInstruction();

	void update() override;
};
