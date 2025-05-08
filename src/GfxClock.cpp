#include "GfxClock.h"


namespace ws4
{
    void GfxClock::update()
    {
        epoch = std::time(nullptr);
        strftime(timeStr, sizeof(timeStr),
                 (localtime(&epoch)->tm_hour % 12 < 10 && localtime(&epoch)->tm_hour % 12 > 0) ? " %-I:%M:%S" : "%-I:%M:%S",
                 localtime(&epoch));
        strftime(timeAPStr, sizeof(timeAPStr), "%p", localtime(&epoch));
        strftime(dateStr, sizeof(dateStr), "%a %b %e", localtime(&epoch)); // %e is space-padded

        time.updateText(timeStr);
        ampm.updateText(timeAPStr);
        date.updateText(dateStr);
    }


    void GfxClock::renderTo(sf::RenderWindow &window)
    {
        time.renderTo(window);
        ampm.renderTo(window);
        date.renderTo(window);
    }
}