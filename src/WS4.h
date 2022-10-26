#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GfxScreen.h"
#include "GfxClock.h"
#include "MapCity.h"
#include "GfxLDL.h"
#include <vector>
#include <array>
#include <map>

using std::vector;
using std::string;
using std::array;
using std::map;


#ifndef WS4_WS4_H
#define WS4_WS4_H


namespace ws4 
{
    class WS4 
    {
        // Window & Rendered
        const short ANIM_FRAMES = 7;
        const short FPS = 30;
        const short WIN_WIDTH = 640;
        const short WIN_HEIGHT = 480;
        const float SCALE = 1.0f;
        const bool winBorders = true;
        const bool fullScreen = false;
        sf::RenderWindow window;
        sf::View view;


        // Timers & Counters
        int iconFrame = 0;
        float iconFrameCounter = 0.f;
        float sceneTime = 12.f;
        float LDLTime = 5.f;
        int dispLDLTimes = 2;
        int scrLDLTimes = 1;
        sf::Clock sceneTimer;
        sf::Clock LDLTimer;


        // Screens
        short scrIdx = 0;
        const vector<string> scr =
        {
            "Current-Conditions",
            "Latest-Observations",
            "Regional-Observations",
            "Local-Forecast-1",
            "Local-Forecast-2",
            "Local-Forecast-3",
            "Forecast-For",
            "Extended-Forecast",
            "Almanac",
        };
        void nextScreen();
        void prevScreen();


        // Graphics
        map<string, sf::Font> fontMap;
        map<string, sf::Color> colorMap;
        map<string, sf::Texture> textureMap;
        map<string, vector<int>> iconPosMap;
        vector<GfxScreen> screens;
        vector<MapCity> regMapCities;
        vector<MapCity> forcMapCities;
        bool showLogo = true;
        sf::Sprite logo;
        GfxClock clock;
        GfxLDL LDL;


        // Data
        int LDLStrIdx = 0;
        vector<string> LDLStrings;
        vector<string> LDLScrollStr;
        vector<string> cityXValues;
        vector<string> cityYValues;
        vector<vector<string>> data;


        // Music
        vector<string> songsPaths;
        bool musicStarted = false;
        bool musicEnabled = true;
        float volume = 20.f;
        int songIdx = 0;
        sf::Music musicPlayer;
        void changeSong();



    public:
        WS4();
        void loadMusic();
        void loadGraphics();
        void getNewData();
        void loadData();
        int runLoop();
    };

}

#endif //WS4_WS4_H