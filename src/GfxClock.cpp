#include "GfxClock.h"


namespace ws4
{
    GfxClock::GfxClock(map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap)
    {
        update();
        time = TextLabel(timeStr, fontMap["Star4000-Small"], "#d7d7d7", 31, 1,  0.8f, 530, 33, colorMap, 2);
        ampm = TextLabel(timeAPStr, fontMap["Star4000-Small"], "#d7d7d7", 31, 1,  0.8f, 573, 33, colorMap, 2);
        date = TextLabel(dateStr, fontMap["Star4000-Small"], "#d7d7d7", 31, 1, 0.8f, 574, 53, colorMap, 2);
    }


    void GfxClock::update()
    {
        epoch = std::time(nullptr);
        strftime(timeStr, sizeof(timeStr), "%-I:%M:%S", localtime(&epoch));
        strftime(timeAPStr, sizeof(timeAPStr), "%p", localtime(&epoch));
        strftime(dateStr, sizeof(dateStr), "%a %b %e", localtime(&epoch)); // %e is space-padded


        // Check if clock positioning needs to be fixed (at 10 and 1)
        if ((localtime(&epoch)->tm_min == 0) && (localtime(&epoch)->tm_sec <= 3))
            fixPosition();


        time.updateText(timeStr);
        ampm.updateText(timeAPStr);
        date.updateText(dateStr);
    }


    void GfxClock::fixPosition()
    {
        // Time clock Text alignment fix - do not let it jump around due to
        // different widths of symbols
        float prevFix = xCoordFix;
        xCoordFix = 522;

        if (localtime(&epoch)->tm_hour % 12 < 10 && localtime(&epoch)->tm_hour % 12 > 0)
            xCoordFix = 530;

        if (prevFix != xCoordFix)
            time.setPos(xCoordFix, 33);
    }


    void GfxClock::renderTo(sf::RenderWindow &window)
    {
        time.renderTo(window);
        ampm.renderTo(window);
        date.renderTo(window);
    }
}