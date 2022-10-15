#include "GfxLoader.h"
#include "DataProc.h"
#include "WS4.h"

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
                                                    TITLE, sf::Style::Titlebar | sf::Style::Close);

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
        // TODO use script to cut out and zoom correct map part, save it as img and load here

        // [0] Current Conditions
        screens.at(0).loadIcons({
            AnimIcon(textureMap["CC"], iconPosMap["CC_Ice-Snow"], 178, 230)
        });

        // [2] Regional Observations
        screens.at(2).loadMap(textureMap["Map"], 150, 200);
        screens.at(2).loadCities({
             MapCity("Oklahoma", "62", 100, 100, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Rain"]),
             MapCity("Ponca City", "61", 140, 250, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Sunny"]),
             MapCity("Tulsa", "65", 290, 110, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Cloudy"]),
             MapCity("Altus", "71", 230, 180, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Mostly-Cloudy"]),
             MapCity("Gage", "59", 410, 130, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Thunderstorm"]),
             MapCity("Tinker AFB", "62", 400, 310, fontMap, colorMap, textureMap["RF"], iconPosMap["RF_Thunderstorm"])
         });

        // [6] Regional Forecast
        screens.at(6).loadMap(textureMap["Map"], 150, 200);
        // screens.at(6).loadCities({});

        // [7] Extended Forecast
        screens.at(7).loadIcons({
            AnimIcon(textureMap["EF"], iconPosMap["EF_Thunderstorms"], 120, 200),
            AnimIcon(textureMap["EF"], iconPosMap["EF_Mostly-Cloudy"], 320, 200),
            AnimIcon(textureMap["EF"], iconPosMap["EF_Snow-to-Rain"], 510, 200),
        });

        // [8] Almanac
        screens.at(8).loadIcons({
            AnimIcon(textureMap["Moon"], iconPosMap["M_New"], 135, 320),
            AnimIcon(textureMap["Moon"], iconPosMap["M_First"], 255, 320),
            AnimIcon(textureMap["Moon"], iconPosMap["M_Full"], 375, 320),
            AnimIcon(textureMap["Moon"], iconPosMap["M_Last"], 495, 320)
        });

        LDLStrings = {"Conditions at Moline", "Ice Snow",
                      "Temp: 56°F",
                      "Humidity:  66%   Dewpoint: 53°",
                      "Barometric Pressure: 29.93 F",
                      "Wind: WNW  38 MPH",
                      "Visib:   0.8 mi.  Ceiling:3300 ft.",
                      "October Precipitation: 0.09 in"};
        LDLScrollStr = "Ministry: Rail Baltica progress slowed by poor design work, bad management.";

        LDL.setText(LDLStrings.at(LDLStrIdx));
    }


    void WS4::loadMusic()
    {
        // Open folder and load all songs
        // Shuffle
        // Play through
        // Shuffle, repeat ...
        songsPaths =
        { };
        
//        if (!musicPlayer.openFromFile(songsPaths[songIdx]))
//            return;

//        musicPlayer.setVolume(volume);
    }


    void WS4::changeSong()
    {
        songIdx++;
        if (songIdx > songsPaths.size())
        {
            // shuffle, start over...
        }
    }


    int WS4::runLoop()
    {
        while (window.isOpen())
        {
            // EVENTS
            sf::Event event;
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
            // if (musicStarted && musicPlayer.getStatus() == sf::Music::Status::Stopped)
            //     changeSong();

        }

        return EXIT_SUCCESS;
    }
}
