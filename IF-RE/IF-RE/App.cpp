#include "App.h"
#include <iostream>
#include "consts.h"
_INC_OBJP_MATRIX



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

    defaultView = sf::View(sf::FloatRect(0, 0, width, height));

    view = sf::View(sf::FloatRect(0, 0, CELL_SIZE * ENV_WIDTH, CELL_SIZE * ENV_HEIGHT));
    root.setView(view);
    
    FPS = _fps;
    root.setFramerateLimit(FPS);

}

void App::initVariables()
{
    /// Setting up environment
    env = new Environment(ENV_WIDTH, ENV_HEIGHT);


    FPS = 0;
    programEnd = false;
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");

    auto create_button = [&](sf::FloatRect size, sf::String str, std::function<void()> f)
    {
        auto btn = new gui::Button(size, PxlFont, str);
        btn->bind(f);
        butts.push_back(btn);
    };

    // first line
    create_button(sf::FloatRect(BTN_HORIZ_POS, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "Pause",
        [&]() 
        {
            env->setPause(true);
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS+ BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "Resume",
        [&]()
        {
            env->setPause(false);
        });
    // second line
    create_button(sf::FloatRect(BTN_HORIZ_POS, BTN_VERT_POS+ BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "+sun",
        [&]() 
        {
            env->setExtraTemp(1);
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS+ BTN_HORIZ_DEL, BTN_VERT_POS+ BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "-sun",
        [&]()
        {
            env->setExtraTemp(-1);
        });
    // third line
    create_button(sf::FloatRect(BTN_HORIZ_POS, BTN_VERT_POS + 2*BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "+delay",
        [&]()
        {
            FPS+=5;
            root.setFramerateLimit(FPS);
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + BTN_HORIZ_DEL, BTN_VERT_POS + 2*BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "-delay",
        [&]()
        {
            if ((FPS-5) > 1)
            {
                FPS-=5;
                root.setFramerateLimit(FPS);
            }
        });
    
    /// Test Label
    lb = new gui::Label(STEP_LABEL_POS, STEP_LABEL_SIZE);
    lb->setString(sf::String(std::to_string(env->gen_step)));
    lb->setFont(PxlFont);


    /// Setting up bots textures
    sf::RectangleShape *emp             = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *bot             = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *food            = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *corpse          = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape *object          = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    
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
    sl = new gui::Slider(sf::Vector2f(40, 100), sf::Vector2f(540, 100), SLD_HEIGHT);
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
            defaultView = sf::View(sf::FloatRect(0, 0, event_.size.width, event_.size.height));
            view.setViewport(sf::FloatRect(0, 0, event_.size.width / root.getSize().x, event_.size.height / root.getSize().y));
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
    objp_matrix mat = env->getMatrix();

    sf::String counter_fps = "FPS: " + std::to_string(int(_FPS));
    sf::Text text(std::string(counter_fps), PxlFont, FPS_LABEL_SIZE);
    text.setPosition(FPS_LABEL_POS);
    text.setFillColor(sf::Color::Red);

    sl->update(root);

    // drawing
    root.setView(view);
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

    // HUD
    //root.setView(defaultView);
    for (auto butt : butts)
        root.draw(*butt);

    root.draw(text);
    root.draw(*lb);
    root.draw(*sl);

    root.display();
}
