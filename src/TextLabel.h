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
        sf::Text label;
        vector<sf::Text> shadowVec;

        // 0 - None, 1 - A bit larger than outline, 2.. 3..
        int shadowLevel = 1;
        double scaleFactor = 0.67;
        int dir = 0;
        sf::Vector2f scale = sf::Vector2f(1.5f, 1.5f);
        
        
    public:
        TextLabel(string text, sf::Font &font, string colorName, int charSize, int shLevel,
                        float spacing, int x, int y, map<string, sf::Color> colorMap, short dir);
        TextLabel() = default;

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
