#include <SFML/Graphics.hpp>
#include "AnimIcon.h"
#include "TextLabel.h"

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
        int x;
        int y;

    public:
        MapCity();
        void updateTemp(string newTemp);
        void updateIcon();
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_MAPCITY_H
