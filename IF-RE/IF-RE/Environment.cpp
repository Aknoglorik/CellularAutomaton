#include "Environment.h"
#include <iostream>

Environment::Environment(int width, int height) : 
	_width(width), _height(height)
{
	mainEmpines = new Empiness;
	
	// Creating & filling matrix
	matrix.resize(_width);
	for (int i = 0; i < _width; i++)
	{
		matrix[i].resize(_height);
		for (int j = 0; j < _height; j++)
		{
			matrix[i][j] = mainEmpines;
			if (i == 10 && j == 40)
			{
				matrix[i][j] = new Bot(this, sf::Vector2i(i, j));
			}
		}
	}
}

Environment::~Environment()
{
}

void Environment::update()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			currentObj = matrix[i][j];

			if (currentObj->isDie())
			{
				delete currentObj; // free mem
				currentObj = mainEmpines;
				matrix[i][j] = mainEmpines;
				continue;
			}

			if (currentObj->getType() != cellType::Empiness)
				currentObj->update();
		}
	}
}

void Environment::moveCell()
{
	sf::Vector2i oldPos = currentObj->getPos();
	sf::Vector2i newPos = oldPos + sf::Vector2i(0, 1);

	if (newPos.y >= _height)
		newPos.y -= _height;


	if (matrix[newPos.y][newPos.x]->getType() == cellType::Empiness)
	{
		currentObj->setPos(newPos);
		matrix[newPos.x][newPos.y] = currentObj;
		matrix[oldPos.x][oldPos.y] = mainEmpines;

	}
}

const std::vector<std::vector<Object*>>& Environment::getMatrix()
{
	return matrix;
}
