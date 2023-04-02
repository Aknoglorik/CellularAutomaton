#include "GeneticAlgorithm.h"
#include "Environment.h"

GeneticAlgorithm::GeneticAlgorithm(int in_num_selection, int descendants_num, int mutation_num)
	: _in_num_selection(in_num_selection), _descendants_num(descendants_num), _mutation_num(mutation_num)
{
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

int GeneticAlgorithm::fitness(Bot* entity)
{
	return entity->life_counter;
	//return entity->move_counter;
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
		if (i < _in_num_selection) // MOVE CONST to certain file
		{
			new_pop.push_back(bot); // Save old bot
			for (int j = 0; j < _descendants_num - _mutation_num - 1; j++) // copy him
			{
				auto newbot = new Bot(*bot);
				new_pop.push_back(newbot);
			}
			for (int j = 0; j < _mutation_num; j++) // copy him _descendants_num-2 times
			{
				new_pop.push_back(mutation(bot)); // add mutaded bots
			}
		}
		else
			break;
		i++;
	}

	// TODO! Check if new_pop.size() < necassary
	while (old_pop.size() > _in_num_selection)
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
