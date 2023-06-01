#include "AnimIcon.h"


namespace ws4
{
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