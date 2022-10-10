#include "GfxScreen.h"


namespace ws4
{
    GfxScreen::GfxScreen(vector<array<sf::Vertex, 4>> sbv, vector<TextLabel> st, vector<TextLabel> dt, vector<AnimIcon> ico)
    {
        staticBgVertices = sbv;
        staticText = st;
        dynamicText = dt;
        icons = ico;
    }


    void GfxScreen::updateText(vector<string> newText)
    {
        int i = 0;
        for (string textStr : newText)
            dynamicText[i++].updateText(textStr);
    }


    void GfxScreen::updateIcons()
    {

    }


    void GfxScreen::renderTo(sf::RenderWindow &window)
    {
        for (const auto& vObj : staticBgVertices)
            window.draw(vObj.data(), 4, sf::TriangleStrip);

        for (auto& iObj : icons)
            iObj.renderTo(window);

        for (auto& tObj : staticText)
            tObj.renderTo(window);

        for (auto& tObj : dynamicText)
            tObj.renderTo(window);
    }
}