#include "App.h"

//Разраб чмо обнов нет

int main()
{
    App game;

    while (game.isOpen() && !game.isGameEnd())
    {
        game.update();

        game.render();
    }

    return 0;
}