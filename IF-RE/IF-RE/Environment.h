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
	int global_temp = 0;
	int global_light = 0;

	GeneticAlgorithm* genAlg = nullptr;
	objp_matrix matrix;

	// bots
	std::list<Bot*> all_bots;
	std::list<Bot*> active_bots;

	Emptiness *mainEmptiness = nullptr;
	Object *currentObj = nullptr;
	
	bool pause = false;
	
	// env props
	float_matrix temp;
	float_matrix hiden_temp;
	float_matrix light;

public:
	int gen_step = 0;
	int gen_generation = 0;

	Environment(int width = 100, int height = 100);
	~Environment();

	friend GeneticAlgorithm;

	void clear();

	void update();
	void tempUpdate();
	void lightUpdate();
	void cellsUpdate();
	void foodUpdate();

	sf::Vector2i generatePosition();

	Object* getByPos(sf::Vector2i);
	Object* getByPos(int, int);
	int getHeight() { return _height; }
	const objp_matrix& getMatrix() { return matrix; }
	const float_matrix& getTemperatureMatrix() { return temp; }
	const float_matrix& getLightMatrix() { return light; }
	int getGloabalTemp() { return global_temp; }
	int getGloaballight() { return global_light; }
	bool getPause() { return pause; }

	void setPause(bool flag) { pause = flag; }
	void setExtraTemp(int temp) { global_temp += temp; if (global_light < 0) global_light = 0; }
	void setExtraLight(int light) { global_light += light; }
	void setGlobalTemp(int temp) { global_temp = temp; }

	// \return True if cell was moved else false
	bool moveCell(int);
	void eatCell(int);
	void gemmationCell(int);
	int lookAround(int);

	void localReduceTemp(sf::Vector2i pos, int val) { temp[pos.x][pos.y] -= val; }

	void saveWorld(std::string fname = "");
	void loadWorld(std::string fname);
};

