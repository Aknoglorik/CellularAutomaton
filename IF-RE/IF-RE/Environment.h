#pragma once

#include <SFML/System.hpp>

#include "Object.hpp"
#include "Cells.h"
#include "GeneticAlgorithm.h"
#include "consts.h"

_INC_OBJ_MATRIX

class Environment
{
	int _width;
	int _height;

	GeneticAlgorithm* genAlg = nullptr;
	obj_matrix matrix;

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
	int getHeight() { return _height; }

	void moveCell(int);
	void eatCell(int);
	const obj_matrix& getMatrix();

};

