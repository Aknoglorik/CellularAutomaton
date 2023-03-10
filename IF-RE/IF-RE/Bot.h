#pragma once
#include "Object.hpp"

// Bioligical unit.
class Bot : public Object
{
	inline static const int type = cellType::Bot;

public:
	virtual int getType() { return type; };

	void update() override {};

	void move();
	void eat();
};
