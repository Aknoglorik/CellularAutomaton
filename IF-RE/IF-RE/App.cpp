#include "App.h"
#include <iostream>


#define CELL_SIZE 10.f


typedef std::vector<std::vector<Object*>> obj_matrix;



// Constructor / Destructors
App::App(unsigned int width, unsigned int height, std::string wname)
{
    initVariables();
    initWindow(width, height, wname);
}

App::~App()
{

}

// Initializers
void App::initWindow(unsigned int width, unsigned int height, std::string wname)
{
    VM.width = width;
    VM.height = height;

    root.create(VM, wname, 7U, sf::ContextSettings(0, 0, 7));
    //sf::FloatRect view(0, 0, 1000, 1000);
    //root.setView(sf::View(view));
    root.setFramerateLimit(60);

}

void App::initVariables()
{
    FPS = 0;
    programEnd = false;
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");

    /// vector of Buttons
    auto btn = new gui::Button(sf::FloatRect(400, 200, 200, 50), PxlFont, "ni?");
    btn->bind([]() 
        { 
            std::cout << "callback" << std::endl; 
        });
    butts.push_back(btn);
    ///

    /// Setting up environment
    env = new Environment();


    /// Setting up bots textures
    sf::RectangleShape *emp     = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *bot     = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *food    = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *corpse  = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *object  = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    
    emp->setOutlineColor(gui::Color::LightGray);
    emp->setOutlineThickness(-1);
    emp->setFillColor(gui::Color::DullWhite);
    bot_shapes.push_back(emp);

    bot->setOutlineColor(gui::Color::DarkGreen);
    bot->setOutlineThickness(-1);
    bot->setFillColor(gui::Color::Green);
    bot_shapes.push_back(bot);
    
    food->setOutlineThickness(-1);
    food->setFillColor(gui::Color::DullWhite);
    food->setFillColor(sf::Color::Magenta);
    bot_shapes.push_back(food);

    bot_shapes.push_back(corpse);
    bot_shapes.push_back(object);
}


// Getters
bool App::isOpen()
{
    return root.isOpen();
}

bool App::isProgramEnd()
{
    return programEnd;
}


// Main methods
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

        case sf::Event::Resized:
            sf::FloatRect view(0, 0, event_.size.width, event_.size.height);
            root.setView(sf::View(view));
            break;
        }
    }
}

void App::update()
{
    /// Getting FPS
    float time = clock.getElapsedTime().asSeconds();
    FPS = 1 / time;

    clock.restart();
    ///

    // game logic
    pollEvent();

    sf::Vector2f mouse_pos(sf::Mouse::getPosition(root).x - (int)root.getSize().x / 2, 
                           sf::Mouse::getPosition(root).y - (int)root.getSize().y / 2);
    
    for (auto butt : butts)
        butt->update(root);
    
    env->update();
}

void App::render()
{
    root.clear();
    obj_matrix mat = env->getMatrix();
    
    // Test Label
    gui::Label lb(sf::Vector2f(60.f, 60.f), 40U);
    lb.setString(sf::String("Im label"));
    lb.setFont(PxlFont);

    sf::RectangleShape* rectangle;

    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            rectangle = bot_shapes[mat[i][j]->getType()];
            rectangle->setPosition(i * CELL_SIZE, j * CELL_SIZE);
            root.draw(*rectangle);
        }
    }

    // drawing
    sf::String counter_fps = "FPS: " + std::to_string(int(FPS));
    sf::Text text(std::string(counter_fps), PxlFont, 40U);
    text.setFillColor(sf::Color::Red);
    
    for (auto butt : butts)
        root.draw(*butt);

    root.draw(text);
    root.draw(lb);

    root.display();
}
