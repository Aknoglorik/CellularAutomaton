#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int num_out_select, float mutation_precent) 
	: _out_selection(num_out_select), _mutation_probability(mutation_precent)
{
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

int GeneticAlgorithm::fitness(const Bot& entity)
{
	return 0;
}

Bot* GeneticAlgorithm::mutation(const Bot* entity)
{
	auto newBot = new Bot(*entity);
	int rnd_cmd_pos = rand() % BOT_BRAIN_SIZE;

	float probability = static_cast <float>(rand()) / static_cast <float> (RAND_MAX);

	if (probability <= _mutation_probability)
		newBot->getBrain()[rnd_cmd_pos] = rand() & BOT_CMD_AMOUNT;

	return newBot;
}

std::vector<Bot*> GeneticAlgorithm::selection(const std::vector<Bot*>&)
{
	return std::vector<Bot*>();
}
