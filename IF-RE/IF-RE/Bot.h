#pragma once
#include "Object.hpp"
#include <vector>

class GeneticAlgorithm;

// Bioligical unit.
class Bot : public Object
{
	inline static const int type = cellType::Bot;
	inline static int bot_count = 0;

	std::vector<int> brain;

	// props
	int digested_material = 0;
	int digest_speed = BOT_DIGEST_SPEED;
	int dir_move = 0;
	int dir_sight = 0;


	int cmd_counter = 0;
	int life_counter = 0;
	int move_counter = 0;

	int spriteType = botSpriteType::prey;

public:
	Bot(Environment* _env, sf::Vector2i pos, unsigned int _energy = BOT_START_ENERGY,
		const std::vector<int>* parent_brain = nullptr);
	Bot(const Bot& other);
	~Bot() { bot_count--; }

	void createRandomBrain();

	virtual int getSpriteType() const { return spriteType; }
	virtual int getType() { return type; };
	std::vector<int>& getBrain() { return brain; }
	int getCmdCounter() { return cmd_counter; };
	int getLifeCounter() { return life_counter; };
	int getDigestedMaterial() { return digested_material; };

	void addDigestMaterial(int amount) { digested_material += amount; }

	friend Environment;
	friend GeneticAlgorithm;

	int getNextInstruction();
	void update() override;
	void digest();

	void reSetup();

};
