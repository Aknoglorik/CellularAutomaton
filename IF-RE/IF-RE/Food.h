#pragma once
#include "Object.hpp"


// ???
class Food : public Object
{
	inline static const int type = cellType::Food;

public:
	inline static unsigned int amount = 0;
	Food() { energy = 10; amount++; }
	~Food() { amount--; }
	
	virtual int getType() { return type; };
};