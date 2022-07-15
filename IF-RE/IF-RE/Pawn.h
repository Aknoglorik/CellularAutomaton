#pragma once

#include "Weapon.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

class Pawn
{
public:
	Pawn(sf::Texture p_skin, sf::Vector2f position, Weapon gun, float speed=10.f, float hp=100.f);
	~Pawn();


private:
	sf::Texture texture;
	sf::Sprite skin;

	sf::Vector2f pos;
	Weapon gun;
	float speed;
	float hp;

	float time;

	bool up;
	bool left;
	bool right;
	bool down;


public:
	bool isAlive();
	bool isRun();

	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos);

	void moveUp(bool flag);
	void moveLeft(bool flag);
	void moveDown(bool flag);
	void moveRight(bool flag);

	void update(float delta_time = 0.01);
	sf::Sprite& getDrawable();
};
