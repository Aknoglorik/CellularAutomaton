#pragma once

#include "Bot.h"
#include <list>
#include <vector>

class GeneticAlgorithm
{
	int _out_selection;
	float _mutation_probability;

public:
	GeneticAlgorithm(int num_out_select = 8, float mutation_precent = .25);
	~GeneticAlgorithm();

	int fitness(Bot* entity);
	Bot* mutation(const Bot* entity);
	std::list<Bot*> selection(std::list<Bot*>&);

	std::list<Bot*> newPopulation(const std::list<Bot*>&);

	void setOutSelection(int num_out_select) { _out_selection = num_out_select; }
	void setMutationProbability(float mutation_precent) { _mutation_probability = mutation_precent; }

	int getOutSelection() { return _out_selection; }
	float getMutationProbability() { return _mutation_probability; }
};

