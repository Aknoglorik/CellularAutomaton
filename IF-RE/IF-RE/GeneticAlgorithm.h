#pragma once

#include "Object.hpp"
#include <vector>

class GeneticAlgorithm
{
	int _out_selection;
	float _mutation_probability;

public:
	GeneticAlgorithm(int num_out_select = 8, float mutation_precent = .25);
	~GeneticAlgorithm();

	int fitness(const Object& entity);
	Object mutation(const Object& entity);
	std::vector<Object> selection(const std::vector<Object>&);

	void setOutSelection(int num_out_select) { _out_selection = num_out_select; }
	void setMutationProbability(int mutation_precent) { _mutation_probability = mutation_precent; }

	int getOutSelection() { return _out_selection; }
	int getMutationProbability() { return _mutation_probability; }
};

