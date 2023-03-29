#include "GeneticAlgorithm.h"
#include "Environment.h"

GeneticAlgorithm::GeneticAlgorithm(int num_out_select, float mutation_precent) 
	: _out_selection(num_out_select), _mutation_probability(mutation_precent)
{
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

int GeneticAlgorithm::fitness(Bot* entity)
{
	return entity->move_counter;
}

Bot* GeneticAlgorithm::mutation(const Bot* entity)
{
	auto newBot = new Bot(*entity);
	int rnd_cmd_pos = rand() % BOT_BRAIN_SIZE;

	//float probability = static_cast <float>(rand()) / static_cast <float> (RAND_MAX);
	//if (probability <= _mutation_probability)
	newBot->getBrain()[rnd_cmd_pos] = rand() % BOT_CMD_AMOUNT;

	return newBot;
}

// \brief delete old population and create new by params
std::list<Bot*> GeneticAlgorithm::selection(std::list<Bot*>& old_pop)
{
	old_pop.sort(
		[&](Bot* a, Bot* b)
		{
			return fitness(a) > fitness(b);
		});
  	int i = 0;
	std::list<Bot*> new_pop;
	for (auto bot : old_pop)
	{
		if (i < 10) // MOVE CONST to certain file
		{
			new_pop.push_back(bot);
			for (int j = 0; j < 8; j++)
			{
				auto newbot = new Bot(*bot);
				new_pop.push_back(newbot);
			}
			new_pop.push_back(mutation(bot));
		}
		else
			break;
		i++;
	}

	// TODO! Check if new_pop.size() < necassary
	while (old_pop.size() > 10)
	{
		auto bot = old_pop.back();
		bot->env->matrix[bot->position.x][bot->position.y] = bot->env->mainEmptiness; // so terribly
		delete bot;
		old_pop.pop_back();
	}
	// clear mem
	old_pop.clear();
	return new_pop;
}
