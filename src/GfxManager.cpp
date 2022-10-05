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

        // TODO draw offscreen?
        
        loadStaticScreenVec(staticScreenVec, fontMap, colorMap);

        
        LDL = GfxLDL(colorMap, fontMap);
    }


    void GfxManager::renderAllTo(sf::RenderWindow &window, short scrIdx)
    {
        // Clear window
        window.clear(colorMap["#1c0a57"]);

        // Render current scene static
        staticScreenVec.at(scrIdx).renderTo(window);

        // Render current scene dynamic


        // Render time & date


        // Render LDL
        LDL.renderTo(window);
    }
}