#include "Bot.h"
#include "Environment.h"



int Bot::getNextInstruction()
{



	dir_move = rand() % 8;
	dir_sight = rand() % 8;
	return 1; rand() % 3;  // 0 - move, 2 - photosynthesis, 1 - eat, 3 - nothing
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
		int abs_dir = dir_move - dir_sight;
		if (abs_dir < 0)
			abs_dir += 8;
		env->moveCell(abs_dir);
		break; 
	}
	case botCmd::eat:
		env->eatCell(dir_sight);
		break;
	case botCmd::photosynthesis: 
	{
		int power = env->getHeight() / (position.y + 1);
		energy += power;
		break;
	}
	case botCmd::nothing:
		break;
	default:
		break;
	}
	energy--;
}
