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
        sf::Vector2f scale = sf::Vector2f(1.5f, 1.5f);
        
        
    public:
        TextLabel(string text, sf::Font &font, string colorName, int charSize, int shLevel, 
                        float spacing, int x, int y, map<string, sf::Color> colorMap, short dir);
        TextLabel() = default;

        void renderTo(sf::RenderWindow &window);
        void updateText(string text);
        sf::String toUtf8String(string text);
        void alignRight();
        void alignLeft();
        void alignCenter();
    };
}

#endif //WS4_TEXTLABEL_H
