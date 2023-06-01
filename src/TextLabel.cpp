#include "TextLabel.h"
#include "GfxLoader.h"
#include <utility>


namespace ws4
{
    TextLabel::TextLabel(string text, string fontName, string colorName, int charSize, int shLevel, float spacing, int x, int y, short dir)
    {
        label = sf::Text(toUtf8String(text), fontMap[fontName], charSize * scaleFactor);
        label.setFillColor(colorMap[std::move(colorName)]);
        label.setPosition(sf::Vector2f(x, y));
        label.setOutlineColor(colorMap["#0e0e0e"]);
        label.setOutlineThickness(1);
        label.setLetterSpacing(spacing);
        label.setScale(scale);

        // Set origin based on dir (0 = L, 1 = C, 2 = R)
        this->dir = dir;
        alignLeft(label, 0);
        if (dir > 1)
            alignRight(label, 0);
        else if (dir > 0)
            alignCenter(label, 0);


        shadowLevel = shLevel;
        for (int i = 0; i <= shadowLevel; i++)
        {
            sf::Text shadow(toUtf8String(text), fontMap[fontName], charSize * scaleFactor);
            shadow.setFillColor(colorMap["#0e0e0e"]);
            shadow.setPosition(sf::Vector2f(x + shadowLevel, y + shadowLevel));
            shadow.setOutlineColor(colorMap["#0e0e0e"]);
            shadow.setOutlineThickness(0);
            shadow.setLetterSpacing(spacing);
            shadow.setScale(scale);
            shadow.setOrigin(label.getOrigin());

            alignLeft(shadow, i-shadowLevel+2);
            if (dir > 1)
                alignRight(shadow, shadowLevel);
            else if (dir > 0)
                alignCenter(shadow, shadowLevel);

            shadowVec.push_back(shadow);
        }
    }

    void TextLabel::alignRight(sf::Text &lbl, int offset)
    {
        sf::Vector2f orig(lbl.getLocalBounds().width + offset, 0);
        lbl.setOrigin(orig);
    }

    void TextLabel::alignLeft(sf::Text &lbl, int offset)
    {
        sf::Vector2f orig(0 + offset, 0);
        lbl.setOrigin(orig);
    }

    void TextLabel::alignCenter(sf::Text &lbl, int offset)
    {
        sf::Vector2f orig(lbl.getLocalBounds().width / 2 + offset, 0);
        lbl.setOrigin(orig);
    }


    void TextLabel::setPos(float x, float y)
    {
        label.setPosition(sf::Vector2f(x, y));
        for (int i = 0; i <= shadowLevel; ++i)
        {
            shadowVec.at(i).setPosition(sf::Vector2f(x + shadowLevel, y + shadowLevel));
        }
    }


    void TextLabel::updateText(const string& text)
    {
        label.setString(toUtf8String(text));

        alignLeft(label, 0);
        if (dir > 1)
            alignRight(label, 0);
        else if (dir > 0)
            alignCenter(label, 0);

        int i = 0;
        for (auto& shadow : shadowVec)
        {
            shadow.setString(toUtf8String(text));

            alignLeft(shadow, i-shadowLevel+2);
            if (dir > 1)
                alignRight(shadow, shadowLevel);
            else if (dir > 0)
                alignCenter(shadow, shadowLevel);

            i++;
        }
    }


    void TextLabel::updateTextInPlace(const string& text)
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

    float TextLabel::getHeight()
    {
        return label.getGlobalBounds().height;
    }


    void TextLabel::renderTo(sf::RenderWindow &window)
    {
        for (const auto& sObj : shadowVec)
            window.draw(sObj);

        window.draw(label);
    }
}
