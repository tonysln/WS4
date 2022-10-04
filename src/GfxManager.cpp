#include "GfxManager.h"
#include "GfxScreen.h"
#include "GfxLoader.h"

using std::initializer_list;


namespace ws4
{
    GfxManager::GfxManager()
    {
        fontMap = loadFontMap();
        colorMap = loadColorMap();
        textureMap = loadTextureMap();

        screenVec.push_back
        (
            GfxScreen {
                vector {
                    buildQuad(110,110,100,100,colorMap["#0e0e0e"]),
                    buildQuad(200,200,100,100,colorMap["#0e0e0e"])
                }, 
                vector {
                    TextLabel("Moline", fontMap["Star4000"], "#d7d7d7", 32, 2, 0.8, 100, 100, colorMap),
                    TextLabel("Testing", fontMap["Star4000-Large"], "#d7d7d7", 28, 2, 0.5, 200, 200, colorMap)
                }
            }
        );

        
        LDL = GfxLDL(colorMap, fontMap);
    }


    void GfxManager::renderAllTo(sf::RenderWindow &window, short scrIdx)
    {
        // Clear window
        window.clear(colorMap["#1c0a57"]);

        // Render current scene static
        screenVec.at(scrIdx).renderTo(window);

        // Render current scene dynamic


        // Render time & date


        // Render LDL
        LDL.renderTo(window);
    }
}