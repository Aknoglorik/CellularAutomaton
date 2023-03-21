#pragma once
#include "Object.hpp"
#include <vector>

class Environment;

// Bioligical unit.
class Bot : public Object
{
	inline static const int type = cellType::Bot;
	std::vector<int> brain;
	int dir_move	= 0;
	int dir_sight	= 0;
	int cmd_counter = 0;
	Environment* env;

public:
	Bot(Environment *_env, sf::Vector2i pos, unsigned int _energy = BOT_START_ENERGY) : env(_env)
	{
		energy = _energy;
		position = pos;
		
		brain.resize(BOT_BRAIN_SIZE);
		for (int i = 0; i < BOT_BRAIN_SIZE; i++)
		{
			brain[i] = rand() % 18;
		}
	}

	virtual int getType() { return type; };

	int getNextInstruction();
	void update() override;
};
