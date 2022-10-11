#include <SFML/Graphics.hpp>
#include "TextLabel.h"
#include "AnimIcon.h"
#include "MapCity.h"
#include <vector>
#include <array>
#include <map>

using std::vector;
using std::string;
using std::array;
using std::map;


#ifndef WS4_GFXSCREEN_H
#define WS4_GFXSCREEN_H


namespace ws4
{
    class GfxScreen
    {   
        vector<array<sf::Vertex, 4>> staticBgVertices;
        vector<TextLabel> dynamicText;
        vector<TextLabel> staticText;
        vector<AnimIcon> icons;
        vector<MapCity> cities;
        sf::Sprite map;
        bool mapScr = false;


    public:
        GfxScreen(vector<array< sf::Vertex, 4>> sbv, vector<TextLabel> st, vector<TextLabel> dt);
        GfxScreen(vector<array< sf::Vertex, 4>> sbv, vector<TextLabel> st);
        GfxScreen() = default;

        void updateText(const vector<string>& newText);
        void updateIcons();
        void loadMap(sf::Texture &texture, int xPos, int yPos);
        void loadIcons(vector<AnimIcon> iconVec);
        void loadCities(vector<MapCity> cityVec);
        void switchIconFrames(int iconFrame);
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXSCREEN_H
