#include "App.h"
#include "consts.h"

int main()
{
    srand(time(0));
    App genAlg(WN_WIDTH, WN_HEIGHT, "Artificial life", WN_START_FPS);

    while (genAlg.isOpen() && !genAlg.isProgramEnd())
    {
        genAlg.update();
        genAlg.render();
    }

    return 0;
}