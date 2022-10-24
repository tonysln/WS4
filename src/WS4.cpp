#include "GfxLoader.h"
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

        // RenderWindow
        window.create(sf::VideoMode(sf::Vector2u(WIN_WIDTH*SCALE, WIN_HEIGHT*SCALE)),
                            TITLE, winBorders ? sf::Style::Titlebar | sf::Style::Close : sf::Style::None);

        window.setFramerateLimit(FPS);
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.setPosition(sf::Vector2i(desktop.size.x/4 - WIN_WIDTH*SCALE/2, 
                                        desktop.size.y/4 - WIN_HEIGHT*SCALE/2));

        // View settings for scaling 
        view.setSize(sf::Vector2f(window.getSize().x/SCALE, window.getSize().y/SCALE));
        view.setCenter(sf::Vector2f(view.getSize().x/2, view.getSize().y/2));
        window.setView(view);
    }


    void WS4::nextScreen()
    {
        scrIdx = (scrIdx + 1) % scr.size();
    }

    void WS4::prevScreen()
    {
        scrIdx = (scrIdx - 1 + scr.size()) % scr.size();
    }


    void WS4::loadGraphics()
    {
        // Load mappings for all graphics
        fontMap = loadFontMap();
        colorMap = loadColorMap();
        textureMap = loadTextureMap();
        iconPosMap = loadIconPositionsMap();

        // [0] Current Conditions
        loadCurrentConditions(screens, fontMap, colorMap);
        // [1] Latest Observations
        loadLatestObservations(screens, fontMap, colorMap);
        // [2] Regional Observations
        loadRegionalObservations(screens, fontMap, colorMap);
        // [3,4,5] Local (36-Hour) Forecast
        loadLocalForecast(screens, fontMap, colorMap);
        // [6] Regional Forecast
        loadRegionalForecast(screens, fontMap, colorMap);
        // [7] Extended Forecast
        loadExtendedForecast(screens, fontMap, colorMap);
        // [8] Almanac
        loadAlmanac(screens, fontMap, colorMap);

        LDL = GfxLDL(" ", colorMap, fontMap);
        clock = GfxClock(colorMap, fontMap);

        if (showLogo)
        {
            logo = sf::Sprite(textureMap["Logo"]);
            logo.setPosition(sf::Vector2f(45.f, 24.f));
        }
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

        ws4p::createMapRegion(420, 660);
        data = ws4p::readyFormatLatestData();
    }


    void WS4::loadData()
    {
        // Create MapCity icon vectors
        vector<MapCity> roMapCities = {};
        for (int i = 0; i < data[4].size(); i++)
            roMapCities.emplace_back(data[4][i], data[5][i], data[7][i], data[8][i],
                                     fontMap, colorMap, textureMap["RF"], iconPosMap[data[6][i]]);

        vector<MapCity> rfMapCities = {};
        for (int i = 0; i < data[13].size(); i++)
            rfMapCities.emplace_back(data[13][i], data[14][i], data[16][i], data[17][i],
                                     fontMap, colorMap, textureMap["RF"], iconPosMap[data[15][i]]);


        // [0] Current Conditions
        screens.at(0).updateText(data[0]);
        screens.at(0).setPressureArrow(buildPressureArrow(data[1][0],
                                                          colorMap["#cdb900"], colorMap["#0e0e0e"]));
        screens.at(0).loadIcons({
            AnimIcon(textureMap["CC"], iconPosMap[data[2][0]], 178, 230)
        });

        screens.at(1).updateText(data[3]);

        // [2] Regional Observations
        screens.at(2).loadMap(textureMap["Map"], 0, 0);
        screens.at(2).loadCities(roMapCities);

        screens.at(3).updateText(data[9]);
        screens.at(4).updateText(data[10]);
        screens.at(5).updateText(data[11]);

        // [6] Regional Forecast
        screens.at(6).loadMap(textureMap["Map"], 0, 0);
        screens.at(6).loadCities(rfMapCities);
        screens.at(6).updateText(data[12]);

        // [7] Extended Forecast
        screens.at(7).updateText(data[18]);
        screens.at(7).loadIcons({
            AnimIcon(textureMap["EF"], iconPosMap[data[19][0]], 122, 200),
            AnimIcon(textureMap["EF"], iconPosMap[data[19][1]], 320, 200),
            AnimIcon(textureMap["EF"], iconPosMap[data[19][2]], 514, 200),
        });

        // [8] Almanac
        screens.at(8).updateText(data[20]);
        screens.at(8).loadIcons({
            AnimIcon(textureMap["Moon"], iconPosMap[data[21][0]], 134, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[data[21][1]], 256, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[data[21][2]], 378, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[data[21][3]], 504, 318)
        });

        LDLStrings = data[22];
        LDLScrollStr = data[23];
        LDL.setText(LDLStrings.at(LDLStrIdx));
    }


    void WS4::loadMusic()
    {
        // Open folder and load all songs
        for (const auto& entry : fs::directory_iterator("../music"))
        {
            if (entry.path().extension() == ".mp3")
                songsPaths.push_back(entry.path());
        }

        if (songsPaths.empty())
            return;

        songIdx = songsPaths.size();
        musicPlayer.setVolume(volume);
        changeSong();
        musicStarted = true;
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

        if (!musicPlayer.openFromFile(songsPaths[songIdx]))
            return;

        musicPlayer.play();
    }


    int WS4::runLoop()
    {
        while (window.isOpen())
        {
            // EVENTS
            sf::Event event{};
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed)
                {
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Escape:
                        case sf::Keyboard::Q:
                        case sf::Keyboard::Space:
                            window.close(); 
                            break;
                        case sf::Keyboard::P:
                            nextScreen();
                            break;
                        case sf::Keyboard::O:
                            prevScreen();
                            break;
                        case sf::Keyboard::S:
                            changeSong();
                            break;
                        default:
                            break;
                    }
                }
            }


            // Scene change timer
            if (sceneTimer.getElapsedTime().asSeconds() >= sceneTime)
            {
                nextScreen();
                sceneTimer.restart();
            }

            // Update LDL text string-by-string in display mode
            if (!LDL.isUsingScroll() && LDLTimer.getElapsedTime().asSeconds() >= LDLTime)
            {
                LDLStrIdx++;
                if (LDLStrIdx >= LDLStrings.size())
                {
                    LDL.displays++;
                    LDLStrIdx = 0;
                }
                LDL.setText(LDLStrings.at(LDLStrIdx));
                LDLTimer.restart();
            }

            // Switch between displaying and scrolling LDL text
            if (!LDL.isUsingScroll() && LDL.displays >= dispLDLTimes)
            {
                LDL.useScroll(true);
                LDL.setText(LDLScrollStr[0]);
            }
            if (LDL.isUsingScroll() && LDL.scrolls >= scrLDLTimes)
            {
                LDL.useScroll(false);
                LDLStrIdx = 0;
                LDL.setText(LDLStrings.at(LDLStrIdx));
                LDLTimer.restart();
            }



            // Clear window
            window.clear(colorMap["#1c0a57"]);

            // Advance through icon animation
            iconFrameCounter++;
            if (iconFrameCounter >= FPS / ANIM_FRAMES)
            {
                iconFrame = (iconFrame + 1) % ANIM_FRAMES;
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

            // Render the logo (if enabled)
            if (showLogo)
                window.draw(logo);

            // Display window
            window.display();


            // Check if time to change song
             if (musicStarted && musicPlayer.getStatus() == sf::Music::Status::Stopped)
                 changeSong();

        }

        return EXIT_SUCCESS;
    }
}
