#include "App.h"


int main()
{
    App genAlg;

    while (genAlg.isOpen() && !genAlg.isProgramEnd())
    {
        genAlg.update();

        genAlg.render();
    }

    return 0;
}