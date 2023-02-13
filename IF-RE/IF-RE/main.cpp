#include "App.h"


int main()
{
    App genAlg(640, 480, "Artificial life");

    while (genAlg.isOpen() && !genAlg.isProgramEnd())
    {
        genAlg.update();
        genAlg.render();
    }

    return 0;
}