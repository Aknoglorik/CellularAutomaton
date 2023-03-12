#include "App.h"


int main()
{
    srand(time(0));
    App genAlg(1000, 1000, "Artificial life");

    while (genAlg.isOpen() && !genAlg.isProgramEnd())
    {
        genAlg.update();
        genAlg.render();
    }

    return 0;
}