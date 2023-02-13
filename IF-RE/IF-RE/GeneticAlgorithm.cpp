#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int num_out_select, float mutation_precent) 
	: _out_selection(num_out_select), _mutation_probability(mutation_precent)
{
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

int GeneticAlgorithm::fitness(const Object& entity)
{
	return 0;
}

Object GeneticAlgorithm::mutation(const Object& entity)
{
	return Object();
}
