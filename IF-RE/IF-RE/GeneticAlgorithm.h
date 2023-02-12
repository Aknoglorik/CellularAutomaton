#pragma once

#include "Object.h"
#include <vector>

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	int fitness(const Object& entity);
	Object mutation(const Object& entity);

	std::vector<Object> selection(const std::vector<Object>&);

};

