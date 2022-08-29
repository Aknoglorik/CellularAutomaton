#include "Weapon.h"
#include <iostream>

Weapon::Weapon(sf::Texture texture)
{
	setPosition(0.f, 0.f);
	time = 0;

	isMelee = true;
	isAttack = false;

	// weapon propertes
	dmg = 10.f;
	attack_speed = 10.f;
	range = 10.f;
	armour_penetration = 10.f;

	// RangeWeapon propertes
	holder_size = 10.f;
	reload_time = 10.f;
	distance_damage = 10.f;

	// class fields

	this->texture = texture;
	skin.setTexture(this->texture);
	setOrigin(sf::Vector2f(0.f, 64.f));
	rotate(45);

	skin.scale(4.f, 4.f);
	skin.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

Weapon::~Weapon()
{
}

void Weapon::isInHand(bool flag)
{
	isActive = flag;
}

void Weapon::attack(bool flag)
{
	isAttack = flag;
}

void Weapon::setAngle(float angle)
{
}

sf::Vector2f Weapon::getCenterPos()
{
	sf::IntRect rect = skin.getTextureRect();
	sf::Vector2f scale = skin.getScale();
	sf::Vector2f center = sf::Vector2f(abs(rect.width) * scale.x, rect.height * scale.y) / 2.f;
	return getPosition() + center;
}


void Weapon::update(sf::Vector2f mouse_pos, float dt)
{

	if (isAttack)
	{
		time += 10 * dt;
		rotate(1);
	}

	if (time > 1)
	{
		isAttack = false;
		time -= 1;
	}

	if (!isAttack)
	{
		float angle = atan2f(mouse_pos.y, mouse_pos.x) * 180 / 3.14159 + 45;
		setRotation(angle);
	}

	skin.setTextureRect(sf::IntRect(0, 0, 16, 16));

}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(skin, states);
}
