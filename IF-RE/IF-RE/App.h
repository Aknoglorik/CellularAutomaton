#ifndef __APP__
#define __APP__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Camera.hpp"
#include "Environment.h"

#define ADD_COLOR_SPECTR
#include "GenGui.h"
#include "DLGGraph.h"


class App
{
public:
	App(unsigned int width = 640, unsigned int height = 480, std::string wname = "SFML 2.5.1", int _fps = 60);
	~App();


private:
	sf::VideoMode VM;
	sf::RenderWindow root;
	sf::Event event_;
	int FPS;

	std::vector<sf::RectangleShape*> bot_shapes;
	std::vector<sf::RectangleShape*> botSpriteByType;

	std::list<gui::GObject*> widgets;

	gui::DialogWndow *dlg = nullptr;
	DLGGraph* dkg_graph = nullptr;

	sf::Vertex *line_dlg_obj = nullptr;

	// Strings for dynamic Labels
	sf::String step_string;
	sf::String gen_string;
	sf::String fps_counter_string;
	sf::String temp_mode;

	Environment *env;

	sf::Clock clock;
	sf::View view, default_view;
	Camera *cameraView;
	operatingMode::Mode view_mode = operatingMode::_default;

	float _FPS;
	bool programEnd;
	bool isFullscreen;
	bool hideHUD;

	sf::Font PxlFont;

	void initWindow(unsigned int width, unsigned int height, std::string wname, int _fps);
	void initVariables();

	void makeCellTextures();

	void makeWidgets();

	void makeButtons();


public:
	bool isOpen();
	bool isProgramEnd();
	
	void pollEvent();
	void update();
	void render();

};

#endif