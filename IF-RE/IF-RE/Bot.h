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
	Bot(Environment* _env, sf::Vector2i pos, unsigned int _energy = BOT_START_ENERGY,
		const std::vector<int>* parent_brain = nullptr);
	Bot(const Bot& other);

	void createRandomBrain();

	virtual int getType() { return type; };
	std::vector<int>& getBrain() { return brain; }

	int getNextInstruction();
	void update() override;
};
