#include "GfxManager.h"
#include "GfxScreen.h"
#include "GfxLoader.h"
#include "WS4.h"

using std::initializer_list;


namespace ws4
{
    GfxManager::GfxManager()
    {
        fontMap = loadFontMap();
        colorMap = loadColorMap();
        textureMap = loadTextureMap();
        iconPosMap = loadIconPositionsMap();


        loadCurrentConditions(screens, fontMap, colorMap);          // [0]
        screens.at(0).loadIcons({
            AnimIcon(textureMap["CC"], iconPosMap["CC_Ice-Snow"], 178, 230)
        });

        loadLatestObservations(screens, fontMap, colorMap);         // [1]
        loadRegionalObservations(screens, fontMap, colorMap);       // [2]
        screens.at(2).loadCities({
            MapCity("Oklahoma", "62", 100, 100, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Rain"]),
            MapCity("Ponca City", "61", 140, 250, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Sunny"]),
            MapCity("Tulsa", "65", 290, 110, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Cloudy"]),
            MapCity("Altus", "71", 230, 180, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Mostly-Cloudy"]),
            MapCity("Gage", "59", 410, 130, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Thunderstorm"]),
            MapCity("Tinker AFB", "62", 400, 310, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Thunderstorm"])
        });

        loadLocalForecast(screens, fontMap, colorMap);              // [3], [4], [5]
        loadRegionalForecast(screens, fontMap, colorMap);           // [6]
//        screens.at(6).loadCities({});

        loadExtendedForecast(screens, fontMap, colorMap);           // [7]
        screens.at(7).loadIcons({
            AnimIcon(textureMap["EF"], iconPosMap["EF_Thunderstorms"], 120, 200),
            AnimIcon(textureMap["EF"], iconPosMap["EF_Mostly-Cloudy"], 320, 200),
            AnimIcon(textureMap["EF"], iconPosMap["EF_Snow-to-Rain"], 510, 200),
        });
        loadAlmanac(screens, fontMap, colorMap);                    // [8]
        screens.at(8).loadIcons({
            AnimIcon(textureMap["Moon"], iconPosMap["M_New"], 135, 320),
            AnimIcon(textureMap["Moon"], iconPosMap["M_First"], 255, 320),
            AnimIcon(textureMap["Moon"], iconPosMap["M_Full"], 375, 320),
            AnimIcon(textureMap["Moon"], iconPosMap["M_Last"], 495, 320)
        });


        LDL = GfxLDL("Currently at Moline", colorMap, fontMap);
        clock = GfxClock(colorMap, fontMap);
    }


    void GfxManager::updateData()
    {

    }


    void GfxManager::renderAllTo(sf::RenderWindow &window, short scrIdx)
    {
        // Clear window
        window.clear(colorMap["#1c0a57"]);

        // Advance through icon animation
        iconFrameCounter++;
        if (iconFrameCounter >= WS4::FPS / WS4::ANIM_FRAMES)
        {
            iconFrame = (iconFrame + 1) % WS4::ANIM_FRAMES;
            screens.at(scrIdx).switchIconFrames(iconFrame);
            iconFrameCounter = 0;
        }

        // Render current scene
        screens.at(scrIdx).renderTo(window);

        // Render time & date
        clock.update();
        clock.renderTo(window);

        // Render LDL
        LDL.renderTo(window);
    }
}