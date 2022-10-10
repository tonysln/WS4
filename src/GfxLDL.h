#include <SFML/Graphics.hpp>
#include "TextLabel.h"
#include <vector>
#include <array>
#include <map>

using std::vector;
using std::string;
using std::array;
using std::map;


#ifndef WS4_GFXLDL_H
#define WS4_GFXLDL_H


namespace ws4
{
    class GfxLDL
    {
        // Lower Display Line

        vector<array<sf::Vertex, 4>> vertexObjs;
        ws4::TextLabel textLabel;

        void scrollText();


    public:
        GfxLDL(string text, map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap);
        GfxLDL() = default;

        void renderTo(sf::RenderWindow &window);
        void setText(string text);
    };
}

#endif //WS4_GFXLDL_H
