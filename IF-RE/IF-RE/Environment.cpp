#include "Environment.h"
#include <fstream>
#include <string>
#include <functional>
#include <algorithm>
#include <random>
#include <iostream>

_INC_OBJP_MATRIX

extern int tempPenalti(float);

float deltaTempByLight(float light)
{
	if (light <= 30)
		return  0.5*(light - 10);
	return light / 256 + 10;
}

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


int Environment::lookAround(int dir)
{
	Vector2i oldPos = currentObj->getPos();
	Vector2i newPos = oldPos + vecByInt(dir);
	if (checkPos(newPos, _width, _height))
		return cellType::Wall;
	return matrix[newPos.x][newPos.y]->getType();
}

Environment::Environment(int width, int height) : 
	_width(width), _height(height)
{
	genAlg = new GeneticAlgorithm;
	pause = true;
	mainEmptiness = new Emptiness;

	// Creating & filling matrix
	matrix.resize(_width);
	temp.resize(_width);
	default_temp.resize(_width);
	hiden_temp.resize(_width);
	light.resize(_width);
	for (int i = 0; i < _width; i++)
	{
		matrix[i].resize(_height);
		temp[i].resize(_height);
		default_temp[i].resize(_height);
		hiden_temp[i].resize(_height);
		light[i].resize(_height);
		for (int j = 0; j < _height; j++)
		{
			matrix[i][j] = mainEmptiness;
			temp[i][j] = 3.f; (height / 2 - 2 * j > 0) ? 2 * height / 2 - 2 * j : 0;;
			default_temp[i][j] = temp[i][j];
			hiden_temp[i][j] = temp[i][j];
			light[i][j] = 10;//  (4 * height / 2 - 2 * j > 0) ? 4 * height / 2 - 2 * j : 0;
			if (!i && !j)
				global_light = light[0][0];
			//if (i == 7 && j == 4)
			{
				matrix[i][j] = new Bot(this, Vector2i(i, j));
				all_bots.push_back(dynamic_cast<Bot*>(matrix[i][j]));
				active_bots.push_back(dynamic_cast<Bot*>(matrix[i][j]));
			}
			if (global_light < light[i][j])
				global_light = light[i][j];
		}
	}

	for (int i = 0; i < _width; ++i)
		for (int j = 0; j < _height; ++j)
			light[i][j] -= global_light;
}

Environment::~Environment()
{
	delete genAlg;
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[0].size(); j++)
			if (matrix[i][j]->getType())
				delete matrix[i][j];

	all_bots.clear();
	delete mainEmptiness;

}

// \brief setup world for new bots (in all_bots)
void Environment::clear()
{
	gen_step = 0;
	gen_generation++;
	//pause = true;
	temp = default_temp;
	currentObj = nullptr;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (matrix[i][j]->getType() && matrix[i][j]->getType() != cellType::Bot) // cellType::Emptiness = 0
				delete matrix[i][j];
			matrix[i][j] = mainEmptiness;
		}
	}
	for (auto bot : all_bots)
	{
		auto b_pos = generatePosition();

		if (!(b_pos.x + 1))
			throw std::exception("New population size too large.");

		bot->reSetup();
		bot->setPos(b_pos);
		matrix[b_pos.x][b_pos.y] = bot;
	}
}

void Environment::update()
{
	if (pause)
		return;
	cellsUpdate();
	foodUpdate();
	if (true || !(gen_step % ENV_FREQ_TEMP_UPDATE))
	{
		lightUpdate();
		tempUpdate();
	}

 	gen_step++;
}

void Environment::lightUpdate()
{
	for (int i = 0; i < _width; ++i)
	{
		for (int j = 0; j < _height; ++j)
		{
			temp[i][j] += deltaTempByLight(light[i][j] + global_light);
		}
	}
}

void Environment::tempUpdate()
{
	sf::Vector2i pos;
	std::vector<int> crawl_order = { 0, 1, 2, 3, 4, 5, 6, 7 };

	std::random_device rd;
	std::mt19937 prnd(rd());
	for (int i = 0; i < _width; ++i)
	{
		for (int j = 0; j < _height; ++j)
		{
			std::shuffle(crawl_order.begin(), crawl_order.end(), prnd);
			for (int dir : crawl_order)
			{
				pos = sf::Vector2i(i,j) + vecByInt(dir);

				if (checkPos(pos, _width, _height))
					continue;

				if (temp[pos.x][pos.y] < temp[i][j])
				{
					temp[i][j] -= ENV_HEAT_TRANSFER;
					temp[pos.x][pos.y] += ENV_HEAT_TRANSFER;
				}
			}
		}
	}
}

