#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;


#ifndef WS4_ANIMICON_H
#define WS4_ANIMICON_H


namespace ws4
{
    class AnimIcon
    {
        sf::Sprite icon;
        sf::IntRect frame;
        sf::Vector2i sizeVec;
        int yPos;
        int w;
        int h;


    public:
        AnimIcon(sf::Texture &texture, vector<int> posVec, int x, int y);
        AnimIcon() = default;

        void update();
        void switchFrame(int iconFrame);
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_ANIMICON_H
