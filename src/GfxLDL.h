#include <SFML/Graphics.hpp>
#include "TextLabel.h"
#include <vector>
#include <array>
#include <queue>
#include <map>

using std::vector;
using std::string;
using std::array;
using std::queue;
using std::map;


#ifndef WS4_GFXLDL_H
#define WS4_GFXLDL_H


namespace ws4
{
    class GfxLDL
    {
        vector<array<sf::Vertex, 4>> vertexObjs;
        ws4::TextLabel textLabel;
        bool scrollMode = false;
        queue<string> wordBuf;
        int bufferCount = -1;
        int scrSpeed = 2;
        int x = 62;
        int y = 398;
        int scrolls = 0;


    public:
        GfxLDL(string text, map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap);
        GfxLDL() = default;

        void setText(string text);
        void useScroll(bool scroll);
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_GFXLDL_H
