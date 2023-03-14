#pragma once
#include "Object.hpp"
#include <vector>

class Environment;

// Bioligical unit.
class Bot : public Object
{
	inline static const int type = cellType::Bot;
	std::vector<int> brain;
	int dir_move, dir_sight, cmd_counter = 0;
	Environment* env;

public:
	Bot(Environment *_env, sf::Vector2i pos, unsigned int _energy =  25) : env(_env)
	{
		this->energy = _energy;
		this->position = pos;
		this->brain.resize(16);
		for (int i = 0; i < 16; i++) 
		{
			this->brain[i] = rand() % 18;
		}
	}

	virtual int getType() { return type; };

	int getNextInstruction();
	void update() override;
};
