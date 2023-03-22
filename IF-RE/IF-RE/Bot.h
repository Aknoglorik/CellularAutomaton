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
	Bot(Environment *_env, sf::Vector2i pos, unsigned int _energy = BOT_START_ENERGY, 
		const std::vector<int>* parent_brain = nullptr) : env(_env)
	{
		energy = _energy;
		position = pos;
		brain.resize(BOT_BRAIN_SIZE);
		if (!parent_brain)
			createRandomBrain();
		else
			for (int i = 0; i < BOT_BRAIN_SIZE; i++)
				brain[i] = parent_brain->at(i);
	}

	void createRandomBrain();

	virtual int getType() { return type; };
	const std::vector<int>* getPBrain() { return &brain; }

	int getNextInstruction();
	void update() override;
};
