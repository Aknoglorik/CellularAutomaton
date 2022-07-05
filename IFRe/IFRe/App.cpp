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
    delete root;
}

// Инициализаторы

void App::initWindow(unsigned int width, unsigned int height, std::string wname)
{
    VM.width = width;
    VM.height = height;

    root = new sf::RenderWindow(VM, wname);
    root->setView(*view);
}

void App::initVariables()
{
    FPS = 0;
    gameEnd = false;
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");

    view = new sf::View;
    view->setCenter(sf::Vector2f(256.f, 128.f));
    view->setSize(sf::Vector2f(640.f, 480.f));
}

void App::initPlayer()
{
    sf::Texture texture;
    texture.loadFromFile("resources/img/hero.png");
    sf::Vector2f pos(100.f, 100.f);
    Weapon gun;

    player = new Pawn(texture, pos, gun, 400);
}


// Гетереы

bool App::isOpen()
{
    return root->isOpen();
}

bool App::isGameEnd()
{
    return gameEnd;
}


// Основные ф-ции

void App::pollEvent()
{
    while (root->pollEvent(event_))
    {
        switch (event_.type)
        {
        case sf::Event::Closed:
            root->close();
            break;
        
        case sf::Event::KeyPressed:
            if (event_.key.code == sf::Keyboard::Escape)
                root->close();
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
                //map_creator.change_by_pos(sf::Mouse::getPosition(*root));
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
    player->update(time);
    map_creator.update();
}

void App::render()
{
    root->clear();

    //drawing
    sf::Sprite pl_skin = player->getDrawable();
    
    sf::String counter_fps = "FPS: " + std::to_string(FPS);
    
    sf::Text text(std::string(counter_fps), PxlFont, 20U);

   
    root->draw(map_creator.getMap());
    root->draw(pl_skin);
    root->draw(text);


    root->display();
}
