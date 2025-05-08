#include <SFML/Graphics.hpp>
#include <codecvt>
#include <array>
#include <map>

using std::string;
using std::vector;
using std::map;


#ifndef WS4_TEXTLABEL_H
#define WS4_TEXTLABEL_H


namespace ws4
{
    class TextLabel
    {
        // 0 - None, 1 - A bit larger than outline, 2.. 3..
        int shadowLevel = 1;
        double scaleFactor = 1.0;
        int dir = 0;
        sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f);

        sf::Text label;
        vector<sf::Text> shadowVec;
        
    public:
        TextLabel(string text, string fontName, string colorName, int charSize, int shLevel,
                        float spacing, int x, int y, short dir);
        TextLabel() = delete;

        void renderTo(sf::RenderWindow &window);
        void updateText(const string& text);
        void updateTextInPlace(const string& text);
        static sf::String toUtf8String(string text);
        void alignRight(sf::Text &lbl, int offset);
        void alignLeft(sf::Text &lbl, int offset);
        void alignCenter(sf::Text &lbl, int offset);
        void setPos(float x, float y);
        float getWidth();
        float getHeight();
    };
}

#endif //WS4_TEXTLABEL_H
