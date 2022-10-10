#include "AnimIcon.h"


namespace ws4
{
    AnimIcon::AnimIcon(sf::Texture &texture, vector<int> posVec, int x, int y)
    {
        w = posVec[0];
        yPos = posVec[1];
        h = posVec[2];

        sizeVec = sf::Vector2i(w, h);
        frame = sf::IntRect(sf::Vector2i(0, yPos), sizeVec);
        icon = sf::Sprite(texture);
        icon.setTextureRect(frame);
        icon.setOrigin(sf::Vector2f(icon.getGlobalBounds().width/2, icon.getGlobalBounds().height/2));
        icon.setPosition(sf::Vector2f(x, y));
    }


    void AnimIcon::update()
    {

    }


    void AnimIcon::switchFrame(int iconFrame)
    {
        frame = sf::IntRect(sf::Vector2i(w * iconFrame, yPos), sizeVec);
        icon.setTextureRect(frame);
    }


    void AnimIcon::renderTo(sf::RenderWindow &window)
    {
        window.draw(icon);
    }
}