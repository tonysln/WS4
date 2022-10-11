#include "TextLabel.h"
#include <utility>


namespace ws4
{
    TextLabel::TextLabel(string text, sf::Font &font, string colorName, int charSize,
                            int shLevel, float spacing, int x, int y, map<string, sf::Color> colorMap, short dir)
    {
        label = sf::Text(toUtf8String(std::move(text)), font, charSize * scaleFactor);
        label.setFillColor(colorMap[std::move(colorName)]);
        label.setPosition(sf::Vector2f(x, y));
        label.setOutlineColor(colorMap["#0e0e0e"]);
        label.setOutlineThickness(1);
        label.setLetterSpacing(spacing);
        label.setScale(scale);

        // Set origin based on dir (0 = L, 1 = C, 2 = R)
        alignLeft();
        if (dir > 1)
            alignRight();
        else if (dir > 0)
            alignCenter();


        shadowLevel = shLevel;
        for (int i = 0; i < shadowLevel; ++i)
        {
            sf::Text shadow(toUtf8String(text), font, charSize * scaleFactor);
            shadow.setFillColor(colorMap["#0e0e0e"]);
            shadow.setPosition(sf::Vector2f(x + shadowLevel, y + shadowLevel));
            shadow.setOutlineColor(colorMap["#0e0e0e"]);
            shadow.setOutlineThickness(0);
            shadow.setLetterSpacing(spacing);
            shadow.setScale(scale);
            shadow.setOrigin(label.getOrigin());

            shadowVec.push_back(shadow);
        }
    }

    void TextLabel::alignRight()
    {
        sf::Vector2f orig(label.getLocalBounds().width, 0);
        label.setOrigin(orig);
    }

    void TextLabel::alignLeft()
    {
        sf::Vector2f orig(0, 0);
        label.setOrigin(orig);
    }

    void TextLabel::alignCenter()
    {
        sf::Vector2f orig(label.getLocalBounds().width / 2, 0);
        label.setOrigin(orig);
    }


    void TextLabel::setPos(float x, float y)
    {
        label.setPosition(sf::Vector2f(x, y));
        for (int i = 0; i < shadowLevel; ++i)
        {
            shadowVec.at(i).setPosition(sf::Vector2f(x + shadowLevel, y + shadowLevel));
        }
    }


    void TextLabel::updateText(const string& text)
    {
        label.setString(toUtf8String(text));
        for (auto& shadow : shadowVec)
            shadow.setString(toUtf8String(text));
    }


    sf::String TextLabel::toUtf8String(string text)
    {
        return sf::String::fromUtf8(text.begin(), text.end());
    }


    float TextLabel::getWidth()
    {
        return label.getGlobalBounds().width;
    }


    void TextLabel::renderTo(sf::RenderWindow &window)
    {
        for (const auto& sObj : shadowVec)
            window.draw(sObj);

        window.draw(label);
    }
}
