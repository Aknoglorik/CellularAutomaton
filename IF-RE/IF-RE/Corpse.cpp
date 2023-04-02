#include "Corpse.h"
#include "Bot.h"
#include "Environment.h"

int _tempPenalti(float x)
{
	int res = ceil(exp(x/16));

	if (!res)
		res = 1;
	return res;
}

Corpse::Corpse(Environment* _env, Bot* bot) : Object(_env)
{
	energy = bot->getEnergy();
	position = bot->getPos();
}

void Corpse::update()
{
	if (is_die)
		return;

	int penalti = _tempPenalti(this->env->getTemperatureMatrix()[position.x][position.y]);
	if (!reduceEnergy(penalti))
		is_die = true;

	env->localReduceTemp(position, -FOOD_REDUCE_TEMP);
}
