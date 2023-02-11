#include "App.h"

// С вас 5 тыщ

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