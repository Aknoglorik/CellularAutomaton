#include "App.h"
#include "consts.h"
#include <fstream>


int main()
{
    std::ofstream file;
    file.open("graph.txt");
    file.close();

    srand(time(0));
    App genAlg(WN_WIDTH, WN_HEIGHT, "Artificial life", WN_START_FPS);

    while (genAlg.isOpen() && !genAlg.isProgramEnd())
    {
        genAlg.update();
        genAlg.render();
    }

    return 0;
}