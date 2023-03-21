#include "Bot.h"
#include "Environment.h"



int Bot::getNextInstruction()
{
	int b = 0;
	if ((brain[cmd_counter] >= 0) && (brain[cmd_counter] <= 7))
	{
		dir_move = brain[cmd_counter];
		b = 0;
	}
	else if ((brain[cmd_counter] >= 8) && (brain[cmd_counter] <= 15))
	{
		dir_sight = brain[cmd_counter] - 8;
		b = 3;
	}
	else if (brain[cmd_counter] == 16)
		b = 2;
	else if (brain[cmd_counter] == 17)
		b = 1;
	cmd_counter++;
	if (cmd_counter == 18) cmd_counter = 0;
	return b;  // 0 - move, 1 - eat, 2 - photosynthesis, 3 - nothing
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
