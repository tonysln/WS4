#include "TextLabel.h"
#include "GfxManager.h"


namespace ws4
{
    TextLabel::TextLabel(string text, sf::Font &font, string colorName, int charSize, 
                            int shLevel, float spacing, int x, int y, map<string, sf::Color> colorMap)
    {
        shadowLevel = shLevel;
        label = sf::Text(toUTF8(text), font, charSize * scaleFactor);

        // Calculate origin/alignment
        sf::Vector2f orig(0, 0);
        // if (align == 'r')
        //     orig.x = tM[curScene].back().getLocalBounds().width;
        // if (align == 'c')
        //     orig.x = tM[curScene].back().getLocalBounds().width / 2;

        label.setOrigin(orig);
        label.setScale(scale);

        label.setFillColor(colorMap[colorName]);
        label.setPosition(sf::Vector2f(x, y));
        label.setOutlineColor(colorMap["#0e0e0e"]);
        label.setOutlineThickness(1);
        label.setLetterSpacing(spacing);
    }


    void TextLabel::updateText(string text)
    {
        label.setString(toUTF8(text));
    }


    sf::String TextLabel::toUTF8(string text)
    {
        return sf::String::fromUtf8(text.begin(), text.end());
    }


    void TextLabel::renderTo(sf::RenderWindow &window)
    {
        window.draw(label);
    }
}
