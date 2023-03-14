#pragma once
#include "Object.hpp"


// This class describe empty cell.
class Emptiness : public Object
{
	inline static const int type = cellType::Emptiness;

public:
	virtual int getType() { return type; };

	void update() override {};
};

