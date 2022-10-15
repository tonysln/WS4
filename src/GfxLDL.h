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
        vector<array<sf::Vertex, 4>> vertexObjs;
        ws4::TextLabel textLabel;
        bool scrollMode = false;
        vector<string> wordBuf;
        string bufStrFull;
        sf::Clock bufTimer;
        int bufIdx = -1;
        int scrSpeed = 2;
        int x = 62;
        int y = 398;
        int offsetPxRight = 60.f;
        int offsetPxLeft = 75.f;
        float lagTime = 18.f;



    public:
        GfxLDL(string text, map<string, sf::Color> &colorMap, map<string, sf::Font> &fontMap);
        GfxLDL() = default;

        void setText(const string& text);
        void useScroll(bool scroll);
        void renderTo(sf::RenderWindow &window);
        bool isUsingScroll();

        int scrolls = 0;
        int displays = 0;
    };
}

#endif //WS4_GFXLDL_H
