#include "Bot.h"
#include "Environment.h"

namespace BotComand
{
	enum
	{
		move,
		photosynthesis,
		nothing
	};
}

int Bot::getNextInstruction()
{



	dir_move = rand() % 8;
	dir_sight = rand() % 8;
	return rand() % 3;  // 0 - move, 1 - photosynthesis, 2 - nothing
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
	case BotComand::move:
	{
		int abs_dir = dir_move - dir_sight;
		if (abs_dir < 0)
			abs_dir += 8;
		env->moveCell(abs_dir);
		break; 
	}
	case BotComand::photosynthesis: 
	{
		int power = env->getHeight() / (position.y + 1);
		energy += power;
		break;
	}
	case BotComand::nothing:
		break;
	default:
		break;
	}
	energy--;
}
