#include <SFML/Graphics.hpp>
#include "TextLabel.h"


#ifndef WS4_GFXCLOCK_H
#define WS4_GFXCLOCK_H


namespace ws4
{
    class GfxClock
    {


    public:
        GfxClock();

        void update();
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXCLOCK_H
