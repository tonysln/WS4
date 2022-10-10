#include <SFML/Graphics.hpp>
#include "TextLabel.h"
#include "AnimIcon.h"
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


    public:
        GfxScreen(vector<array<sf::Vertex, 4>> sbv, vector<TextLabel> st, vector<TextLabel> dt, vector<AnimIcon> ico);
        GfxScreen() = default;

        void updateText(vector<string> newText);
        void updateIcons();
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXSCREEN_H
