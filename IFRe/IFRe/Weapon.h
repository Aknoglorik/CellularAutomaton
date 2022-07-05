#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Weapon
{
public:
	Weapon();
	~Weapon();


private:
	sf::Texture texture;
	sf::Sprite skin;

	float dmg;
	float distance_damage;
	float holder_size;
	float reload_time;
	float bullet_per_sec;
	float range;
	float armour_penetration;


public:


};

