#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;


#ifndef WS4_ANIMICON_H
#define WS4_ANIMICON_H


namespace ws4
{
    class AnimIcon
    {
        int w{};
        int h{};
        int yPos{};
        sf::Vector2i sizeVec;
        sf::IntRect frame;
        sf::Sprite icon;


    public:
        AnimIcon(sf::Texture &texture, vector<int> posVec, int x, int y)
            : sizeVec(sf::Vector2i(posVec[0], posVec[2])),
              frame(sf::IntRect(sf::Vector2i(0, posVec[1]), sizeVec)),
              icon(sf::Sprite(texture))
        {
            w = posVec[0];
            h = posVec[2];
            yPos = posVec[1];
            icon.setTextureRect(frame);
            icon.setOrigin(sf::Vector2f(icon.getGlobalBounds().size.x/2, icon.getGlobalBounds().size.y/2));
            icon.setPosition(sf::Vector2f(x, y));
        }

        AnimIcon() = delete;

        void update();
        void switchFrame(int iconFrame);
        void renderTo(sf::RenderWindow &window);
    };
}

#endif //WS4_ANIMICON_H
