#include "GfxScreen.h"
#include "TextLabel.h"


namespace ws4
{
    GfxScreen::GfxScreen(vector<array<sf::Vertex, 4>> vObj, vector<ws4::TextLabel> tLbls)
    {
        vertexObjs = vObj;
        textLabels = tLbls;
    }


    void GfxScreen::renderTo(sf::RenderWindow &window)
    {
        for (const auto& vObj : vertexObjs)
            window.draw(vObj.data(), 4, sf::TriangleStrip);

        for (auto& tObj : textLabels)
            tObj.renderTo(window);
    }
}