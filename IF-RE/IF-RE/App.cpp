#include "App.h"
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
    delete cameraView;
    delete env;

    for (int i = 0; i < widgets.size(); i++)
        delete widgets[i];

    for (int i = 0; i < bot_shapes.size(); i++)
        delete bot_shapes[i];
}

// Initializers
void App::initWindow(unsigned int width, unsigned int height, std::string wname, int _fps)
{
    VM.width = width;
    VM.height = height;

    isFullscreen = (WN_START_MOD == sf::Style::Fullscreen);
    root.create(VM, wname, WN_START_MOD, sf::ContextSettings(0, 0, 7));

    //sf::RenderWindow ret;
    //ret.create(VM, wname, 7U, sf::ContextSettings(0, 0, 7));

    default_view = sf::View(sf::FloatRect(0, 0, width, height));

    view = sf::View(sf::FloatRect(0, 0, CELL_SIZE * ENV_WIDTH, CELL_SIZE * ENV_HEIGHT + HUD_HEIGHT));
    cameraView = new Camera(view);
    root.setView(view);
    
    FPS = _fps;
    root.setFramerateLimit(FPS);

}

void App::initVariables()
{
    PxlFont.loadFromFile("resources/font/pxlfont.ttf");
    
    /// Setting up environment
    env = new Environment(ENV_WIDTH, ENV_HEIGHT);


    /// Setup buttons props
    FPS = 0;
    programEnd = false;
    auto create_button = [&](sf::FloatRect size, sf::String str, std::function<void()> f)
    {
        auto btn = new gui::Button(size, PxlFont, str);
        btn->bind(f);
        btn->setAnc(BTN_ANCHOR);
        widgets.push_back(btn);
    };

    // first line
    create_button(sf::FloatRect(BTN_HORIZ_POS, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "Pause",
        [&]() 
        {
            env->setPause(true);
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "Resume",
        [&]()
        {
            env->setPause(false);
        });

    create_button(sf::FloatRect(BTN_HORIZ_POS + 4*BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "temp",
        [&]() 
        {
            view_mode = operatingMode::_temperature;
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + 5*BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "def",
        [&]()
        {
            view_mode = operatingMode::_default;
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
            else
            {
                FPS = 0;
                root.setFramerateLimit(1);
            }
        });
    ///


    // Slider
    auto sld = new gui::Slider(SLD_POSITION, SLD_SIZE, SLD_HEIGHT);
    sld->setAnc(BTN_ANCHOR);
    widgets.push_back(sld);


    /// Labels
    gui::Label* lb_step = new gui::Label(STEP_LABEL_POS, STEP_LABEL_SIZE);
    lb_step->setDynamicString(step_string);
    lb_step->setFont(PxlFont);
    lb_step->setColor(sf::Color::Red);
    lb_step->setAnc(BTN_ANCHOR);
    widgets.push_back(lb_step);

    gui::Label* lb_temp = new gui::Label(FPS_LABEL_POS + sf::Vector2f(0, BTN_VERT_DEL), FPS_LABEL_SIZE);
    lb_temp->setDynamicString(temp_mode);
    lb_temp->setFont(PxlFont);
    lb_temp->setColor(sf::Color::Red);
    lb_temp->setAnc(BTN_ANCHOR);
    widgets.push_back(lb_temp);

    gui::Label* lb_fps = new gui::Label(FPS_LABEL_POS, FPS_LABEL_SIZE);
    lb_fps->setDynamicString(fps_counter_string);
    lb_fps->setFont(PxlFont);
    lb_fps->setColor(sf::Color::Red);
    lb_fps->setAnc(BTN_ANCHOR);
    widgets.push_back(lb_fps);
    ///


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
    ///
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
        {
            auto pressed_key = event_.key.code;

            if (pressed_key == sf::Keyboard::Escape)
                root.close();
            if (pressed_key == sf::Keyboard::F11)
            {
                root.close();
                root.create(VM, "", (isFullscreen)? sf::Style::Default : sf::Style::Fullscreen, sf::ContextSettings(0, 0, 7));

                isFullscreen = !isFullscreen;
            }
            if (pressed_key == sf::Keyboard::W)
                cameraView->moveUp(true);
            if (pressed_key == sf::Keyboard::A)
                cameraView->moveLeft(true);
            if (pressed_key == sf::Keyboard::S)
                cameraView->moveDown(true);
            if (pressed_key == sf::Keyboard::D)
                cameraView->moveRight(true);
            break;
        }
        case sf::Event::KeyReleased:
        {
            auto released_key = event_.key.code;
            if (released_key == sf::Keyboard::W)
                cameraView->moveUp(false);
            if (released_key == sf::Keyboard::A)
                cameraView->moveLeft(false);
            if (released_key == sf::Keyboard::S)
                cameraView->moveDown(false);
            if (released_key == sf::Keyboard::D)
                cameraView->moveRight(false);
            break;
        }

        case sf::Event::MouseWheelScrolled:
            if (event_.mouseWheelScroll.delta < 0) //& view..z < 2)
            {
                //current_zoom *= 1.1;
                view.zoom(1.1);
            }
            else if (event_.mouseWheelScroll.delta > 0) //&& current_zoom > 0.5)
            {
                //current_zoom *= 0.9;
                view.zoom(0.9);
            }
            break;

        case sf::Event::Resized:
            default_view = sf::View(sf::FloatRect(0, 0, event_.size.width, event_.size.height));
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
    
    for (auto wid : widgets)
        wid->update(root);

    step_string         = "Step " + std::to_string(env->gen_step);
    fps_counter_string  = "FPS: " + std::to_string(int(_FPS));

    env->update();

    cameraView->move();
}

void App::render()
{
    root.clear();

    // drawing
    root.setView(view);
    int max_temp = 0;
    int min_temp = 0;
    if (view_mode == operatingMode::_default || view_mode == operatingMode::_temperature)
    {
        objp_matrix mat = env->getMatrix();
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
    }
    
    if (view_mode == operatingMode::_temperature)
    {
        int_matrix mat = env->getTemperatureMatrix();

        auto colorByInt = [](float temp) -> sf::Color
        {
            float Red, Green, Blue;
            if (temp <= 66)
            {
                Red = 255;
            }
            else
            {
                Red = temp - 60;
                Red = 329.698727446 * pow(Red, -0.1332047592);
                if (Red < 0) Red = 0;
                if (Red > 255) Red = 255;
            }

            if (temp <= 66)
            {
                Green = temp;
                Green = 99.4708025861 * log(Green) - 161.1195681661;

                if (Green < 0) Green = 0;
                if (Green > 255) Green = 255;
            }
            else
            {
                Green = temp - 60;
                Green = 288.1221695283 * pow(Green, -0.0755148492);

                if (Green < 0) Green = 0;
                if (Green > 255) Green = 255;
            }

            if (temp >= 66)
            {
                Blue = 255;
            }
            else
            {

                if (temp <= 19)
                    Blue = 0;
                else
                {
                    Blue = temp - 10;
                    Blue = 138.5177312231 * log(Blue) - 305.0447927307;

                    if (Blue < 0) Blue = 0;
                    if (Blue > 255) Blue = 255;
                }
            }

            return sf::Color(Red, Green, Blue, 150);
        };

        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        max_temp = mat[0][0];
        min_temp = mat[0][0];
        float koef = 1;

        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[0].size(); j++)
            {
                if (mat[i][j] > max_temp)
                    max_temp = mat[i][j];

                if (mat[i][j] < min_temp)
                    min_temp = mat[i][j];
            }
        }

        koef = max_temp / ((max_temp - min_temp)? (max_temp - min_temp) : 1);

        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[0].size(); j++)
            {
                rectangle->setFillColor(colorByInt((max_temp - mat[i][j]) * koef));
                rectangle->setPosition(i * CELL_SIZE, j * CELL_SIZE);
                root.draw(*rectangle);
            }
        }

        delete rectangle;
    }
    temp_mode = "Temp: " + std::to_string(min_temp) + " ~ " + std::to_string(max_temp);

    // HUD
    root.setView(default_view);

    sf::RectangleShape hud_bg(sf::Vector2f(default_view.getSize().x, HUD_HEIGHT));
    hud_bg.setFillColor(HUD_BG);
    hud_bg.setPosition(0, default_view.getSize().y - HUD_HEIGHT);
    root.draw(hud_bg);

    for (auto wid : widgets)
        root.draw(*wid);

    root.display();
}
