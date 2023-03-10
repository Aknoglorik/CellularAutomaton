#pragma once
#include "Object.hpp"


// ???
class Food : public Object
{
	inline static const int type = cellType::Food;

public:
	virtual int getType() { return type; };

	void update() override {};
};
