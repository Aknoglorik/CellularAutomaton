#ifndef __APP__
#define __APP__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Pawn.h"
#include "MapCreator.h"


class App
{
public:
	App(unsigned int width = 640, unsigned int height = 480, std::string wname = "SFML 2.5.1");
	~App();


private:
	sf::VideoMode VM;
	sf::RenderWindow root;
	sf::Event event_;

	sf::Clock clock;
	sf::View view;

	float current_zoom;

	float FPS;
	bool gameEnd;
	sf::Font PxlFont;
	
	MapCreator map_creator;

	void initWindow(unsigned int width, unsigned int height, std::string wname);
	void initVariables();
	void initPlayer();

	Pawn *player;

public:
	bool isOpen();
	bool isGameEnd();
	
	void pollEvent();
	void update();
	void render();

};

#endif