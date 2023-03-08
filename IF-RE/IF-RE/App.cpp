#include "App.h"
#include <vector>
#include <iostream>


#define CELL_SIZE 20.f


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

    /// Seting up environment
    env = new Environment();
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
    
    //env->update();
}

void App::render()
{
    root.clear();
    obj_matrix mat = env->getMatrix();
    
    sf::RectangleShape rectangle(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    
    // Test Label
    gui::Label lb(sf::Vector2f(60.f, 60.f), 40U);
    lb.setString(sf::String("Im label"));
    lb.setFont(PxlFont);

    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {

            auto name = sf::String("Empiness");//mat[i][j]->name;
            if (name == sf::String("Empiness"))
            {
                rectangle.setOutlineColor(sf::Color::Black);
                rectangle.setOutlineThickness(-1);
                rectangle.setFillColor(gui::Color::DullWhite);

            }
            else if (name == sf::String("Bot"))
            {
                rectangle.setOutlineColor(gui::Color::DarkGreen);
                rectangle.setOutlineThickness(-1);
                rectangle.setFillColor(gui::Color::Green);
            }
            else
            {
                rectangle.setOutlineThickness(-1);
                rectangle.setFillColor(gui::Color::DullWhite);
                rectangle.setFillColor(sf::Color::Magenta);
            }
            
            rectangle.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            root.draw(rectangle);
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
