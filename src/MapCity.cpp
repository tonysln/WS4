#include "MapCity.h"


namespace ws4
{
    MapCity::MapCity(string nameText, string tempText, string xs, string ys, map<string, sf::Font> &fontMap,
                            map<string, sf::Color> &colorMap, sf::Texture &icoTxt, vector<int> icoPos)
    {
        x = std::stoi(xs);
        y = std::stoi(ys);

        name = TextLabel(std::move(nameText), fontMap["Star4000"], "#d7d7d7", 30, 1, 0.6f, x, y, colorMap, 1);
        temp = TextLabel(std::move(tempText), fontMap["Star4000-Large-Compressed"], "#cdb900", 34, 1, 1.0f, x, y, colorMap, 1);

        name.setPos(x, y - name.getHeight());
        temp.setPos(x - temp.getWidth(), y + name.getHeight() / 2 - 4);
        icon = AnimIcon(icoTxt, icoPos, x + temp.getWidth() / 2, y + name.getHeight());
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