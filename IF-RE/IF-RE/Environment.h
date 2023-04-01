#pragma once

#include <SFML/System.hpp>
#include <list>

#include "Object.hpp"
#include "Cells.h"
#include "GeneticAlgorithm.h"
#include "consts.h"

_INC_OBJP_MATRIX
_INC_FLOAT_MATRIX

class GeneticAlgorithm;

class Environment
{
	int _width;
	int _height;
	int _temp = 0;

	GeneticAlgorithm* genAlg = nullptr;
	objp_matrix matrix;

	// bots
	std::list<Bot*> all_bots;
	std::list<Bot*> active_bots;

	Emptiness *mainEmptiness = nullptr;
	Object *currentObj = nullptr;
	
	bool pause = false;
	
	// temprature
	float_matrix temp;

public:
	int gen_step = 0;
	int gen_generation = 0;

	Environment(int width = 100, int height = 100);
	~Environment();

	friend GeneticAlgorithm;

	void clear();

	void update();
	sf::Vector2i generatePosition();

	Object* getByPos(sf::Vector2i);
	Object* getByPos(int, int);
	int getHeight() { return _height; }
	const objp_matrix& getMatrix() { return matrix; }
	const float_matrix& getTemperatureMatrix() { return temp; }
	int getGloabalTemp() { return _temp; }
	bool getPause() { return pause; }

	void setPause(bool flag) { pause = flag; }
	void setExtraTemp(int temp) { _temp += temp; }
	void setGlobalTemp(int temp) { _temp = temp; }

	// \return True if cell was moved else false
	bool moveCell(int);
	void eatCell(int);
	void gemmationCell(int);
	int lookAround(int);

	void saveWorld(std::string fname = "");
	void loadWorld(std::string fname);
};

