#include "Pawn.h"

Pawn::Pawn(sf::Texture p_skin, sf::Vector2f position, Weapon* gun, float move_speed, float heal_points)
{
	texture = p_skin;
	pos = position;

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

	last_released = 'r';

	this->gun = gun;

	this->gun->setPosition(getCenterPos());
}

Pawn::~Pawn()
{
	delete gun;
}

bool Pawn::isAlive()
{
	return (hp > 0.f);
}

bool Pawn::isRun()
{
	return up || left || down || right;
}

sf::Vector2f Pawn::getCenterPos()
{
	sf::IntRect rect = skin.getTextureRect();
	sf::Vector2f scale = skin.getScale();
	sf::Vector2f center = sf::Vector2f(abs(rect.width) * scale.x, rect.height * scale.y) / 2.f;
	return pos + center;
}

sf::Vector2f Pawn::getPos()
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

	if (!flag)
		last_released = 'u';
}

void Pawn::moveLeft(bool flag)
{
	left = flag;

	if (!flag)
		last_released = 'l';
}

void Pawn::moveDown(bool flag)
{
	down = flag;

	if (!flag)
		last_released = 'd';
}

void Pawn::moveRight(bool flag)
{
	right = flag;

	if (!flag)
		last_released = 'r';
}

void Pawn::attack()
{
	gun->attack(true);
}

void Pawn::update(sf::Vector2f MP_reletative_pl, float dt)
{
	time += 10*dt;

	if (time > 6)
		time -= 6;

	sf::Vector2f move((float)(right - left), (float)(down - up));
	
	float lenght = sqrtf(powf(move.x, 2) + powf(move.y, 2));
	
	if (lenght > 0.1f)
		move *= speed * dt / lenght;

	// move update
	int height = 1;
	if (up && !down)
		height = 2;
	else if (down)
		height = 0;

	// stay sheet
	if ((!left && !right || !(left - right)) && (!up && !down || !(up - down)))
		height = 3;

	// save dir
	bool s_left = false;
	if (!isRun()) // FIXME! Add more stay_sheets
		switch (last_released)
		{
		case 'u':
			break;
		case 'l':
			s_left = true;
			break;
		case 'd':
			break;
		case 'r':
			break;
		}

	skin.setTextureRect(sf::IntRect(16 * int(time) + 16*(left || s_left), 16 * height, (s_left || left) ? -16 : 16, 16));

	gun->update(MP_reletative_pl, dt);


	gun->move(move);
	pos += move;
	skin.move(move);
}

void Pawn::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (!up || (up && down))
	{
		target.draw(skin, states);
		target.draw(*gun, states);
	}
	else if (up)
	{
		target.draw(*gun, states);
		target.draw(skin, states);
	}
}
