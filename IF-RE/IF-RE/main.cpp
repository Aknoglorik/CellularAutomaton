#include "App.h"

// � ��� 5 ���

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