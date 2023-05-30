//#include "GfxLoader.h"
#include "DataProc.h"
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include "WS4.h"

namespace fs =  std::filesystem;
using std::to_string;
using std::localtime;
using std::strftime;


namespace ws4
{
    WS4::WS4()
    {
        // Setup vars
        char TITLE[] = "WS4 Build " __DATE__;
        SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER || SDL_INIT_AUDIO);
        window = SDL_CreateWindow
                (
                        TITLE,
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        WIN_WIDTH,
                        WIN_HEIGHT,
                        SDL_WINDOW_SHOWN
                );
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        scr = {
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
//        sceneTimer = SDL_AddTimer(sceneTime, nextScreen, const_cast<char*>("scene"));
//        LDLTimer = SDL_AddTimer(LDLTime, nextLDL, const_cast<char*>("LDL"));
    }


    int WS4::nextScreen()
    {
        scrIdx = (scrIdx + 1) % scr.size();
        return 1;
    }

    int WS4::prevScreen()
    {
        scrIdx = (scrIdx - 1 + scr.size()) % scr.size();
        return 1;
    }

    int WS4::nextLDL()
    {
        return 1;
    }

    void WS4::loadGraphics()
    {
        // Load mappings for all graphics
//        fontMap = loadFontMap();
//        colorMap = loadColorMap();
//        textureMap = loadTextureMap();
//        iconPosMap = loadIconPositionsMap();
    }

    void WS4::getNewData()
    {
        ws4p::fetchNewData();
        int valid = ws4p::runValidator();
        if (valid != 0)
        {
            std::cout << "NB! Validator value: " << valid << '\n';
            // Run corrector / handle somehow
        }

        ws4p::createMapRegion(1780, 430);
        data = ws4p::readyFormatLatestData();
        cityROXValues = {"160", "530", "350", "490", "340", "90", "320"};
        cityROYValues = {"140", "120", "170", "220", "270", "300", "340"};
        cityRFXValues = {"160", "530", "350", "490", "340", "90", "320"};
        cityRFYValues = {"140", "120", "170", "220", "270", "300", "340"};
    }

    void WS4::loadData()
    {

    }

    void WS4::loadMusic()
    {
        if (!musicEnabled)
            return;

        // Open folder and load all songs
        for (const auto& entry : fs::directory_iterator("../music"))
        {
            if (entry.path().extension() == ".mp3")
                songsPaths.push_back(entry.path());
        }

        if (songsPaths.empty())
            return;

        songIdx = songsPaths.size();
//        musicPlayer.setVolume(volume);
        changeSong();
//        musicStarted = true;
    }

    void WS4::changeSong()
    {
        songIdx++;
        if (songIdx >= songsPaths.size())
        {
            // Shuffle
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(songsPaths.begin(), songsPaths.end(),std::mt19937(seed));
            songIdx = 0;
        }

//        if (!musicPlayer.openFromFile(songsPaths[songIdx]))
//            return;
//
//        musicPlayer.play();
    }


    int WS4::runLoop()
    {
        SDL_Event e;
        bool running = true;
        while (running) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.scancode)
                {
                    case SDL_SCANCODE_Q:
                    case SDL_SCANCODE_ESCAPE:
                    case SDL_SCANCODE_SPACE:
                        running = false;
                        break;
                    case SDL_SCANCODE_P:
                        nextScreen();
                        break;
                    case SDL_SCANCODE_O:
                        prevScreen();
                        break;
                    case SDL_SCANCODE_S:
                        changeSong();
                        break;
                    default:
                        break;
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_Rect r;
            r.x = 50;
            r.y = 50;
            r.w = 50;
            r.h = 50;

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &r);
            SDL_RenderPresent(renderer);
        }

        SDL_DestroyWindow(window);
//        SDL_RemoveTimer(sceneTimer);
//        SDL_RemoveTimer(LDLTimer);
        SDL_Quit();

        return EXIT_SUCCESS;
    }
}
