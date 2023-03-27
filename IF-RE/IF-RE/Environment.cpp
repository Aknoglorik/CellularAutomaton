#include "Environment.h"
#include <fstream>
#include <string>
#include <iostream>

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

/// \brief Check if position in of Rect(0, 0, width, height) and correct pos if necassary
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

//int lookAround(int dir)
//{
//	Vector2i oldPos = currentObj->getPos();
//	Vector2i newPos = oldPos + vecByInt(dir);
//	if (checkPos(newPos, _width, _height) == true)
//		return 1;
//	if (matrix[newPos.x][newPos.y]->getType() == cellType::Emptiness)
//		return 2;
//	else if (matrix[newPos.x][newPos.y]->getType() == cellType::Food)
//		return 3;
//	else if (matrix[newPos.x][newPos.y]->getType() == cellType::Bot)
//		return 4;
//	else
//		return 5;
//}

Environment::Environment(int width, int height) : 
	_width(width), _height(height)
{
	genAlg = new GeneticAlgorithm;

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
			temp[i][j] = 3;// (height / 2 - 2 * j > 0) ? height / 2 - 2 * j : 0;
			
			//if (j == 0 || j == _height - 1)//i == 10)
			{
				matrix[i][j] = new Bot(this, Vector2i(i, j));
			}
		}
	}
}

Environment::~Environment()
{
	delete genAlg;
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[0].size(); j++)
			if (matrix[i][j]->getType())
				delete matrix[i][j];

	delete mainEmptiness;

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
			}
		}
	}
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			currentObj = matrix[i][j];
			if (currentObj->getType() != cellType::Emptiness)
				currentObj->update();
		}
	}
	generateFood();
	gen_step++;
}

void Environment::generateFood()
{
	if (Food::amount >= FOOD_AMOUNT) // REDO!
		return;

	bool flag = false;

	for (int i = 0; i < _width; i++)
		for (int j = 0; j < _height; j++)
			if (matrix[i][j]->getType() == cellType::Emptiness)
			{
				flag = true;
				break;
			}

	if (!flag)
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

	if (matrix[newPos.x][newPos.y]->getType() == cellType::Bot && currentObj->getType() == cellType::Bot)
	{
		matrix[newPos.x][newPos.y]->setIsDie(true);

		currentObj->addEnergy(matrix[newPos.x][newPos.y]->getEnergy() * BOT_EAT_RATIO);

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
		if ((!checkPos(newPos, _width, _height)) && (matrix[newPos.x][newPos.y]->getType() == cellType::Emptiness))
		{
			currentObj->setEnergy(currentObj->getEnergy() / 2);
			auto upCastObj = (Bot*)currentObj;

			matrix[newPos.x][newPos.y] = genAlg->mutation(upCastObj);
			matrix[newPos.x][newPos.y]->setPos(newPos);

			return;
		}
	}	
}

void Environment::saveWorld(std::string fname)
{
	std::ofstream out(fname);

	if (!out.is_open())
	{
		std::cout << "Not found file!" << std::endl;
		return;
	}

	out << _width << ' ' << _height << ' ' << this->_temp << '\n';

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			int type = matrix[i][j]->getType();

			out << type << ' ';
			if (type == cellType::Bot)
			{
				// save props
				auto bot = (Bot*)matrix[i][j];
				out << bot->cmd_counter << ' ' << bot->dir_move << ' ' << bot->dir_sight << ' ' << bot->spriteType << ' ' 
					<< bot->life_counter << ' ' << bot->digest_speed << ' ' << bot->digested_material << ' ';

				// save brain
				out << bot->brain.size() << ' ';
				for (int i = 0; i < bot->brain.size(); i++)
					out << bot->brain[i] << ' ';
			}
			out << matrix[i][j]->getEnergy() << ' ' << matrix[i][j]->isDie() << ' ' << temp[i][j] << ' ';
		}
		out << '\n';
	}
	out.close();
}

void Environment::loadWorld(std::string fname)
{
	std::ifstream in(fname);

	if (!in.is_open())
	{
		std::cout << "Not found file!" << std::endl;
		return;
	}

	in >> _width >> _height >> _temp;

	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[0].size(); j++)
			if (matrix[i][j]->getType())
				delete matrix[i][j];
	
	matrix.resize(_width);
	temp.resize(_width);
	for (int i = 0; i < _width; i++)
	{
		matrix[i].resize(_height);
		temp[i].resize(_height);
		for (int j = 0; j < _height; j++)
		{
			matrix[i][j] = mainEmptiness;
		}
	}

	int type;
	int size;
	unsigned int energy;
	bool is_die;
	std::vector<int> brain;
	int cmd_counter, dir_move, dir_sight, spriteType, life_counter, digest_speed, digested_material;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			in >> type;
			if (type == cellType::Bot)
			{
				in >> cmd_counter >> dir_move >> dir_sight >> spriteType >> life_counter >> digest_speed >> digested_material;
				in >> size;
				brain.resize(size);

				for (int i = 0; i < brain.size(); i++)
					in >> brain[i];
			}
			in >> energy >> is_die >> temp[i][j];

			switch (type)
			{
			case cellType::Bot:
			{
				// copy stats
				auto newBot = new Bot(this, sf::Vector2i(i, j), energy, &brain);
				newBot->setIsDie(is_die);
				newBot->cmd_counter			= cmd_counter;
				newBot->dir_move			= dir_move;
				newBot->dir_sight			= dir_sight;
				newBot->spriteType			= spriteType;
				newBot->life_counter		= life_counter;
				newBot->digest_speed		= digest_speed;
				newBot->digested_material	= digested_material;

				matrix[i][j] = newBot;
				break;
			}
			case cellType::Food:
			{
				matrix[i][j] = new Food;
				matrix[i][j]->setPos(i, j);
				break;
			}
			case cellType::Emptiness:
			case cellType::Corpse:
			default:
				break;
			}
		}
	}

	in.close();
}
