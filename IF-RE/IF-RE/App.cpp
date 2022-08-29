#include "App.h"

// Конструкторы / деконструкторы

App::App(unsigned int width, unsigned int height, std::string wname)
{
    initVariables();
    initWindow(width, height, wname);
    initPlayer();
}

App::~App()
{
    delete player;
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
    current_zoom = 1.f;

    FPS = 0;
    gameEnd = false;
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");

    view.setCenter(sf::Vector2f(256.f, 128.f));
    view.setSize(sf::Vector2f(640.f, 480.f));
    
}

void App::initPlayer()
{
    sf::Texture texture, sword;
    texture.loadFromFile("resources/img/hero.png");
    sf::Vector2f pos(100.f, 100.f);

    sword.loadFromFile("resources/img/sword.png");
    Weapon* gun = new Weapon(sword);

    player = new Pawn(texture, pos, gun, 400);
}


// Гетереы

bool App::isOpen()
{
    return root.isOpen();
}

bool App::isGameEnd()
{
    return gameEnd;
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
           // Player contoling
            if (event_.key.code == sf::Keyboard::W)
                player->moveUp(true);
            if (event_.key.code == sf::Keyboard::A)
                player->moveLeft(true);
            if (event_.key.code == sf::Keyboard::S)
                player->moveDown(true);
            if (event_.key.code == sf::Keyboard::D)
                player->moveRight(true);
            break;
        
        case sf::Event::KeyReleased:
            if (event_.key.code == sf::Keyboard::W)
                player->moveUp(false);
            if (event_.key.code == sf::Keyboard::A)
                player->moveLeft(false);
            if (event_.key.code == sf::Keyboard::S)
                player->moveDown(false);
            if (event_.key.code == sf::Keyboard::D)
                player->moveRight(false);
            break;

        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                player->attack();
            break;
            
        case sf::Event::MouseWheelScrolled:
            if (event_.mouseWheelScroll.delta < 0 && current_zoom < 2)
            {   
                current_zoom *= 1.1;
                view.zoom(1.1);
            }
            else if (event_.mouseWheelScroll.delta > 0 && current_zoom > 0.5)
            {
                current_zoom *= 0.9;
                view.zoom(0.91);
            }
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

    player->update(mouse_pos,time);
    map_creator.update();
}

void App::render()
{
    root.clear();

    //drawing
    sf::String counter_fps = "FPS: " + std::to_string(FPS);
    sf::Text text(std::string(counter_fps), PxlFont, 20U);
    
    view.setCenter(player->getCenterPos());
    root.setView(view);

    root.draw(map_creator.getMap());
    root.draw(*player);
    root.draw(text);

    root.display();
}
