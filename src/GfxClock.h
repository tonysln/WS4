#include <SFML/Graphics.hpp>
#include "TextLabel.h"
#include <ctime>


#ifndef WS4_GFXCLOCK_H
#define WS4_GFXCLOCK_H


namespace ws4
{
    class GfxClock
    {
        std::time_t epoch = std::time(nullptr);
        char timeStr[12]{};
        char timeAPStr[6]{};
        char dateStr[12]{};
        TextLabel time;
        TextLabel ampm;
        TextLabel date;


    public:
        GfxClock(map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap);
        GfxClock() = default;

        void update();
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXCLOCK_H
