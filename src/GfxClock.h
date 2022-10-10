#include <SFML/Graphics.hpp>
#include "TextLabel.h"


#ifndef WS4_GFXCLOCK_H
#define WS4_GFXCLOCK_H


namespace ws4
{
    class GfxClock
    {
        ws4::TextLabel time;
        ws4::TextLabel date;


    public:
        GfxClock(map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap);
        GfxClock() = default;

        void update();
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXCLOCK_H
