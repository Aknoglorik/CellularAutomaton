#pragma once
#include "Object.hpp"


class Bot;

// Remains afte bot's death
class Corpse : public Object
{
	inline static const int type = cellType::Corpse;

public:
	Corpse(Environment* _env, Bot*);
	virtual int getType() { return type; }

	void update() override;
};
