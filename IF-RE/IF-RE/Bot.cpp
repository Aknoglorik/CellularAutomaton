#include "Bot.h"
#include "Environment.h"

namespace BotComand
{
	enum
	{
		move,
		eat
	};
}

int Bot::getNextInstruction()
{
	return rand() % 2; // 0 - move up, 1 - eat
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
		env->moveCell();
		break;
	case BotComand::eat:
		energy++;
		break;
	default:
		break;
	}


	energy--;
}
