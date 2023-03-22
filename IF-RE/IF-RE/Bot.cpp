#include "Bot.h"
#include "Environment.h"



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
	}
	else if ((brain[cmd_counter] >= 8) && (brain[cmd_counter] <= 15))
	{
		dir_sight = brain[cmd_counter] - 8;
		Inst = botCmd::nothing;
	}
	else if (brain[cmd_counter] == 16)
		Inst = botCmd::photosynthesis;
	else if (brain[cmd_counter] == 17)
		Inst = botCmd::eat;
	else if (brain[cmd_counter] == 18)
		Inst = botCmd::gemmation;

	cmd_counter++;
	if (cmd_counter == BOT_BRAIN_SIZE)
		cmd_counter = 0;

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
	case botCmd::gemmation:
		env->gemmationCell(dir_sight);
		break;
	default:
		break;
	}
	if(energy)
		energy--;
}
