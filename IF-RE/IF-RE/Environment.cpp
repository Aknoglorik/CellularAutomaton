#include "Environment.h"


_INC_OBJP_MATRIX


using sf::Vector2i; // work only in this cpp

/// \brief Function return vector2i by botMove direction (0-7)
/// \brief 0 - up, 1 - up-right, 2 - right ...  
Vector2i vecByInt(int dir)
{
	Vector2i v_dir(0, 0);
	// vertical
	switch (dir)
	{
	case botMove::up:
	case botMove::up_right:
	case botMove::up_left:
		v_dir += DIR_UP;
		break;
	case botMove::down:
	case botMove::down_right:
	case botMove::down_left:
		v_dir += DIR_DOWN;
		break;
	default:
		break;
	}
	// horizontal
	switch (dir)
	{
	case botMove::right:
	case botMove::up_right:
	case botMove::down_right:
		v_dir += DIR_RIGHT;
		break;
	case botMove::left:
	case botMove::up_left:
	case botMove::down_left:
		v_dir += DIR_LEFT;
		break;
	default:
		break;
	}
	return v_dir;
}

/// \brief Check if position out of Rect(0, 0, width, height) and correct pos if necassary
/// \param pos - checkable position
/// \param width, height - properties of a Rect
/// \return True - if correct in the vertical is nesaccary else false
bool checkPos(Vector2i& pos, int width, int height)
{
	bool vert_corr = false;
	if (pos.y >= height)
	{
		pos.y = height - 1;
		vert_corr = true;
	}

	if (pos.y < 0)
	{
		pos.y = 0;
		vert_corr = true;
	}

	if (pos.x >= width)
		pos.x = 0;

	if (pos.x < 0)
		pos.x = width - 1;

	return vert_corr;
}

Environment::Environment(int width, int height) : 
	_width(width), _height(height)
{
	mainEmptiness = new Emptiness;
	
	// Creating & filling matrix
	matrix.resize(_width);
	temp.resize(_width);
	for (int i = 0; i < _width; i++)
	{
		matrix[i].resize(_height);
		temp[i].resize(_height);
		for (int j = 0; j < _height; j++)
		{
			matrix[i][j] = mainEmptiness;
			temp[i][j] = _height / (2*j + 10);

			if (j == 0 || j == _height - 1)//i == 10)
			{
				matrix[i][j] = new Bot(this, Vector2i(i, j));
			}
			if (i == 10 && j == 5)
			{
				matrix[i][j] = new Food;
				matrix[i][j]->setPos(Vector2i(i, j));
			}
		}
	}
}

Environment::~Environment()
{
}

void Environment::update()
{
	if (pause)
		return;

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
	if (Food::amount > FOOD_AMOUNT) // REDO!
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

Object* Environment::getByPos(Vector2i pos)
{
	return matrix[pos.x][pos.y];
}

Object* Environment::getByPos(int x, int y)
{
	return matrix[x][y];
}

void Environment::setExtraTemp(int extra_temperature)
{
	for (int i = 0; i < _width; i++)
		for (int j = 0; j < _height; j++)
			temp[i][j] += extra_temperature;

}

void Environment::moveCell(int dir_move)
{
	Vector2i oldPos = currentObj->getPos();
	Vector2i newPos = oldPos + vecByInt(dir_move);

	checkPos(newPos, _width, _height);

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


/// \brief Method allow cell to eat other in the direction of view
/// 
/// \param dir - cell view direction
void Environment::eatCell(int dir)
{
	Vector2i oldPos = currentObj->getPos();
	Vector2i newPos = oldPos + vecByInt(dir);

	if (checkPos(newPos, _width, _height)) // True mean y of newPos was corrected, that is mean bot look at the wall
		return;

	if (matrix[newPos.x][newPos.y]->getType() == cellType::Bot)
	{
		matrix[newPos.x][newPos.y]->setIsDie(true);

		currentObj->addEnergy(matrix[newPos.x][newPos.y]->getEnergy());

		// REDO! (DRY dont executed mb)
		delete matrix[newPos.x][newPos.y]; // free mem
		matrix[newPos.x][newPos.y] = mainEmptiness;
	}
}

void Environment::gemmationCell(int dir)
{
	int dir_gem = (dir + 4) % 8;
	Vector2i oldPos = currentObj->getPos();
	Vector2i newPos = oldPos + vecByInt(dir_gem);

	for(int i = 0; i < 8; i++)
	{
		dir_gem = (dir_gem + i) % 8;
		newPos = oldPos + vecByInt(dir_gem);
		if ((!checkPos(newPos, _width, _height)) && 
			(matrix[newPos.x][newPos.y]->getType() == cellType::Emptiness))
		{
			currentObj->setEnergy(currentObj->getEnergy() / 2);
			auto upCastObj = (Bot*)currentObj;
			matrix[newPos.x][newPos.y] = new Bot(this, newPos, 
				currentObj->getEnergy(), upCastObj->getPBrain());
			return;
		}
	}	
}

const objp_matrix& Environment::getMatrix()
{
	return matrix;
}
