#include "GfxLoader.h"
#include "DataProc.h"
#include <filesystem>
#include <algorithm>
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
    }


    void WS4::loadData()
    {
        // NB! Graphics *MUST* be loaded before calling this method

        // Connection point with DataProc here
        // TODO possibly place all into a dict or one vector
        vector<string> ccText = {"Moline", "56°", "Ice Snow", "66%", "53°", "0.8 mi.",
                                 "3300 ft.", "29.93", "Wind:  WNW  38", "Gusts to  77", "Wind Chill:", "52°"};
        bool ccPressureArrowUp = true;
        string ccIcon = "CC_Ice-Snow";
        vector<string> loText = {};
        vector<string> roCities = {"Oklahoma", "Ponca City", "Tulsa", "Altus", "Gage", "Tinker AFB"};
        vector<string> roTemps = {"62", "61", "65", "71", "59", "62"};
        vector<string> roIcons = {"RF_Rain", "RF_Sunny", "RF_Cloudy", "RF_Mostly-Cloudy", "RF_Thunderstorm", "RF_Thunderstorm"};
        vector<string> lf1Text = {};
        vector<string> lf2Text = {};
        vector<string> lf3Text = {};
        vector<string> efText = {};
        vector<string> efIcons = {"EF_Thunderstorms", "EF_Mostly-Cloudy", "EF_Snow-to-Rain"};
        vector<string> aText = {};
        vector<string> aMoons = {"M_New", "M_First", "M_Full", "M_Last"};
        LDLStrings = {"Conditions at Moline", "Ice Snow",
                      "Temp: 56°F",
                      "Humidity:  66%   Dewpoint: 53°",
                      "Barometric Pressure: 29.93 F",
                      "Wind: WNW  38 MPH",
                      "Visib:   0.8 mi.  Ceiling:3300 ft.",
                      "October Precipitation: 0.09 in"};
        LDLScrollStr = "Ministry: Rail Baltica progress slowed by poor design work, bad management.";



        // [0] Current Conditions
        screens.at(0).updateText(ccText);
        screens.at(0).setPressureArrow(buildPressureArrow(ccPressureArrowUp,
                                                          colorMap["#cdb900"], colorMap["#0e0e0e"]));
        screens.at(0).loadIcons({
            AnimIcon(textureMap["CC"], iconPosMap[ccIcon], 178, 230)
        });

        // [2] Regional Observations
        screens.at(2).loadMap(textureMap["Map"], 150, 200);
        screens.at(2).loadCities({
             MapCity(roCities[0], roTemps[0], 100, 100, fontMap, colorMap, textureMap["RF"], iconPosMap[roIcons[0]]),
             MapCity(roCities[1], roTemps[1], 140, 250, fontMap, colorMap, textureMap["RF"], iconPosMap[roIcons[1]]),
             MapCity(roCities[2], roTemps[2], 290, 110, fontMap, colorMap, textureMap["RF"], iconPosMap[roIcons[2]]),
             MapCity(roCities[3], roTemps[3], 230, 180, fontMap, colorMap, textureMap["RF"], iconPosMap[roIcons[3]]),
             MapCity(roCities[4], roTemps[4], 410, 130, fontMap, colorMap, textureMap["RF"], iconPosMap[roIcons[4]]),
             MapCity(roCities[5], roTemps[5], 400, 310, fontMap, colorMap, textureMap["RF"], iconPosMap[roIcons[5]])
         });

        // [6] Regional Forecast
        screens.at(6).loadMap(textureMap["Map"], 150, 200);
        // screens.at(6).loadCities({});

        // [7] Extended Forecast
        screens.at(7).loadIcons({
            AnimIcon(textureMap["EF"], iconPosMap[efIcons[0]], 122, 200),
            AnimIcon(textureMap["EF"], iconPosMap[efIcons[1]], 320, 200),
            AnimIcon(textureMap["EF"], iconPosMap[efIcons[2]], 514, 200),
        });

        // [8] Almanac
        screens.at(8).loadIcons({
            AnimIcon(textureMap["Moon"], iconPosMap[aMoons[0]], 134, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[aMoons[1]], 256, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[aMoons[2]], 378, 318),
            AnimIcon(textureMap["Moon"], iconPosMap[aMoons[3]], 504, 318)
        });

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
                LDL.setText(LDLScrollStr);
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

            // Display window
            window.display();


            // Check if time to change song
             if (musicStarted && musicPlayer.getStatus() == sf::Music::Status::Stopped)
                 changeSong();

        }

        return EXIT_SUCCESS;
    }
}
