#pragma once

#include "Weapon.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

class Pawn : public sf::Drawable, public sf::Transformable
{
public:
	Pawn(sf::Texture p_skin, sf::Vector2f position, Weapon* gun, float speed=10.f, float hp=100.f);
	~Pawn();


private:
	sf::Texture texture;
	sf::Sprite skin;

	sf::Vector2f pos;
	Weapon* gun;
	float speed;
	float hp;

	float time;

	bool up;
	bool left;
	bool right;
	bool down;

	char last_released;


public:
	bool isAlive();
	bool isRun();

	sf::Vector2f getPos();
	sf::Vector2f getCenterPos();
	void setPos(sf::Vector2f pos);

	void moveUp(bool flag);
	void moveLeft(bool flag);
	void moveDown(bool flag);
	void moveRight(bool flag);

	void attack();

	void update(sf::Vector2f mouse_position, float delta_time = 0.01);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
