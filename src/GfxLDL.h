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
        bool scrollMode = false;
        int bufIdx = 0;
        int scrSpeed = 3;
        int x = 64;
        int y = 399;
        int offsetPxRight = 70.f;
        int offsetPxLeft = 90.f;
        float lagTime = 17.f;

        vector<array<sf::Vertex, 4>> vertexObjs;
        TextLabel textLabel;
        vector<string> wordBuf;
        string bufStrFull;
        sf::Clock bufTimer;

    public:
        explicit GfxLDL(const string& text);
        GfxLDL() = delete;

        void setText(const string& text);
        void useScroll(bool scroll);
        void renderTo(sf::RenderWindow &window);
        bool isUsingScroll();

        int scrolls = 0;
        int displays = 0;
    };
}

#endif //WS4_GFXLDL_H