void Environment::cellsUpdate()
{
	std::list<Bot*>::iterator it = active_bots.begin();
	std::list<Bot*>::iterator it_to_del = it;

	for (; it != active_bots.end();)
	{
		it_to_del = it;
		++it;
		if ((*it_to_del)->isDie())
		{
			sf::Vector2i pos = (*it_to_del)->getPos();
			matrix[pos.x][pos.y] = new Corpse(this, *it_to_del);
			active_bots.erase(it_to_del);
		}
	}

	if (active_bots.size() <= genAlg->getOutSelection())
	{
		std::cout << active_bots.size() << std::endl;
		all_bots = genAlg->selection(all_bots);
		active_bots = all_bots;
		clear();
		return;
	}

	// Update movabel objs
	for (auto bot : active_bots)
	{
		currentObj = bot;
		currentObj->update();
	}
	// Update other objs
	for (int i = 0; i < _width; ++i)
	{
		for (int j = 0; j < _height; ++j)
		{
			currentObj = matrix[i][j];
			if (currentObj->getType() != cellType::Emptiness && currentObj->getType() != cellType::Bot)
			{
				currentObj->update();
				if (currentObj->isDie())
				{
					delete matrix[i][j];
					matrix[i][j] = mainEmptiness;
				}
			}
		}
	}
}

void Environment::foodUpdate()
{
	if (Food::amount < FOOD_AMOUNT)
	{
		sf::Vector2i food_pos = generatePosition();
		if ((bool)(food_pos.x + 1) && (tempPenalti(temp[food_pos.x][food_pos.y]) <= 3))
		{
			matrix[food_pos.x][food_pos.y] = new Food(this);
			matrix[food_pos.x][food_pos.y]->setPos(food_pos);
		}
	}
}

sf::Vector2i Environment::generatePosition()
{
	bool flag = false;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
			if (matrix[i][j]->getType() == cellType::Emptiness)
			{
				flag = true;
				break;
			}
		if (flag)
			break;
	}

	if (!flag)
		return sf::Vector2i(-1, -1);

	int x, y;
	do
	{
		x = rand() % _width;
		y = rand() % _height;
	} 
	while (matrix[x][y]->getType() != cellType::Emptiness);

	return sf::Vector2i(x, y);
}

Object* Environment::getByPos(Vector2i pos)
{
	return matrix[pos.x][pos.y];
}

Object* Environment::getByPos(int x, int y)
{
	return matrix[x][y];
}

bool Environment::moveCell(int dir_move)
{
	Vector2i oldPos = currentObj->getPos();
	Vector2i newPos = oldPos + vecByInt(dir_move);

	// True mean y of newPos was corrected, that is mean bot look at the wall
	if (checkPos(newPos, _width, _height))
		return false;

	if (currentObj->getType() == cellType::Bot && matrix[newPos.x][newPos.y]->getType() == cellType::Food)
	{
		currentObj->setPos(newPos);
	
		currentObj->addEnergy(matrix[newPos.x][newPos.y]->getEnergy());
		delete matrix[newPos.x][newPos.y];
	
		matrix[newPos.x][newPos.y] = currentObj;
		matrix[oldPos.x][oldPos.y] = mainEmptiness;
	}
	else if (currentObj->getType() == cellType::Bot && matrix[newPos.x][newPos.y]->getType() == cellType::Corpse)
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
	return true;
}

/// \brief Method allow cell to eat other in the direction of view
/// 
/// \param dir - cell view direction
void Environment::eatCell(int dir)
{
	Vector2i oldPos = currentObj->getPos();
	Vector2i newPos = oldPos + vecByInt(dir);

	// True mean y of newPos was corrected, that is mean bot look at the wall
	if (checkPos(newPos, _width, _height)) 
		return;
	
	if (!matrix[newPos.x][newPos.y]->isDie() && matrix[newPos.x][newPos.y]->getType() == cellType::Bot && currentObj->getType() == cellType::Bot)
	{
		matrix[newPos.x][newPos.y]->setIsDie(true);
		currentObj->addEnergy(matrix[newPos.x][newPos.y]->getEnergy() * BOT_EAT_RATIO);
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
			all_bots.push_back((Bot*)matrix[newPos.x][newPos.y]);
			active_bots.push_back((Bot*)matrix[newPos.x][newPos.y]);
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

	out << gen_generation << ' ' << gen_step << ' ' << _width << ' ' << _height << ' ' << this->global_temp << ' ' << global_light << '\n';

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
			out << matrix[i][j]->getEnergy() << ' ' << matrix[i][j]->isDie() << ' ' << temp[i][j] << ' ' << light[i][j] << ' ';
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

	in >> gen_generation >> gen_step >> _width >> _height >> global_temp >> global_light;

	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[0].size(); j++)
			if (matrix[i][j]->getType())
				delete matrix[i][j];
	all_bots.clear();
	active_bots.clear();

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
			in >> energy >> is_die >> temp[i][j] >> light[i][j];

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
				all_bots.push_back(newBot);
				active_bots.push_back(newBot);
				break;
			}
			case cellType::Food:
			{
				matrix[i][j] = new Food(this);
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
