#pragma once
#include "Object.hpp"


// This class describe empty cell.
class Empiness : public Object
{
	inline static const sf::String name = "Empiness";
};

// Bioligical unit.
class Bot : public Object
{
	// Brain
	// other properties
	// like a color, hp
	inline static const sf::String name = "Bot";
};

// ???
class Food : public Object
{
	inline static const sf::String name = "Food";
};


// Remains afte bot's death
class Corpse : public Object
{
	inline static const sf::String name = "Corpse";
};
