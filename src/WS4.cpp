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

    WS4::WS4():
        logo(textureMap["Logo"]),
        LDL(" ")
    {
        // Setup vars
        char TITLE[] = "WS4 Build " __DATE__;

        // RenderWindow
        window.create(sf::VideoMode(sf::Vector2u(WIN_WIDTH * SCALE, WIN_HEIGHT * SCALE)),
                      TITLE, sf::Style::None, sf::State::Windowed);

        window.setFramerateLimit(FPS);
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.setPosition(sf::Vector2i(desktop.size.x / 4 - WIN_WIDTH * SCALE / 2,
                                        desktop.size.y / 4 - WIN_HEIGHT * SCALE / 2));

        // View settings for scaling 
        view.setSize(sf::Vector2f(window.getSize().x / SCALE, window.getSize().y / SCALE));
        view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
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
        textureMap = loadTextureMap();
        iconPosMap = loadIconPositionsMap();

        // [0] Current Conditions
        loadCurrentConditions(screens);
        // [1] Latest Observations
        loadLatestObservations(screens);
        // [2] Regional Observations
        loadRegionalObservations(screens);
        // [3,4,5] Local (36-Hour) Forecast
        loadLocalForecast(screens);
        // [6] Regional Forecast
        loadRegionalForecast(screens);
        // [7] Extended Forecast
        loadExtendedForecast(screens);
        // [8] Almanac
        loadAlmanac(screens);

        LDL = GfxLDL(" ");
        clock = GfxClock();

        if (showLogo)
        {
            logo = sf::Sprite(textureMap["Logo"]); // re-load
            logo.setPosition(sf::Vector2f(44.f, 23.f));
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

        ws4p::createMapRegion(1780, 430);
        data = ws4p::readyFormatLatestData();
        cityROXValues = {"160", "530", "350", "490", "340", "90", "320"};
        cityROYValues = {"140", "120", "170", "220", "270", "300", "340"};
        cityRFXValues = {"160", "530", "350", "490", "340", "90", "320"};
        cityRFYValues = {"140", "120", "170", "220", "270", "300", "340"};
    }


    void WS4::loadData()
    {
        // Create MapCity icon vectors
        vector<MapCity> roMapCities = {};
        for (int i = 0; i < cityROXValues.size(); i++)
            roMapCities.emplace_back(data[4][i], data[5][i], cityROXValues[i], cityROYValues[i],
                                     textureMap["RF"], iconPosMap[data[6][i]]);

        vector<MapCity> rfMapCities = {};
        for (int i = 0; i < cityRFXValues.size(); i++)
            rfMapCities.emplace_back(data[11][i], data[12][i], cityRFXValues[i], cityRFYValues[i],
                                     textureMap["RF"], iconPosMap[data[13][i]]);


        // [0] Current Conditions
        screens.at(0).updateText(data[0]);
        screens.at(0).setPressureArrow(buildPressureArrow(data[1][0], "#cdb900", "#0e0e0e"));
        screens.at(0).loadIcons({
            AnimIcon(textureMap["CC"], iconPosMap[data[2][0]], 184, 218)
        });

        screens.at(1).updateText(data[3]);

        // [2] Regional Observations
        screens.at(2).loadMap(textureMap["Map"], 0, 0);
        screens.at(2).loadCities(roMapCities);

        screens.at(3).updateText(data[7]);
        screens.at(4).updateText(data[8]);
        screens.at(5).updateText(data[9]);

        // [6] Regional Forecast
        screens.at(6).loadMap(textureMap["Map"], 0, 0);
        screens.at(6).loadCities(rfMapCities);
        screens.at(6).updateText(data[10]);

        // [7] Extended Forecast
        screens.at(7).updateText(data[14]);
        screens.at(7).loadIcons({
            AnimIcon(textureMap["EF"], iconPosMap[data[15][0]], 122, 200),
            AnimIcon(textureMap["EF"], iconPosMap[data[15][1]], 320, 200),
            AnimIcon(textureMap["EF"], iconPosMap[data[15][2]], 514, 200),
        });

        // [8] Almanac
        screens.at(8).updateText(data[16]);
        screens.at(8).loadIcons({
            AnimIcon(textureMap["Moon"], iconPosMap[data[17][0]], 134, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[data[17][1]], 256, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[data[17][2]], 378, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[data[17][3]], 504, 318)
        });

        LDLStrings = data[18];
        LDLScrollStr = data[19];
        LDL.setText(LDLStrings.at(LDLStrIdx));
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
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    switch(keyPressed->scancode)
                    {
                        case sf::Keyboard::Scancode::Escape:
                        case sf::Keyboard::Scancode::Q:
                        case sf::Keyboard::Scancode::Space:
                            window.close(); 
                            break;
                        case sf::Keyboard::Scancode::P:
                            nextScreen();
                            break;
                        case sf::Keyboard::Scancode::O:
                            prevScreen();
                            break;
                        case sf::Keyboard::Scancode::S:
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
            window.clear(sf::Color(28,10,87));

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
             if (musicEnabled && musicStarted && musicPlayer.getStatus() == sf::Music::Status::Stopped)
                 changeSong();

        }

        return EXIT_SUCCESS;
    }
}
