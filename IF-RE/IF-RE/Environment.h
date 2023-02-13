#pragma once

#include <SFML/System.hpp>

#include "Object.h"
#include "Bots.h"
#include "GeneticAlgorithm.h"

class Environment
{
	int _width;
	int _height;

	GeneticAlgorithm* genAlg;
	std::vector<std::vector<Object>> matrix;

public:
	Environment(int width = 100, int height = 100);
	~Environment();

	const Object& getByPos(sf::Vector2i);
	const Object& getByPos(int, int);

	const std::vector<std::vector<Object>>& getMatrix();

};

