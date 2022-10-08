#include <SFML/Graphics.hpp>


#ifndef WS4_ANIMICON_H
#define WS4_ANIMICON_H


namespace ws4
{
    class AnimIcon
    {
        sf::Sprite icon;
        sf::IntRect frame;
        int w;
        int h;
        int x;
        int y;


    public:
        AnimIcon();
        void nextFrane();
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_ANIMICON_H
