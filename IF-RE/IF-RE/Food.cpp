#include "Food.h"
#include "Environment.h"

extern int tempPenalti(float);

void Food::update()
{
	if (is_die)
		return;
	int penalti = tempPenalti(this->env->getTemperatureMatrix()[position.x][position.y]);
	if (!reduceEnergy(penalti))
		is_die = true;

	env->localReduceTemp(position, FOOD_REDUCE_TEMP);
}