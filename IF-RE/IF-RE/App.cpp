#include "App.h"
#include "consts.h"
_INC_OBJP_MATRIX

#include <iostream>


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
    delete dlg;
    delete line_dlg_obj;

    for (int i = 0; i < widgets.size(); i++)
        widgets.pop_back();

    for (int i = 0; i < bot_shapes.size(); i++)
        delete bot_shapes[i];

    for (int i = 0; i < botSpriteByType.size(); i++)
        delete botSpriteByType[i];
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

    view = sf::View(sf::FloatRect(0, 0, width * CELL_SIZE * ENV_HEIGHT / height, CELL_SIZE * ENV_HEIGHT));
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

    line_dlg_obj = new sf::Vertex[2];

    /// Setup buttons props
    FPS = 0;
    programEnd = false;
    hideHUD = false;

    makeWidgets();
    makeCellTextures();
}

void App::makeCellTextures()
{
    /// Setting up bots textures
    sf::RectangleShape* emp = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape* bot = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape* food = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape* corpse = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape* object = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    emp->setOutlineColor(gui::Color::LightGray);
    emp->setOutlineThickness(-1);
    emp->setFillColor(gui::Color::DullWhite);
    bot_shapes.push_back(emp);

    bot->setOutlineColor(gui::Color::DarkGreen);
    bot->setOutlineThickness(-1);
    bot->setFillColor(gui::Color::Green);
    bot_shapes.push_back(bot);

    food->setOutlineColor(gui::Color::DarkRed2);
    food->setOutlineThickness(-1);
    food->setFillColor(gui::Color::DarkRed);
    bot_shapes.push_back(food);

    corpse->setOutlineColor(gui::Color::DarkGray3);
    corpse->setOutlineThickness(-1);
    corpse->setFillColor(gui::Color::LightGray);
    bot_shapes.push_back(corpse);

    object->setFillColor(sf::Color::Magenta);
    bot_shapes.push_back(object);

    sf::RectangleShape* predator = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape* prey = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    sf::Color cl(gui::Color::Red);
    cl.a = 150;
    predator->setFillColor(cl);
    botSpriteByType.push_back(predator);

    cl.a = 0;
    prey->setFillColor(cl);
    botSpriteByType.push_back(prey);

    ///
}

void App::makeWidgets()
{

    dkg_graph = new DLGGraph(sf::Vector2f(800, 600), sf::Vector2f(0,  CELL_SIZE * ENV_HEIGHT));//sf::Vector2f(-800, 600));
    //dkg_graph->setAnc(gui::TopRight);
    //widgets.push_back(dkg_graph);

    makeButtons();

    // Slider
    auto sld = new gui::Slider(SLD_POSITION, SLD_SIZE, 0, -19, 20,
        [&](int value)
        {
            env->setGlobalTemp(value);
        });
    //sld->setDynamicValue(env->getGloabalTemp());
    sld->setAnc(BTN_ANCHOR);
    widgets.push_back(sld);


    /// Labels
    gui::Label* lb_step = new gui::Label(STEP_LABEL_POS, STEP_LABEL_SIZE);
    lb_step->setDynamicString(step_string);
    lb_step->setFont(PxlFont);
    lb_step->setColor(sf::Color::Red);
    lb_step->setAnc(BTN_ANCHOR);
    widgets.push_back(lb_step);

    gui::Label* lb_gen = new gui::Label(STEP_LABEL_POS + sf::Vector2f(0, BTN_VERT_DEL), STEP_LABEL_SIZE);
    lb_gen->setDynamicString(gen_string);
    lb_gen->setFont(PxlFont);
    lb_gen->setColor(sf::Color::Red);
    lb_gen->setAnc(BTN_ANCHOR);
    widgets.push_back(lb_gen);

    gui::Label* lb_temp = new gui::Label(STEP_LABEL_POS + sf::Vector2f(0, 2 * BTN_VERT_DEL), FPS_LABEL_SIZE);
    lb_temp->setDynamicString(temp_mode);
    lb_temp->setFont(PxlFont);
    lb_temp->setColor(sf::Color::Red);
    lb_temp->setAnc(BTN_ANCHOR);
    widgets.push_back(lb_temp);

    gui::Label* lb_fps = new gui::Label(STEP_LABEL_POS + sf::Vector2f(2 * BTN_HORIZ_DEL, 2 * BTN_VERT_DEL), FPS_LABEL_SIZE);
    lb_fps->setDynamicString(fps_counter_string);
    lb_fps->setFont(PxlFont);
    lb_fps->setColor(sf::Color::Red);
    lb_fps->setAnc(BTN_ANCHOR);
    widgets.push_back(lb_fps);
    ///
}

