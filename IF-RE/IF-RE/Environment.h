#pragma once

#include <SFML/System.hpp>

#include "Object.hpp"
#include "Cells.h"
#include "GeneticAlgorithm.h"
#include "consts.h"

_INC_OBJP_MATRIX
_INC_INT_MATRIX

class Environment
{
	int _width;
	int _height;
	int _temp = 0;

	GeneticAlgorithm* genAlg = nullptr;
	objp_matrix matrix;

	Emptiness *mainEmptiness = nullptr;
	Object *currentObj = nullptr;
	
	bool pause = false;
	
	// temprature
	int_matrix temp;

public:
	int gen_step = 0;

	Environment(int width = 100, int height = 100);
	~Environment();

	void update();
	void generateFood();

	Object* getByPos(sf::Vector2i);
	Object* getByPos(int, int);
	int getHeight() { return _height; }
	const objp_matrix& getMatrix() { return matrix; }
	const int_matrix& getTemperatureMatrix() { return temp; }
	int getGloabalTemp() { return _temp; }
	bool getPause() { return pause; }

	void setPause(bool flag) { pause = flag; }
	void setExtraTemp(int temp) { _temp += temp; }
	void setGlobalTemp(int temp) { _temp = temp; }

	void moveCell(int);
	void eatCell(int);
	void gemmationCell(int);

	void saveWorld(std::string fname = "");
	void loadWorld(std::string fname);
};

