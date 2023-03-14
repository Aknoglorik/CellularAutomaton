#include "App.h"
#include <iostream>


#define CELL_SIZE 20.f


typedef std::vector<std::vector<Object*>> obj_matrix;



// Constructor / Destructors
App::App(unsigned int width, unsigned int height, std::string wname, int _fps)
{
    initVariables();
    initWindow(width, height, wname, _fps);
}

App::~App()
{

}

// Initializers
void App::initWindow(unsigned int width, unsigned int height, std::string wname, int _fps)
{
    VM.width = width;
    VM.height = height;

    root.create(VM, wname, 7U, sf::ContextSettings(0, 0, 7));
    //sf::FloatRect view(0, 0, 1000, 1000);
    //root.setView(sf::View(view));
    FPS = _fps;
    root.setFramerateLimit(FPS);

}

void App::initVariables()
{
    /// Setting up environment
    env = new Environment(30, 30);


    FPS = 0;
    programEnd = false;
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");

    auto create_button = [&](sf::FloatRect size, sf::String str, std::function<void()> f)
    {
        auto btn = new gui::Button(size, PxlFont, str);
        btn->bind(f);
        butts.push_back(btn);
    };

    /// vector of Buttons

    auto start_pos = 1600;
    auto vert_pos  = 50;
    auto wtdh      = 100;
    auto hght      = 30;
    auto vert_del  = 40;
    auto hor_del   = 110;

    // first line
    create_button(sf::FloatRect(start_pos, vert_pos, wtdh, hght), "Pause",
        []() 
        {
            std::cout << "Pause" << std::endl;
        });
    create_button(sf::FloatRect(start_pos+ hor_del, vert_pos, wtdh, hght), "Resume",
        []()
        {
            std::cout << "Resume" << std::endl;
        });
    // second line
    create_button(sf::FloatRect(start_pos, vert_pos+ vert_del, wtdh, hght), "+sun",
        []() 
        {
            std::cout << "+sun" << std::endl;
        });
    create_button(sf::FloatRect(start_pos+ hor_del, vert_pos+ vert_del, wtdh, hght), "-sun",
        []() 
        {
            std::cout << "-sun" << std::endl;
        });
    // third line
    create_button(sf::FloatRect(start_pos, vert_pos + 2*vert_del, wtdh, hght), "+delay",
        [&]()
        {
            FPS+=5;
            root.setFramerateLimit(FPS);
        });
    create_button(sf::FloatRect(start_pos + hor_del, vert_pos + 2*vert_del, wtdh, hght), "-delay",
        [&]()
        {
            if ((FPS-5) > 1)
            {
                FPS-=5;
                root.setFramerateLimit(FPS);
            }
        });
    
    /// Test Label
    lb = new gui::Label(sf::Vector2f(60.f, 60.f), 40U);
    lb->setString(sf::String(std::to_string(env->gen_step)));
    lb->setFont(PxlFont);


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
    
    food->setFillColor(gui::Color::Red);
    bot_shapes.push_back(food);

    corpse->setFillColor(gui::Color::LightGray);
    bot_shapes.push_back(corpse);

    object->setFillColor(sf::Color::Magenta);
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
    _FPS = 1 / time;

    clock.restart();
    ///

    // game logic
    pollEvent();

    sf::Vector2f mouse_pos(sf::Mouse::getPosition(root).x - (int)root.getSize().x / 2, 
                           sf::Mouse::getPosition(root).y - (int)root.getSize().y / 2);
    
    for (auto butt : butts)
        butt->update(root);

    lb->setString(sf::String("Step " + std::to_string(env->gen_step)));
    
    env->update();
}

void App::render()
{
    root.clear();
    obj_matrix mat = env->getMatrix();
    
    // Test Label

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
    sf::String counter_fps = "FPS: " + std::to_string(int(_FPS));
    sf::Text text(std::string(counter_fps), PxlFont, 40U);
    text.setFillColor(sf::Color::Red);
    
    for (auto butt : butts)
        root.draw(*butt);

    root.draw(text);
    root.draw(*lb);

    root.display();
}
