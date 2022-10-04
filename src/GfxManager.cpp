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

        // TODO move to gfxloader
        staticScreenVec.push_back
        (
            // Screen 0 - "Current Conditions"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, colorMap["#2652b2"]),
                    buildQuad(55, 94, 527, 302, colorMap["#254ba3"]),
                    buildQuad(57, 96, 523, 298, colorMap["#254698"]),
                    buildQuad(59, 98, 519, 294, colorMap["#24408c"]),
                    buildQuad(61, 100, 515, 290, colorMap["#233a80"]),
                    buildQuad(63, 102, 511, 286, colorMap["#223474"]),
                    buildQuad(65, 104, 507, 282, colorMap["#222f69"]),
                    buildQuad(66, 105, 506, 281, colorMap["#212b60"]),
                    buildQuad(67, 106, 505, 280, colorMap["#21285a"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Current", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 21, colorMap, 0),
                    TextLabel("Conditions", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                    TextLabel("Humidity:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 141, colorMap, 0),
                    TextLabel("Dewpoint:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 181, colorMap, 0),
                    TextLabel("Ceiling:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 225, colorMap, 0),
                    TextLabel("Visibility:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 267, colorMap, 0),
                    TextLabel("Pressure:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 308, colorMap, 0),
                }
            }
        );

        staticScreenVec.push_back
        (
            // Screen 1 - "Latest Observations"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, colorMap["#2652b2"]),
                    buildQuad(55, 94, 527, 302, colorMap["#254ba3"]),
                    buildQuad(57, 96, 523, 298, colorMap["#254698"]),
                    buildQuad(59, 98, 519, 294, colorMap["#24408c"]),
                    buildQuad(61, 100, 515, 290, colorMap["#233a80"]),
                    buildQuad(63, 102, 511, 286, colorMap["#223474"]),
                    buildQuad(65, 104, 507, 282, colorMap["#222f69"]),
                    buildQuad(66, 105, 506, 281, colorMap["#212b60"]),
                    buildQuad(67, 106, 505, 280, colorMap["#21285a"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Latest Observations", fontMap["Star4000"], "#cdb900", 34, 3, 0.5, 163, 35, colorMap, 0),
                    TextLabel("Fº", fontMap["Star4000-Small"], "#d7d7d7", 30, 0, 1.0, 305, 78, colorMap, 0),
                    TextLabel("WEATHER", fontMap["Star4000-Small"], "#d7d7d7", 30, 0, 1.0, 365, 78, colorMap, 0),
                    TextLabel("WIND", fontMap["Star4000-Small"], "#d7d7d7", 30, 0, 1.0, 505, 78, colorMap, 0),
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
        staticScreenVec.at(scrIdx).renderTo(window);

        // Render current scene dynamic


        // Render time & date


        // Render LDL
        LDL.renderTo(window);
    }
}