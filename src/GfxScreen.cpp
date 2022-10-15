#include "GfxScreen.h"
#include <utility>


namespace ws4
{
    GfxScreen::GfxScreen(vector<array<sf::Vertex, 4>> sbv, vector<TextLabel> st, vector<TextLabel> dt)
    {
        staticBgVertices = std::move(sbv);
        staticText = std::move(st);
        dynamicText = std::move(dt);
    }

    GfxScreen::GfxScreen(vector<array<sf::Vertex, 4>> sbv, vector<TextLabel> st)
    {
        staticBgVertices = std::move(sbv);
        staticText = std::move(st);
    }


    void GfxScreen::updateText(const vector<string>& newText)
    {
        int i = 0;
        for (const string& textStr : newText)
            dynamicText[i++].updateText(textStr);
    }


    void GfxScreen::updateIcons()
    {

    }


    void GfxScreen::loadMap(sf::Texture &texture, int xPos, int yPos)
    {
        map = sf::Sprite(texture);
//        map.setScale(sf::Vector2f(1.8f, 1.8f));
        map.setTextureRect(sf::IntRect(sf::Vector2i(xPos, yPos), sf::Vector2i(640, 308)));
        map.setPosition(sf::Vector2f(0, 90));
        mapScr = true;
    }


    void GfxScreen::loadIcons(vector<AnimIcon> iconVec)
    {
        icons = std::move(iconVec);
    }


    void GfxScreen::loadCities(vector<MapCity> cityVec)
    {
        cities = std::move(cityVec);
    }


    void GfxScreen::switchIconFrames(int iconFrame)
    {
        for (auto& iObj : icons)
            iObj.switchFrame(iconFrame);

        for (auto& cObj : cities)
            cObj.switchFrames(iconFrame);
    }


    void GfxScreen::renderTo(sf::RenderWindow &window)
    {
        for (const auto& vObj : staticBgVertices)
            window.draw(vObj.data(), 4, sf::TriangleStrip);

        if (mapScr)
            window.draw(map);

        for (auto& cObj : cities)
            cObj.renderTo(window);

        for (auto& iObj : icons)
            iObj.renderTo(window);

        for (auto& tObj : staticText)
            tObj.renderTo(window);

        for (auto& tObj : dynamicText)
            tObj.renderTo(window);
    }
}