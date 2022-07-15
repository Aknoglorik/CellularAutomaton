#include "MapCreator.h"

MapCreator::MapCreator()
{
	initLevel();


    
}

MapCreator::~MapCreator()
{
}

void MapCreator::initLevel()
{
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 9, 9, 9, 9, 9, 9, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 4, 9, 9, 9, 9, 9, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 9, 9, 9, 9, 9, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 9, 9, 9, 9, 9, 2, 0, 
        2, 0, 1, 0, 3, 0, 2, 2, 2, 9, 9, 9, 9, 9, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 9, 9, 9, 9, 9, 1, 1,
    };

    map.load("resources/img/floor.png", sf::Vector2u(16, 16), level, 16, 8);
    map.scale(2.f, 2.f);
}


void MapCreator::update()
{

}

const TileMap& MapCreator::getMap()
{
    return map;
}

void MapCreator::change_by_pos(sf::Vector2f pos)
{
    return;
}
