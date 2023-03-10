#pragma once
#include "Object.hpp"


// This class describe empty cell.
class Empiness : public Object
{
	inline static const int type = cellType::Empiness;

public:
	virtual int getType() { return type; };

	void update() override {};
};

