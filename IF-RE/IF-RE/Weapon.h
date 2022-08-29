#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>



class Weapon : public sf::Drawable, public sf::Transformable
{
public:
	Weapon(sf::Texture texture);
	~Weapon();


private:
	sf::Texture texture;
	sf::Sprite skin;

	bool isMelee;
	bool isActive;
	bool isAttack;

	float time;

	float dmg;
	float distance_damage;
	float holder_size;
	float reload_time;
	float attack_speed;
	float range;
	float armour_penetration;


public:
	void isInHand(bool flag);
	void attack(bool flag);
	
	void setAngle(float angle);
	sf::Vector2f getCenterPos();

	void update(sf::Vector2f mouse_pos, float deltatime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

