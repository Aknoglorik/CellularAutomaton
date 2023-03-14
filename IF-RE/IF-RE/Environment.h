#pragma once

#include <SFML/System.hpp>

#include "Object.hpp"
#include "Cells.h"
#include "GeneticAlgorithm.h"

namespace BotMove
{
	enum
	{
		up,
		up_right,
		right,
		down_right,
		down,
		down_left,
		left,
		up_left
	};
}


class Environment
{
	int _width;
	int _height;

	GeneticAlgorithm* genAlg = nullptr;
	std::vector<std::vector<Object*>> matrix;

	Emptiness *mainEmptiness = nullptr;
	Object *currentObj = nullptr;

public:
	int gen_step = 0;

	Environment(int width = 100, int height = 100);
	~Environment();

	void update();
	void generateFood();

	Object* getByPos(sf::Vector2i);
	Object* getByPos(int, int);

	void moveCell(int);

	const std::vector<std::vector<Object*>>& getMatrix();

};

