#pragma once
#include "Object.hpp"


// This class describe empty cell.
class Empiness : public Object
{
	inline static const int type = cellType::Empiness;

public:
	virtual int getType() { return type; };
};

// Bioligical unit.
class Bot : public Object
{
	// Brain
	// other properties
	// like a color, hp
	inline static const int type = cellType::Bot;

public:
	virtual int getType() { return type; };
};

// ???
class Food : public Object
{
	inline static const int type = cellType::Food;

public:
	virtual int getType() { return type; };
};


// Remains afte bot's death
class Corpse : public Object
{
	inline static const int type = cellType::Corpse;

public:
	virtual int getType() { return type; };
};
