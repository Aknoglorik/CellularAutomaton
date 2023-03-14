#include "Environment.h"
#include <iostream>

Environment::Environment(int width, int height) : 
	_width(width), _height(height)
{
	mainEmptiness = new Emptiness;
	
	// Creating & filling matrix
	matrix.resize(_width);
	for (int i = 0; i < _width; i++)
	{
		matrix[i].resize(_height);
		for (int j = 0; j < _height; j++)
		{
			matrix[i][j] = mainEmptiness;
			if (i == 10 && j == 10)
			{
				matrix[i][j] = new Bot(this, sf::Vector2i(i, j));
			}
			if (i == 10 && j == 5)
			{
				matrix[i][j] = new Food;
				matrix[i][j]->setPos(sf::Vector2i(i, j));
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
				currentObj = mainEmptiness;
				matrix[i][j] = mainEmptiness;
				continue;
			}

			if (currentObj->getType() != cellType::Emptiness)
				currentObj->update();
		}
	}
	generateFood();
	gen_step++;
}

void Environment::generateFood()
{
	if (Food::amount > 10) // REDO!
		return;
	int x, y;
	do
	{
		x = rand() % _width;
		y = rand() % _height;
	}
	while (getByPos(x, y)->getType() != cellType::Emptiness); // REDO! there is no logic to check if field is filled in

	matrix[x][y] = new Food;
	matrix[x][y]->setPos(x, y);
}

Object* Environment::getByPos(sf::Vector2i pos)
{
	return matrix[pos.x][pos.y];
}

Object* Environment::getByPos(int x, int y)
{
	return matrix[x][y];
}

void Environment::moveCell(int dir)
{
	//Moved
	sf::Vector2i oldPos = currentObj->getPos();
	sf::Vector2i newPos = oldPos;
	switch (dir) {
	case BotMove::up:
		//up
		newPos += sf::Vector2i(0, -1);
		break;
	case BotMove::up_right:
		//up+right
		newPos += sf::Vector2i(1, -1);
		break;
	case BotMove::right:
		//right
		newPos += sf::Vector2i(1, 0);
		break;
	case BotMove::down_right:
		//down + rihgt
		newPos += sf::Vector2i(1, 1);
		break;
	case BotMove::down:
		//down
		newPos += sf::Vector2i(0, 1);
		break;
	case BotMove::down_left:
		//down+left
		newPos += sf::Vector2i(-1, 1);
		break;
	case BotMove::left:
		//left
		newPos += sf::Vector2i(-1, 0);
		break;
	case BotMove::up_left:
		//up
		newPos += sf::Vector2i(-1, -1);
		break;
	default: 
		break;
	}
	/*if (newPos.y != 5)
	{
		 newPos += sf::Vector2i(0, 1);
	}
	else 
	{
		newPos += sf::Vector2i(1, 0);
	}*/
	if (newPos.y >= _height)
		newPos.y = _height - 1;

	if (newPos.y < 0)
		newPos.y = 0;

	if (newPos.x >= _width)
		newPos.x = 0;

	if (newPos.x < 0)
		newPos.x = _width - 1;

	

	// very bad code
	// mb redo to switch()
	if (currentObj->getType() == cellType::Bot && matrix[newPos.x][newPos.y]->getType() == cellType::Food)
	{
		currentObj->setPos(newPos);

		currentObj->addEnergy(matrix[newPos.x][newPos.y]->getEnergy());
		delete matrix[newPos.x][newPos.y];

		matrix[newPos.x][newPos.y] = currentObj;
		matrix[oldPos.x][oldPos.y] = mainEmptiness;
	}
	else if (!matrix[newPos.x][newPos.y]->getType()) // cellType::Emptiness = 0
	{
		currentObj->setPos(newPos);
		matrix[newPos.x][newPos.y] = currentObj;
		matrix[oldPos.x][oldPos.y] = mainEmptiness;
	}
}

const std::vector<std::vector<Object*>>& Environment::getMatrix()
{
	return matrix;
}
