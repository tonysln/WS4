#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GfxManager.h"
#include <vector>
#include <time.h>
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
        const short FPS = 7;
        const float SCALE = 1.0f;
        const short WIN_WIDTH = 640;
        const short WIN_HEIGHT = 480;
        const short ANIM_FRAMES = 7;

        sf::RenderWindow window;
        sf::ContextSettings sts;
        sf::View view;

        std::time_t epoch = std::time(nullptr);
        char timeStr[12];
        char timeAPStr[6];
        char dateStr[12];
        sf::Clock sceneTimer;
        sf::Time elapsedScene;

        map<string, sf::Font> fM;
        map<string, sf::Color> cM;
        map<string, vector<sf::Text>> tM;
        map<string, vector<array<sf::Vertex, 4>>> vM;
        map<string, map<string, vector<int>>> iconPos;
        map<string, vector<sf::Sprite>> iM;

        ws4::GfxManager gfxManager;
        
        sf::Texture moonPhasesTexture;
        sf::Texture curCondTexture;
        sf::Texture extForcTexture;
        sf::Texture regMapsTexture;
        sf::Texture regBaseMapTexture;
        int animFrame;

        
        sf::Music musicPlayer;
        map<string, map<string, string>> dM;
        const vector<string> scr = 
        {
            "Current-Conditions",
            "Latest-Observations",
            "Local-Forecast-1",
            "Local-Forecast-2",
            "Extended-Forecast",
            "Almanac",
            "Forecast-For",
            // "Travel-Forecast",
            // "Air-Quality",
        };
        short cur = 0;
        short icoCt = 0;
        float sceneTime = 10.f;

        void nextScreen();
        void prevScreen();
        void nextScreenUpdate();
        void drawGraphics();
        void drawText();
        void changeSong();


    public:
        WS4();
        void loadFonts();
        void loadTextures();
        void loadGraphics();
        void loadData();
        void loadMusic();
        int runLoop();
        void loadLDL();
    };

}

#endif //WS4_WS4_H