#include <SFML/Graphics.hpp>
#include "AnimIcon.h"
#include "TextLabel.h"
#include <string>

using std::string;


#ifndef WS4_MAPCITY_H
#define WS4_MAPCITY_H


namespace ws4
{
    class MapCity
    {
        AnimIcon icon;
        TextLabel name;
        TextLabel temp;
        int x = 0;
        int y = 0;

    public:
        MapCity(string nameText, string tempText, string xs, string ys, map<string, sf::Font> &fontMap,
                        map<string, sf::Color> &colorMap, sf::Texture &icoTxt, vector<int> icoPos);
        MapCity() = default;

        void updateTemp(string newTemp);
        void updateIcon();
        void switchFrames(int iconFrame);
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_MAPCITY_H
