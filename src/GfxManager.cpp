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

        loadCurrentConditions(screens, fontMap, colorMap);
        loadLatestObservations(screens, fontMap, colorMap);
        loadRegionalObservations(screens, fontMap, colorMap);
        loadLocalForecast(screens, fontMap, colorMap);
        loadRegionalForecast(screens, fontMap, colorMap);
        loadExtendedForecast(screens, fontMap, colorMap);
        loadAlmanac(screens, fontMap, colorMap);


        LDL = GfxLDL(colorMap, fontMap);
    }


    void GfxManager::updateData()
    {

    }


    void GfxManager::renderAllTo(sf::RenderWindow &window, short scrIdx)
    {
        // Clear window
        window.clear(colorMap["#1c0a57"]);

        // Render current scene
        screens.at(scrIdx).renderTo(window);

        // Render time & date
        clock.update();
        clock.renderTo(window);

        // Render LDL
        LDL.renderTo(window);
    }
}