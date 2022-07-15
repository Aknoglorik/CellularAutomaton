#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "TileMap.h"


class MapCreator 
{
public:
    MapCreator();
    ~MapCreator();


private:
    sf::Texture floor_tileset;
    sf::Texture wall_tileset;

    TileMap map;

    void initLevel();


public:
    void update();
    const TileMap& getMap();

    void change_by_pos(sf::Vector2f pos);

};

