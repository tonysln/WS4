#include "WS4.h"


int main()
{
    ws4::WS4 ws4Engine;

    ws4Engine.getNewData();
    ws4Engine.loadGraphics();
    ws4Engine.loadData();
    ws4Engine.loadMusic();

    return ws4Engine.runLoop();
};
