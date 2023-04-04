#include "Bot.h"
#include "Environment.h"
#include <iostream>

int tempPenalti(float x)
{
	int res = ceil((float)pow(x - 10, 2) / 32);

	if (!res)
		res = 1;
	return res;
}


Bot::Bot(Environment* _env, sf::Vector2i pos, unsigned int _energy, const std::vector<int>* parent_brain)
	: Object(_env)
{
	energy = _energy;
	position = pos;
	brain.resize(BOT_BRAIN_SIZE);
	if (!parent_brain)
		createRandomBrain();
	else
		for (int i = 0; i < BOT_BRAIN_SIZE; i++)
			brain[i] = parent_brain->at(i);
	bot_count++;
}

// \brief copy-constructor
Bot::Bot(const Bot& other) : Object(other.env)
{
	env = other.env;
	energy = other.energy;
	position = other.position;

	brain.resize(other.brain.size());
	std::copy(other.brain.begin(), other.brain.end(), brain.begin());
	bot_count++;
}

void Bot::createRandomBrain()
{
	for (int i = 0; i < BOT_BRAIN_SIZE; i++)
	{
		brain[i] = rand() % BOT_CMD_AMOUNT;
	}
}

void Bot::digest()
{
	if (digested_material - digest_speed >= 0)
		energy += digest_speed * BOT_DIGEST_RATIO;
	else
	{
		energy += digested_material * BOT_DIGEST_RATIO;
		digested_material = 0;
	}
}

void Bot::reSetup()
{
	// props
	digested_material = 0;
	dir_move = 0;
	dir_sight = 0;

	cmd_counter = 0;
	life_counter = 0;
	move_counter = 0;
	spriteType = botSpriteType::prey;

	energy = BOT_START_ENERGY;
	is_die = false;
}

int ifer(int p)
{
	if (p > (BOT_BRAIN_SIZE - 1))
		p %= BOT_BRAIN_SIZE;
	return p;
}

int Bot::getNextInstruction()
{
	if (brain[cmd_counter] == 64)
		cmd_counter--;

	int Inst = botCmd::nothing;
	//move
	if ((brain[cmd_counter] >= 0) && (brain[cmd_counter] <= 7))
	{
		dir_move = brain[cmd_counter];
		Inst = botCmd::move;
		cmd_counter++;
	}
	//direction sight
	else if ((brain[cmd_counter] >= 8) && (brain[cmd_counter] <= 15))
	{
		dir_sight += (brain[cmd_counter]);
		dir_sight %= 8;
		Inst = botCmd::nothing;
		cmd_counter++;
	}
	//photosynthesis
	else if (brain[cmd_counter] == 16) 
	{
		Inst = botCmd::photosynthesis;
		cmd_counter++;
	}
	//eat
	else if (brain[cmd_counter] == 17)
	{
		Inst = botCmd::eat;
		cmd_counter++;
	}
	/*else if (brain[cmd_counter] == 18)
	{
		Inst = botCmd::gemmation;
		cmd_counter++;
	}*/
	//Check temperature
	else if (brain[cmd_counter] == 18)
	{
		Inst = botCmd::nothing;
		if ((cmd_counter + 1) == BOT_BRAIN_SIZE)
			cmd_counter = 0;
		else
			cmd_counter++;
		if (env->getTemperatureMatrix()[position.x][position.y] > (brain[cmd_counter] * 3))
		{
			if ((cmd_counter + 1) == BOT_BRAIN_SIZE)
				cmd_counter = 0;
			else
				cmd_counter++;
			cmd_counter = ifer(brain[cmd_counter] + BOT_BRAIN_SIZE - 2);
		}
		else
		{
			if ((cmd_counter + 2) == BOT_BRAIN_SIZE)
				cmd_counter = 0;
			else if ((cmd_counter + 2) > BOT_BRAIN_SIZE)
				cmd_counter = ifer(cmd_counter + 2);
			else cmd_counter += 2;
			cmd_counter = ifer(brain[cmd_counter] + BOT_BRAIN_SIZE - 3);
		}
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
			cmd_counter = ifer(brain[cmd_counter] + BOT_BRAIN_SIZE - 2);
		}
		else
		{
			if ((cmd_counter + 2) == BOT_BRAIN_SIZE)
				cmd_counter = 0;
			else if ((cmd_counter + 2) > BOT_BRAIN_SIZE)
				cmd_counter = ifer(cmd_counter + 2);
			else cmd_counter += 2;
			cmd_counter = ifer(brain[cmd_counter] + BOT_BRAIN_SIZE - 3);
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
			cmd_counter = ifer(cmd_counter + brain[cmd_counter]);
	}
	//look around
	else if (brain[cmd_counter] == 25)
	{
		int delta = 0;
		switch (env->lookAround(dir_sight))
		{
		case cellType::Wall:
			delta = 1;
			break;
		case cellType::Emptiness:
			delta = 2;
			break;
		case cellType::Bot:
			delta = 3;
			break;
		case cellType::Food:
			delta = 4;
			break;
		case cellType::Corpse:
			delta = 5;
			break;
		}
		cmd_counter += brain[ifer(cmd_counter + delta)];
	}
	else if (brain[cmd_counter] == 27)
	{
		cmd_counter = ifer(cmd_counter + 1);
		dir_move = brain[cmd_counter] % 8;
		Inst = botCmd::move;
		int delta = 0;
		switch (env->lookAround(dir_sight))
		{
		case cellType::Wall:
			delta = 1;
			break;
		case cellType::Emptiness:
			delta = 2;
			break;
		case cellType::Bot:
			delta = 3;
			break;
		case cellType::Food:
			delta = 4;
			break;
		case cellType::Corpse:
			delta = 5;
			break;
		}
		cmd_counter += brain[ifer(cmd_counter + delta)] + BOT_BRAIN_SIZE - 1;
	}
	else
		cmd_counter += brain[cmd_counter]; 

	cmd_counter = ifer(cmd_counter);

	return Inst;  // 0 - move, 1 - eat, 2 - photosynthesis, 3 - nothing, 4 - gemmation
};

void Bot::update()
{
	if (is_die || energy <= 0)// || life_counter >= BOT_MAX_LIFE)
	{
		is_die = true;
		return;
	}

	switch (getNextInstruction())
	{
	case botCmd::move:
	{
		if (!reduceEnergy(BOT_NRG_TO_MOVE))
			break;

		int abs_dir = dir_move + dir_sight;
		if (abs_dir > 7)
			abs_dir -= 8;
		if (env->moveCell(abs_dir))
			move_counter++;
		break; 
	}
	case botCmd::eat:
	{
		if (!reduceEnergy(BOT_NRG_TO_EAT))
			break;

		spriteType = botSpriteType::predator;
		env->eatCell(dir_sight);
		break;
	}
	case botCmd::photosynthesis: 
	{
		/*if (spriteType == botSpriteType::predator)
			break;*/

		int power = env->getLightMatrix()[position.x][position.y] + env->getGloaballight();
		energy += power;
		break;
	}
	case botCmd::nothing:
		break;
	case botCmd::gemmation:
		//env->gemmationCell(dir_sight);
		break;
	default:
		break;
	}

	if ((long)energy > BOT_MAX_ENERGY)
		energy = BOT_MAX_ENERGY;

	if (spriteType == botSpriteType::predator)
		digest();

	int penalti = tempPenalti(env->getTemperatureMatrix()[position.x][position.y] + env->getGloabalTemp());
	//reduceEnergy(penalti);

	env->localReduceTemp(position, -10);
	life_counter++;
}
