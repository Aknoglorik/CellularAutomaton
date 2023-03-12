#ifndef __APP__
#define __APP__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Environment.h"

#define ADD_COLOR_SPECTR
#include "GenGui.h"


class App
{
public:
	App(unsigned int width = 640, unsigned int height = 480, std::string wname = "SFML 2.5.1");
	~App();


private:
	sf::VideoMode VM;
	sf::RenderWindow root;
	sf::Event event_;

	std::vector<sf::RectangleShape*> bot_shapes;
	std::vector<gui::Button*> butts;
	gui::Label* lb;

	Environment *env;

	sf::Clock clock;
	sf::View view;

	float FPS;
	bool programEnd;
	sf::Font PxlFont;

	void initWindow(unsigned int width, unsigned int height, std::string wname);
	void initVariables();


public:
	bool isOpen();
	bool isProgramEnd();
	
	void pollEvent();
	void update();
	void render();

};

#endif