void App::makeButtons()
{
    auto create_button = [&](sf::FloatRect size, sf::String str, std::function<void()> f, gui::Anchor anc = BTN_ANCHOR)
    {
        auto btn = new gui::Button(size, PxlFont, str);
        btn->bind(f);
        btn->setAnc(anc);
        widgets.push_back(btn);
    };

    // Left side
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
    create_button(sf::FloatRect(BTN_HORIZ_POS + 4 * BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "tempera",
        [&]()
        {
            view_mode = operatingMode::_temperature;
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + 5 * BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "default",
        [&]()
        {
            view_mode = operatingMode::_default;
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + 6 * BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "Energy",
        [&]()
        {
            view_mode = operatingMode::_energy;
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + 7 * BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "BotType",
        [&]()
        {
            view_mode = operatingMode::_botType;
        });
    // second line
    create_button(sf::FloatRect(BTN_HORIZ_POS, BTN_VERT_POS + BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "+delay",
        [&]()
        {
            FPS += 5;
            root.setFramerateLimit(FPS);

        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "-delay",
        [&]()
        {
            if ((FPS - 5) > 1)
            {
                FPS -= 5;
                root.setFramerateLimit(FPS);
            }
            else
            {
                FPS = 0;
                root.setFramerateLimit(1);
            }
        });

    create_button(sf::FloatRect(BTN_HORIZ_POS + 6 * BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "-sun",
        [&]()
        {
            env->setExtraLight(-1);
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + 7 * BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "+sun",
        [&]()
        {
            env->setExtraLight(1);
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + 6 * BTN_HORIZ_DEL, BTN_VERT_POS + 2 * BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "-temp",
        [&]()
        {
            env->setExtraTemp(-1);
        });
    create_button(sf::FloatRect(BTN_HORIZ_POS + 7 * BTN_HORIZ_DEL, BTN_VERT_POS + 2 * BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "+temp",
        [&]()
        {
            env->setExtraTemp(1);
        });

    // Right side
    // first line
    create_button(sf::FloatRect(-BTN_HORIZ_POS - 2 * BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "Save",
        [&]()
        {
            env->saveWorld("saved_world.txt");
        },
        gui::BottomRight);
    create_button(sf::FloatRect(-BTN_HORIZ_POS - BTN_HORIZ_DEL, BTN_VERT_POS, BTN_WITDH, BTN_HEIGHT), "Load",
        [&]()
        {
            env->loadWorld("saved_world.txt");
        },
        gui::BottomRight);
    // second line
    create_button(sf::FloatRect(-BTN_HORIZ_POS - 2 * BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "GenInfo",
        [&]()
        {
            if (!dlg)
            {
                dlg = new gui::DialogWndow(DLG_POS, DLG_SIZE, PxlFont, root);
                widgets.push_back(dlg);
            }
        },
        gui::BottomRight);
    create_button(sf::FloatRect(-BTN_HORIZ_POS - BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "CloseInfo",
        [&]()
        {
            if (dlg)
                dlg->do_it_close = true;
            dlg = nullptr;
        },
        gui::BottomRight);
    create_button(sf::FloatRect(-BTN_HORIZ_POS - 2 * BTN_HORIZ_DEL, BTN_VERT_POS + 2*BTN_VERT_DEL, BTN_WITDH, BTN_HEIGHT), "Graph",
        [&]()
        {
            dkg_graph->draw_it = !dkg_graph->draw_it;
        },
        gui::BottomRight);
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
                root.setFramerateLimit(FPS);

                isFullscreen = !isFullscreen;
            }
            if (pressed_key == sf::Keyboard::F1)
                hideHUD = !hideHUD;
            if (pressed_key == sf::Keyboard::W)
                cameraView->moveUp(true);
            if (pressed_key == sf::Keyboard::A)
                cameraView->moveLeft(true);
            if (pressed_key == sf::Keyboard::S)
                cameraView->moveDown(true);
            if (pressed_key == sf::Keyboard::D)
                cameraView->moveRight(true);
            if (pressed_key == sf::Keyboard::Space)
                env->setPause(!env->getPause());
            if (pressed_key == sf::Keyboard::Equal)
            {
                FPS += 5;
                root.setFramerateLimit(FPS);
            }
            if (pressed_key == sf::Keyboard::Hyphen)
            {
                if ((FPS - 5) > 1)
                {
                    FPS -= 5;
                    root.setFramerateLimit(FPS);
                }
                else
                {
                    FPS = 0;
                    root.setFramerateLimit(1);
                }
            }
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
        {
            if (event_.mouseWheelScroll.delta < 0)
            {
                view.zoom(1.1);
            }
            else if (event_.mouseWheelScroll.delta > 0)
            {
                view.zoom(0.9);
            }
            break;
        }

        case sf::Event::MouseButtonPressed:
        {
            sf::Vector2i m_pos = sf::Mouse::getPosition(root);
            sf::Vector2f pos = root.mapPixelToCoords(m_pos, view);
            auto workPlace = sf::IntRect(0, 0, root.getSize().x, root.getSize().y - HUD_HEIGHT * view.getViewport().height);

            if (!workPlace.contains(m_pos) || dlg && dlg->getHitBox().contains((sf::Vector2f)m_pos))
                break;
            
            if (!sf::FloatRect(0, 0, ENV_WIDTH * CELL_SIZE, ENV_HEIGHT * CELL_SIZE).contains(pos))
                break;

            auto obj = env->getMatrix()[(int)(pos.x / CELL_SIZE)][(int)(pos.y / CELL_SIZE)];
            
            if (obj->getType() == cellType::Bot && dlg)
            {
                dlg->setCurrentObj((Bot*)obj);
            }
            

            break;
        }

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

    pollEvent();

    // HUD logic
    if (!hideHUD) 
    {
        for (auto wid : widgets)
            wid->update(root);

        std::_Erase_nodes_if(widgets, [&](gui::GObject* gobj)->bool
            {
                if (gobj->do_it_close)
                {
                    if (gobj == (gui::GObject*)dlg)
                        dlg = nullptr;
                    delete gobj;

                    gobj = nullptr;
                    return true;
                }
                return false;
            });

        step_string         = "Step " + std::to_string(env->gen_step);
        gen_string          = "Gen  " + std::to_string(env->gen_generation);
        fps_counter_string  = "IPS: " + std::to_string(int(_FPS));
    }

    int step = env->update();
    if (step + 1)
    {
        //std::cout << "--" << step  << std::endl;
        //std::cout << "step " << step << std::endl;
        dkg_graph->AddPoint(sf::Vector2f(env->gen_generation, step));
        //std::cout << env->gen_generation << ' ' << step << std::endl;
    }

    cameraView->move();
    dkg_graph->update(root);
}

void App::render()
{
    root.clear();

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

    // drawing
    root.setView(view);
    int max_temp = 0;
    int min_temp = 0;

    int max_enrg = 0;
    int min_enrg = 0;

    bool flag = false;

    objp_matrix mat = env->getMatrix();
    sf::RectangleShape* rectangle;
    sf::RectangleShape* color_rectangle = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));;
    temp_mode = "DefaultView";
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            rectangle = bot_shapes[mat[i][j]->getType()];
            rectangle->setPosition(i * CELL_SIZE, j * CELL_SIZE);
            root.draw(*rectangle);

            if (view_mode == operatingMode::_energy && mat[i][j]->getType() == cellType::Bot)
            {
                color_rectangle->setFillColor(colorByInt((mat[i][j])->getEnergy() * 3));
                color_rectangle->setPosition(i * CELL_SIZE, j * CELL_SIZE);
                root.draw(*color_rectangle);

                if (mat[i][j]->getEnergy() > max_enrg)
                    max_enrg = mat[i][j]->getEnergy();


                if (!flag && !min_enrg && mat[i][j]->getType() == cellType::Bot)
                {
                    min_enrg = mat[i][j]->getEnergy();
                }

                if (flag && mat[i][j]->getEnergy() < min_enrg && mat[i][j]->getType() == cellType::Bot)
                {
                    min_enrg = mat[i][j]->getEnergy();
                }

                temp_mode = "Enrg: " + std::to_string(min_enrg) + " ~ " + std::to_string(max_enrg);

            }
            if (view_mode == operatingMode::_botType && mat[i][j]->getType() == cellType::Bot)
            {
                rectangle = botSpriteByType[((Bot*)mat[i][j])->getSpriteType()/2];
                rectangle->setPosition(i * CELL_SIZE, j * CELL_SIZE);
                root.draw(*rectangle);

                if (mat[i][j]->getEnergy() > max_enrg)
                    max_enrg = mat[i][j]->getEnergy();

                if (mat[i][j]->getEnergy() < min_enrg)
                    min_enrg = mat[i][j]->getEnergy();

                temp_mode = "Predator-Prey";

            }
        }
    }
    delete color_rectangle;
    
    if (view_mode == operatingMode::_temperature)
    {
        float_matrix mat2 = env->getTemperatureMatrix();

        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        max_temp = mat2[0][0];
        min_temp = mat2[0][0];
        float koef = 1;

        for (int i = 0; i < mat2.size(); i++)
        {
            for (int j = 0; j < mat2[0].size(); j++)
            {

                if (mat2[i][j] > max_temp)
                    max_temp = mat2[i][j];

                if (mat2[i][j] < min_temp)
                    min_temp = mat2[i][j];
            }
        }

        koef = 4000 / ((max_temp - min_temp)? (max_temp - min_temp) : 1);
        if (!koef)
            koef = 3;
        if (koef < 0)
            koef = -koef;
        for (int i = 0; i < mat2.size(); i++)
        {
            for (int j = 0; j < mat2[0].size(); j++)
            {
                rectangle->setFillColor(colorByInt((max_temp - mat2[i][j]) * 30));// koef));
                rectangle->setPosition(i * CELL_SIZE, j * CELL_SIZE);
                root.draw(*rectangle);
            }
        }

        delete rectangle;
        temp_mode = "Temp: " + std::to_string(min_temp + env->getGloabalTemp()) + " ~ " + std::to_string(max_temp + env->getGloabalTemp());
    }
    // dl selected obj
    if (dlg)
    {
        auto sel_obj = dlg->getCurrentObj();
        if (sel_obj)
        {
            sf::Vector2f sel_obj_pos(sel_obj->getPos().x * CELL_SIZE, sel_obj->getPos().y * CELL_SIZE);
            auto second_point = root.mapPixelToCoords(root.mapCoordsToPixel(dlg->getPosition(), default_view), view);

            dlg->selectedBot.setPosition(sel_obj_pos);
            root.draw(dlg->selectedBot);

            line_dlg_obj[0] = sf::Vertex(sel_obj_pos, gui::Color::DarkGray2);
            line_dlg_obj[1] = sf::Vertex(second_point, gui::Color::DarkGray2);

            root.draw(line_dlg_obj, 4, sf::Lines);
        }
    }
    root.draw(*dkg_graph);
    // HUD
    if (!hideHUD)
    {
            root.setView(default_view);

            sf::RectangleShape hud_bg(sf::Vector2f(default_view.getSize().x, HUD_HEIGHT));
            hud_bg.setFillColor(HUD_BG);
            hud_bg.setPosition(0, default_view.getSize().y - HUD_HEIGHT);
            root.draw(hud_bg);

            for (auto wid : widgets)
                root.draw(*wid);
    }

    root.display();
}
