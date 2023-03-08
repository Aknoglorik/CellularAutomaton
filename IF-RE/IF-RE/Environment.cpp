#include "Environment.h"

Environment::Environment(int width, int height) : 
	_width(width), _height(height)
{
	mainEmpines = new Empiness;
	
	// Creating & filling matrix
	matrix.resize(_height);
	for (int i = 0; i < _height; i++)
	{
		matrix[i].resize(_width);
		for (int j = 0; j < _width; j++)
			matrix[i][j] = mainEmpines;
	}
}

Environment::~Environment()
{
}

void Environment::update()
{
	for (auto row : matrix)
	{
		for (auto cell : row)
		{
			//if (cell->name != sf::String("Empiness"))
				//cell->update();
		}
	}
}

const std::vector<std::vector<Object*>>& Environment::getMatrix()
{
	return matrix;
}
