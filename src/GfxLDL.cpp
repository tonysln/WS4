#include "GfxLDL.h"
#include "GfxLoader.h"
#include "GfxManager.h"
#include "TextLabel.h"


namespace ws4
{
    GfxLDL::GfxLDL(map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap)
    {
        vertexObjs = 
        {
            buildQuad(0, 399, 640, 81, colorMap["#141414"]),
            buildQuad(0, 400, 640, 80, colorMap["#afafaf"]),
            buildQuad(0, 402, 640, 78, colorMap["#233270"])
        };

        textLabel = TextLabel("Currently at Moline", fontMap["Star4000"], "#d7d7d7", 30, 1, 1.0f, 62, 398, colorMap, 0);
    }


    void GfxLDL::setText(string text)
    {
        textLabel.updateText(text);
    }


    void GfxLDL::renderTo(sf::RenderWindow &window)
    {
        // Drawing vertex objects
        for (const auto& vObj : vertexObjs)
            window.draw(vObj.data(), 4, sf::TriangleStrip);


        // Animating text


        // Drawing text
        textLabel.renderTo(window);
    }


    void GfxLDL::scrollText()
    {

    }
}
