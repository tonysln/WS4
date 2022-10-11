#include "MapCity.h"

namespace ws4
{
    MapCity::MapCity(string nameText, string tempText, int x, int y, map<string, sf::Font> &fontMap,
                            map<string, sf::Color> &colorMap, sf::Texture &icoTxt, vector<int> icoPos)
    {
        this->x = x;
        this->y = y;
        // TODO better pos calculation

        name = TextLabel(std::move(nameText), fontMap["Star4000"], "#d7d7d7",
                                            30, 1, 0.6f, x, y, colorMap, 0);
        temp = TextLabel(std::move(tempText), fontMap["Star4000-Large-Compressed"], "#cdb900",
                                    34, 1, 1.0f, x + 18, y + 33, colorMap, 0);
        icon = AnimIcon(icoTxt, icoPos, x + 70, y + 44);
    }


    void MapCity::updateTemp(string newTemp) {
        temp.updateText(newTemp);
    }


    void MapCity::updateIcon()
    {

    }


    void MapCity::switchFrames(int iconFrame)
    {
        icon.switchFrame(iconFrame);
    }


    void MapCity::renderTo(sf::RenderWindow &window)
    {
        icon.renderTo(window);
        temp.renderTo(window);
        name.renderTo(window);
    }
}