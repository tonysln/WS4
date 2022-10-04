#include <SFML/Graphics.hpp>
#include <codecvt>
#include <array>
#include <map>

using std::string;
using std::map;


#ifndef WS4_TEXTLABEL_H
#define WS4_TEXTLABEL_H


namespace ws4
{
    class TextLabel
    {
        sf::Text label;
        sf::Text shadow;

        // 0 - None, 1 - A bit larger than outline, 2.. 3..
        int shadowLevel; 
        int shadowOffset = 3;
        double scaleFactor = 0.67;
        sf::Vector2f scale = sf::Vector2f(1.5f, 1.5f);
        
        
    public:
        TextLabel(string text, sf::Font &font, string colorName, int charSize, int shLevel, 
                                            float spacing, int x, int y, map<string, sf::Color> colorMap);
        TextLabel() = default;

        void renderTo(sf::RenderWindow &window);
        void updateText(string text);
        sf::String toUTF8(string text);
    };
}

#endif //WS4_TEXTLABEL_H
