#include "GfxClock.h"


namespace ws4
{
    GfxClock::GfxClock(map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap)
    {
        time = TextLabel(" 9:16:33 PM", fontMap["Star4000-Small"], "#d7d7d7", 31, 0,  0.8f, 574, 33, colorMap, 2);
        date = TextLabel("MON OCT 10", fontMap["Star4000-Small"], "#d7d7d7", 31, 0, 0.8f, 574, 53, colorMap, 2);
    }


    void GfxClock::update()
    {

    }


    void GfxClock::renderTo(sf::RenderWindow &window)
    {
        time.renderTo(window);
        date.renderTo(window);
    }
}