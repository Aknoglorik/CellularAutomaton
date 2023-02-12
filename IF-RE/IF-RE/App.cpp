#include "App.h"

// Конструкторы / деконструкторы
App::App(unsigned int width, unsigned int height, std::string wname)
{
    initVariables();
    initWindow(width, height, wname);
}

App::~App()
{

}

// Инициализаторы
void App::initWindow(unsigned int width, unsigned int height, std::string wname)
{
    VM.width = width;
    VM.height = height;

    root.create(VM, wname);
    root.setView(view);
}

void App::initVariables()
{
    FPS = 0;
    programEnd = false;
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");
}


// Гетереы
bool App::isOpen()
{
    return root.isOpen();
}

bool App::isProgramEnd()
{
    return programEnd;
}


// Основные ф-ции
void App::pollEvent()
{
    while (root.pollEvent(event_))
    {
        switch (event_.type)
        {
        case sf::Event::Closed:
            root.close();
            break;
        
        case sf::Event::KeyPressed:
            if (event_.key.code == sf::Keyboard::Escape)
                root.close();
            break;
        }
    }
}

void App::update()
{
    float time = clock.getElapsedTime().asSeconds();
    FPS = 1 / time;

    clock.restart();

    pollEvent();

    // game logic
    sf::Vector2f mouse_pos(sf::Mouse::getPosition(root).x - (int)root.getSize().x / 2, 
                           sf::Mouse::getPosition(root).y - (int)root.getSize().y / 2);
}

void App::render()
{
    root.clear();

    //drawing
    sf::String counter_fps = "FPS: " + std::to_string(FPS);
    sf::Text text(std::string(counter_fps), PxlFont, 20U);

    root.setView(view);
    root.draw(text);

    root.display();
}
