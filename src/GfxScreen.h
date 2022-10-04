#include <SFML/Graphics.hpp>
#include "TextLabel.h"
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
        vector<array<sf::Vertex, 4>> vertexObjs;
        vector<sf::Sprite> animIcons;
        vector<ws4::TextLabel> textLabels;


    public:
        GfxScreen(vector<array<sf::Vertex, 4>> vObj, vector<ws4::TextLabel> tLbls);
        GfxScreen() = default;

        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXSCREEN_H
