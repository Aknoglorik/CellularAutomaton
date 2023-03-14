#pragma once

#include <SFML/System.hpp>

#include "Object.hpp"
#include "Cells.h"
#include "GeneticAlgorithm.h"


class Environment
{
	int _width;
	int _height;

	GeneticAlgorithm* genAlg = nullptr;
	std::vector<std::vector<Object*>> matrix;

	Emptiness *mainEmpines = nullptr;
	Object *currentObj = nullptr;

public:
	int gen_step = 0;

	Environment(int width = 100, int height = 100);
	~Environment();

	void update();
	void generateFood();

	Object* getByPos(sf::Vector2i);
	Object* getByPos(int, int);

	int getNextMove();
	void moveCell();

	const std::vector<std::vector<Object*>>& getMatrix();

};

