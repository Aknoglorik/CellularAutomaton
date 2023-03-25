#include "Bot.h"
#include "Environment.h"


Bot::Bot(Environment* _env, sf::Vector2i pos, unsigned int _energy, const std::vector<int>* parent_brain)
	: env(_env)
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

// \brief copy-constructor
Bot::Bot(const Bot& other)
{
	env = other.env;
	energy = other.energy;
	position = other.position;

	brain.resize(other.brain.size());
	std::copy(other.brain.begin(), other.brain.end(), brain.begin());
}

void Bot::createRandomBrain()
{
	for (int i = 0; i < BOT_BRAIN_SIZE; i++)
	{
		brain[i] = rand() % BOT_CMD_AMOUNT;
	}
}

int Bot::getNextInstruction()
{
	int Inst = botCmd::nothing;
	if ((brain[cmd_counter] >= 0) && (brain[cmd_counter] <= 7))
	{
		dir_move = brain[cmd_counter];
		Inst = botCmd::move;
		cmd_counter++;
	}
	else if ((brain[cmd_counter] >= 8) && (brain[cmd_counter] <= 15))
	{
		dir_sight = brain[cmd_counter] - 8;
		Inst = botCmd::nothing;
		cmd_counter++;
	}
	else if (brain[cmd_counter] == 16)
	{
		Inst = botCmd::photosynthesis;
		cmd_counter++;
	}
	else if (brain[cmd_counter] == 17)
	{
		Inst = botCmd::eat;
		cmd_counter++;
	}
	else if (brain[cmd_counter] == 18)
	{
		Inst = botCmd::gemmation;
		cmd_counter++;
	}
	//Check energy very more if)
	else if (brain[cmd_counter] == 19)
	{
		Inst = botCmd::nothing;
		if ((cmd_counter + 1) == BOT_BRAIN_SIZE)
			cmd_counter = 0;
		else
			cmd_counter++;
		if (energy > (brain[cmd_counter] * 3))
		{
			if ((cmd_counter + 1) == BOT_BRAIN_SIZE)
				cmd_counter = 0;
			else
				cmd_counter++;
			cmd_counter = (brain[cmd_counter] + 62) % BOT_BRAIN_SIZE;
		}
		else
		{
			if ((cmd_counter + 2) == BOT_BRAIN_SIZE)
				cmd_counter = 0;
			else if ((cmd_counter + 2) > BOT_BRAIN_SIZE)
				cmd_counter = (cmd_counter + 2) % BOT_BRAIN_SIZE;
			else cmd_counter += 2;
			cmd_counter = (brain[cmd_counter] + 61) % BOT_BRAIN_SIZE;
		}
	}
	//Check bot position.y 
	else if (brain[cmd_counter] == 20)
	{
		Inst = botCmd::nothing;
		if ((cmd_counter + 1) == BOT_BRAIN_SIZE)
			cmd_counter = 0;
		else
			cmd_counter++;
		if (position.y > brain[cmd_counter]) 
			cmd_counter = (cmd_counter + brain[cmd_counter]) % BOT_BRAIN_SIZE;
	}

	cmd_counter %= BOT_BRAIN_SIZE;

	return Inst;  // 0 - move, 1 - eat, 2 - photosynthesis, 3 - nothing, 4 - gemmation
};

void Bot::update()
{
	if (is_die || energy <= 0)
	{
		is_die = true;
		return;
	}

	switch (getNextInstruction())
	{
	case botCmd::move:
	{
		int abs_dir = dir_move + dir_sight;
		if (abs_dir > 7)
			abs_dir -= 8;
		env->moveCell(abs_dir);
		break; 
	}
	case botCmd::eat:
		spriteType = botSpriteType::predator;
		env->eatCell(dir_sight);
		break;
	case botCmd::photosynthesis: 
	{
		int power = env->getTemperatureMatrix()[position.x][position.y] + env->getGloabalTemp();
		if (((long)energy + power) > 0)
			energy += power;
		else
			energy = 0;

		break;
	}
	case botCmd::nothing:
		break;
	case botCmd::gemmation:
		env->gemmationCell(dir_sight);
		break;
	default:
		break;
	}

	if ((long)energy > BOT_MAX_ENERGY)
		energy = BOT_MAX_ENERGY;

	if(energy)
		energy--;
}
