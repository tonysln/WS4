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
        GfxClock()
        {
            update();
            time = TextLabel(timeStr, "Star4000-Small", "#d7d7d7", 32, 1,  0.9f, 412, 33, 0);
            ampm = TextLabel(timeAPStr, "Star4000-Small", "#d7d7d7", 32, 1,  0.9f, 575, 33, 2);
            date = TextLabel(dateStr, "Star4000-Small", "#d7d7d7", 32, 1, 0.9f, 575, 53, 2);
        }

        void update();
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXCLOCK_H
