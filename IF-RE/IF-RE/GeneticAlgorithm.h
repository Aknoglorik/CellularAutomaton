#pragma once

#include "Bot.h"
#include <list>
#include <vector>

class GeneticAlgorithm
{
	int _in_num_selection;
	int _descendants_num;
	int _mutation_num;

public:
	GeneticAlgorithm(int in_num_selection = ENV_NUM_SELECTION, int descendants_num = ENV_NUM_DESCENDANTS, int mutation_num = ENV_NUM_MUTATION);
	~GeneticAlgorithm();

	int fitness(Bot* entity);
	Bot* mutation(const Bot* entity);
	std::list<Bot*> selection(std::list<Bot*>&);

	std::list<Bot*> newPopulation(const std::list<Bot*>&);

	void setOutSelection(int num_out_select) { _in_num_selection = num_out_select; }
	void setMutationProbability(int mutation_precent) { _mutation_num = mutation_precent; }

	int getOutSelection() { return _in_num_selection; }
	int getMutationProbability() { return _mutation_num; }
};

