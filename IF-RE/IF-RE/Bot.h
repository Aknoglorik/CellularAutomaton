#pragma once
#include "Object.hpp"
#include <vector>

class Environment;

// Bioligical unit.
class Bot : public Object
{
	inline static const int type = cellType::Bot;
	std::vector<int> brain;
	int dir_move;
	int dir_sight;
	int cmd_counter;
	Environment* env;

public:
	Bot(Environment *_env, sf::Vector2i pos, unsigned int _energy = BOT_START_ENERGY) : env(_env)
	{
		this->energy = _energy;
		this->position = pos;
		dir_move	= 0;
		dir_sight	= 0;
		cmd_counter = 0;
		this->brain.resize(BOT_BRAIN_SIZE);
		for (int i = 0; i < BOT_BRAIN_SIZE; i++)
		{
			this->brain[i] = rand() % 18;
		}
	}

	virtual int getType() { return type; };

	int getNextInstruction();
	void update() override;
};
