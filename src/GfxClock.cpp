#include "GfxClock.h"


namespace ws4
{
    GfxClock::GfxClock(map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap)
    {
        update();
        time = TextLabel(timeStr, fontMap["Star4000-Small"], "#d7d7d7", 31, 1,  0.9f, 531, 33, colorMap, 2);
        ampm = TextLabel(timeAPStr, fontMap["Star4000-Small"], "#d7d7d7", 31, 1,  0.9f, 576, 33, colorMap, 2);
        date = TextLabel(dateStr, fontMap["Star4000-Small"], "#d7d7d7", 31, 1, 0.9f, 574, 53, colorMap, 2);
    }


    void GfxClock::update()
    {
        epoch = std::time(nullptr);
        strftime(timeStr, sizeof(timeStr),
                 (localtime(&epoch)->tm_hour % 12 < 10 && localtime(&epoch)->tm_hour % 12 > 0) ? " %-I:%M:%S" : "%-I:%M:%S",
                 localtime(&epoch));
        strftime(timeAPStr, sizeof(timeAPStr), "%p", localtime(&epoch));
        strftime(dateStr, sizeof(dateStr), "%a %b %e", localtime(&epoch)); // %e is space-padded

        time.updateTextInPlace(timeStr);
        ampm.updateTextInPlace(timeAPStr);
        date.updateTextInPlace(dateStr);
    }


    void GfxClock::renderTo(sf::RenderWindow &window)
    {
        time.renderTo(window);
        ampm.renderTo(window);
        date.renderTo(window);
    }
}