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
        int x = 0;
        int y = 0;
        TextLabel name;
        TextLabel temp;
        AnimIcon icon;

    public:
        MapCity(string nameText, string tempText, string xs, string ys, sf::Texture &icoTxt, vector<int> icoPos);
        MapCity() = delete;

        void updateTemp(const string& newTemp);
        void updateIcon();
        void switchFrames(int iconFrame);
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_MAPCITY_H
