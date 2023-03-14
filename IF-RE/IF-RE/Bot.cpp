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
	dir = rand() % 8;
	return rand() % 3; // 0 - move, 1 - photosynthesis, 2 - nothing
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
		env->moveCell(dir);
		break;
	case BotComand::photosynthesis:
		energy += 2;
		break;
	case BotComand::nothing:
		break;
	default:
		break;
	}

}
