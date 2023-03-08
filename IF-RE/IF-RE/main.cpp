#include "App.h"


int main()
{
    App genAlg(1000, 1000, "Artificial life");

    while (genAlg.isOpen() && !genAlg.isProgramEnd())
    {
        genAlg.update();
        genAlg.render();
    }

    return 0;
}