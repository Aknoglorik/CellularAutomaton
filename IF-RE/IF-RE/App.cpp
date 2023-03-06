#include "App.h"
#include <vector>

#define ADD_COLOR_SPECTR
#include "GenGui.h"

typedef std::vector<std::vector<int>> int_matrix;


// ������������ / ��������������
App::App(unsigned int width, unsigned int height, std::string wname)
{
    initVariables();
    initWindow(width, height, wname);
}

App::~App()
{

}

// ��������������
void App::initWindow(unsigned int width, unsigned int height, std::string wname)
{
    VM.width = width;
    VM.height = height;

    root.create(VM, wname, 7U, sf::ContextSettings(0, 0, 7));
    root.setView(view);
    root.setFramerateLimit(60);

}

void App::initVariables()
{
    FPS = 0;
    programEnd = false;
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");
}


// �������
bool App::isOpen()
{
    return root.isOpen();
}

bool App::isProgramEnd()
{
    return programEnd;
}


// �������� �-���
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

    /// TEST SAMPLE
    /// it must be in update method
    int_matrix mat;
    mat.resize(10);
    for (int i = 0; i < 10; i++)
        mat[i].resize(10);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            mat[i][j] = 0;
            if (i == 5 && j == 7)
                mat[i][j] = 1;

        }
    ///

    
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));
    

    

    auto colorByNum = [&](int i, int j) 
    {
        switch (mat[i][j])
        {
        case 0:
            rectangle.setOutlineColor(sf::Color::Black);
            rectangle.setOutlineThickness(-1);
            rectangle.setFillColor(con::Color::DullWhite);
            break;
        case 1:
            rectangle.setOutlineColor(con::Color::DarkGreen);
            rectangle.setOutlineThickness(-1);
            rectangle.setFillColor(con::Color::Green);
            break;
        default:
            rectangle.setFillColor(sf::Color::Magenta);
        }
    };

    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            colorByNum(i, j);
            
            rectangle.setPosition(i*100, j*100);
            root.draw(rectangle);
        }
    }

    // Think about moving this code shape in initWindow()
    sf::FloatRect view(0, 0, 1000, 1000);
    root.setView(sf::View(view));

    // drawing
    sf::String counter_fps = "FPS: " + std::to_string(int(FPS));
    sf::Text text(std::string(counter_fps), PxlFont, 40U);
    text.setFillColor(sf::Color::Red);
    root.draw(text);

    root.display();
}
