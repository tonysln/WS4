#include <SFML/Graphics.hpp>
#include "GfxScreen.h"
#include "GfxLDL.h"
#include <vector>
#include <array>
#include <map>

using std::vector;
using std::string;
using std::array;
using std::map;


#ifndef WS4_GFXMANAGER_H
#define WS4_GFXMANAGER_H


namespace ws4
{
    class GfxManager
    {   
        map<string, sf::Font> fontMap;
        map<string, sf::Color> colorMap;
        map<string, sf::Texture> textureMap;

        map<string, map<string, vector<int>>> iconPos;
        vector<GfxScreen> staticScreenVec;
        GfxLDL LDL;

        // TODO static and dynamic stuff

        sf::Texture mainScreenTexture;


    public:
        GfxManager();

        void renderAllTo(sf::RenderWindow &window, short scrIdx);
    };
}

#endif //WS4_GFXMANAGER_H
