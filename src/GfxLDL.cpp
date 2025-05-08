#include "GfxLDL.h"
#include "GfxLoader.h"
#include "TextLabel.h"
#include <sstream>
#include <utility>


namespace ws4
{
    GfxLDL::GfxLDL(const string& text):
    textLabel("", "Star4000", "#d7d7d7", 30, 1, 1.0f, x, y, 0) {
        vertexObjs =
        {
            buildQuad(0, 399, 640, 81, "#141414"),
            buildQuad(0, 400, 640, 80, "#afafaf"),
            buildQuad(0, 402, 640, 78, "#233270")
        };

        // textLabel = TextLabel();
        setText(text);
    }


    void GfxLDL::setText(const string& text)
    {
        if (scrollMode)
        {
            textLabel.updateText(text);
            return;
        }

        wordBuf.clear();
        bufStrFull = "";
        stringstream lnStream("");
        string seg;
        lnStream << text;

        while(getline(lnStream, seg, ' '))
            wordBuf.push_back(seg);

        bufIdx = 0;
        bufStrFull = wordBuf.at(bufIdx);
        textLabel.updateText(bufStrFull);
        bufTimer.restart();
    }


    void GfxLDL::useScroll(bool scroll)
    {
        scrollMode = scroll;
        if (scrollMode)
        {
            scrolls = 0;
            textLabel.updateText("");
            x = 640 + offsetPxRight;
            textLabel.setPos(x, y);
        }
        else
        {
            displays = 0;
            bufIdx = -1;
            x = 64;
            textLabel.setPos(x, y);
        }
    }


    bool GfxLDL::isUsingScroll()
    {
        return scrollMode;
    }


    void GfxLDL::renderTo(sf::RenderWindow &window)
    {
        // Drawing vertex objects
        for (const auto& vObj : vertexObjs)
            window.draw(vObj.data(), 4, sf::PrimitiveType::TriangleStrip);

        // Animating text
        if (scrollMode)
        {
            x -= scrSpeed;
            textLabel.setPos(x, y);

            if (x + textLabel.getWidth() <= -offsetPxLeft)
            {
                x = 640 + offsetPxRight;
                scrolls++;
            }
        }
        else if (!wordBuf.empty() && bufIdx > -1 && bufIdx < wordBuf.size()-1)
        {
            if (bufTimer.getElapsedTime().asMilliseconds() > lagTime)
            {
                bufIdx++;
                bufStrFull += " ";
                bufStrFull += wordBuf.at(bufIdx);
                textLabel.updateText(bufStrFull);
                bufTimer.restart();
            }
        }

        // Drawing text
        textLabel.renderTo(window);
    }

}
