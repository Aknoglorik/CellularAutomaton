#pragma once
#include <SFML/Graphics.hpp>
#include "consts.h"


class Camera
{
public:
	Camera(sf::View& cam) : camera(cam) {}
	
	void moveUp(bool flag)
	{
		up = flag;
	}

	void moveLeft(bool flag)
	{
		left = flag;
	}

	void moveDown(bool flag)
	{
		down = flag;
	}

	void moveRight(bool flag)
	{
		right = flag;
	}

	void move() 
	{
		sf::Vector2f offset((float)(right - left), (float)(down - up));
		offset *= speed;

		camera.move(offset);
	}

	sf::View& camera;

	float speed = VIEW_SPEED;
	bool up		= false, 
		 left	= false, 
		 down	= false, 
		 right	= false;
};

