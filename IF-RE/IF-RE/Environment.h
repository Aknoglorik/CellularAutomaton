#pragma once

#include <SFML/System.hpp>

#include "Object.hpp"
#include "Bots.h"
#include "GeneticAlgorithm.h"


class Environment
{
	int _width;
	int _height;

	GeneticAlgorithm* genAlg = nullptr;
	std::vector<std::vector<Object*>> matrix;

	Empiness *mainEmpines;

public:
	Environment(int width = 100, int height = 100);
	~Environment();

	void update();

	const Object& getByPos(sf::Vector2i);
	const Object& getByPos(int, int);

	const std::vector<std::vector<Object*>>& getMatrix();

};

