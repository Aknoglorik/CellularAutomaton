#pragma once
#include "Object.hpp"



// Remains afte bot's death
class Corpse : public Object
{
	inline static const int type = cellType::Corpse;

public:
	virtual int getType() { return type; };

	void update() override {};
};
