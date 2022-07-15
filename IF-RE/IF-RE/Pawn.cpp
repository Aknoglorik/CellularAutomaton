#include "Pawn.h"


Pawn::Pawn(sf::Texture p_skin, sf::Vector2f position, Weapon gun, float move_speed, float heal_points)
{
	pos = position;

	texture = p_skin;

	skin.setTexture(texture);
	skin.setPosition(pos);

	skin.scale(8.f, 8.f);
	skin.setTextureRect(sf::IntRect(0, 0, 16, 16));

	time = 0;

	speed = move_speed;
	hp = heal_points;

	up = false;
	left = false;
	down = false;
	right = false;
}

Pawn::~Pawn()
{
}

bool Pawn::isAlive()
{
	return (hp > 0.f);
}

bool Pawn::isRun()
{
	return up || left || down || right;
}

sf::Vector2<float> Pawn::getPos()
{
	return pos;
}

void Pawn::setPos(sf::Vector2f pos)
{
	this->pos = pos;
}

void Pawn::moveUp(bool flag)
{
	up = flag;
}

void Pawn::moveLeft(bool flag)
{
	left = flag;
}

void Pawn::moveDown(bool flag)
{
	down = flag;
}

void Pawn::moveRight(bool flag)
{
	right = flag;
}

void Pawn::update(float dt)
{
	if (isRun())
		time += 10*dt;
	
	if (time > 6)
		time -= 6;

	sf::Vector2f move((float)(right - left), (float)(down - up));
	
	float lenght = sqrtf(powf(move.x, 2) + powf(move.y, 2));
	
	if (lenght > 0.1f)
		move *= speed * dt / lenght;

	skin.setTextureRect(sf::IntRect(16*int(time), 0, 16, 16));

	pos += move;
	skin.move(move);
}

sf::Sprite& Pawn::getDrawable()
{
	return skin;
}
