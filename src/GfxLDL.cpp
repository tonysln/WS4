#include "GfxLDL.h"
#include <utility>
#include "GfxLoader.h"
#include "TextLabel.h"


namespace ws4
{
    GfxLDL::GfxLDL(string text, map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap)
    {
        vertexObjs = 
        {
            buildQuad(0, 399, 640, 81, colorMap["#141414"]),
            buildQuad(0, 400, 640, 80, colorMap["#afafaf"]),
            buildQuad(0, 402, 640, 78, colorMap["#233270"])
        };

        textLabel = TextLabel(std::move(text), fontMap["Star4000"], "#d7d7d7", 30, 1, 1.0f, x, y, colorMap, 0);
    }


    void GfxLDL::setText(string text)
    {
        if (scrollMode)
        {
            textLabel.updateText(std::move(text));
            return;
        }

        // Split into words, add to queue
        // set text label to first word
        bufferCount = 300; // set as num of words * ...
    }


    void GfxLDL::useScroll(bool scroll)
    {
        scrollMode = scroll;
        if (scrollMode)
        {
            textLabel.updateText("");
            x = 640 + 50;
        }
        else
        {
            x = 62;
        }
    }


    void GfxLDL::renderTo(sf::RenderWindow &window)
    {
        // Drawing vertex objects
        for (const auto& vObj : vertexObjs)
            window.draw(vObj.data(), 4, sf::TriangleStrip);

        // Animating text
        if (scrollMode)
        {
            x -= scrSpeed;
            textLabel.setPos(x, y);

            if (x + textLabel.getWidth() <= -50)
            {
                x = 640 + 50;
                scrolls++;
            }
        }
        else if (bufferCount > 0)
        {
            // Add next word from queue to textLabel
            // Update text label
            // decrement buffer count to wait
        }

        // Drawing text
        textLabel.renderTo(window);
    }

}
