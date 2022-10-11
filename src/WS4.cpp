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

        LDL = GfxLDL("Currently at Moline", colorMap, fontMap);
        clock = GfxClock(colorMap, fontMap);

        LDL.useScroll(true);
        LDL.setText("Ministry: Rail Baltica progress slowed by poor design work, bad management.");

        // Dynamic data
        loadData();
    }

    void WS4::nextScreen()
    {
        scrIdx = (scrIdx + 1) % scr.size();
        nextScreenUpdate();
    }

    void WS4::prevScreen()
    {
        scrIdx = (scrIdx - 1 + scr.size()) % scr.size();
        nextScreenUpdate();
    }


    void WS4::nextScreenUpdate()
    {
        // Time clock Text alignment fix - do not let it jump around due to 
        // different widths of symbols
        for (u_long i = 0; i < scr.size(); i++)
        {
            double xCoordFix = 101.333;
            if (localtime(&epoch)->tm_hour % 12 < 10 && 
                localtime(&epoch)->tm_hour % 12 > 0)
                xCoordFix = 92.333;
        }
    }


    void WS4::loadData()
    {
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
    }


//    void WS4::loadData()
//    {
//        dM["Current-Conditions"]["city"] = "Moline";
//        dM["Current-Conditions"]["temp"] = "56";
//        dM["Current-Conditions"]["cond"] = "Ice Snow";
//        dM["Current-Conditions"]["icon-0"] = "Ice-Snow";
//        dM["Current-Conditions"]["humidity"] = "66%";
//        dM["Current-Conditions"]["dewpoint"] = "53";
//        dM["Current-Conditions"]["ceiling"] = "0.8 mi.";
//        dM["Current-Conditions"]["visib"] = "3300 ft.";
//        dM["Current-Conditions"]["pressure"] = "29.93";
//        dM["Current-Conditions"]["pressure-arrow"] = "up";
//        dM["Current-Conditions"]["wind"] = "Wind:  WNW  38";
//        dM["Current-Conditions"]["gusts"] = "Gusts to  77";
//        dM["Current-Conditions"]["scroller"] = "Conditions at Moline";
//
//        dM["Forecast-For"]["forecast-day"] = "Saturday";
//        dM["Forecast-For"]["num-cities"] = "5";
//        dM["Forecast-For"]["map-x"] = "400";
//        dM["Forecast-For"]["map-y"] = "1900";
//        dM["Forecast-For"]["icon-0"] = "Mostly-Clear";
//        dM["Forecast-For"]["icon-0-x"] = "100";
//        dM["Forecast-For"]["icon-0-y"] = "120";
//        dM["Forecast-For"]["icon-1"] = "Mostly-Cloudy";
//        dM["Forecast-For"]["icon-1-x"] = "220";
//        dM["Forecast-For"]["icon-1-y"] = "240";
//        dM["Forecast-For"]["icon-2"] = "Rain";
//        dM["Forecast-For"]["icon-2-x"] = "290";
//        dM["Forecast-For"]["icon-2-y"] = "270";
//        dM["Forecast-For"]["icon-3"] = "Rain-Wind";
//        dM["Forecast-For"]["icon-3-x"] = "350";
//        dM["Forecast-For"]["icon-3-y"] = "300";
//        dM["Forecast-For"]["icon-4"] = "Partly-Clear";
//        dM["Forecast-For"]["icon-4-x"] = "460";
//        dM["Forecast-For"]["icon-4-y"] = "130";
//        dM["Forecast-For"]["city-0"] = "Tulsa";
//        dM["Forecast-For"]["city-1"] = "Fort Smith";
//        dM["Forecast-For"]["city-2"] = "OK City";
//        dM["Forecast-For"]["city-3"] = "Amarillo";
//        dM["Forecast-For"]["city-4"] = "Dallas";
//        dM["Forecast-For"]["city-0-temp"] = "67";
//        dM["Forecast-For"]["city-1-temp"] = "54";
//        dM["Forecast-For"]["city-2-temp"] = "58";
//        dM["Forecast-For"]["city-3-temp"] = "66";
//        dM["Forecast-For"]["city-4-temp"] = "70";
//
//        dM["Travel-Forecast"]["forecast-day"] = "For Saturday";
//        dM["Air-Quality"]["airq-day"] = "Friday";
//        dM["Almanac"]["icon-0"] = "Full";
//        dM["Almanac"]["icon-1"] = "Last";
//        dM["Almanac"]["icon-2"] = "New";
//        dM["Almanac"]["icon-3"] = "First";
//
//        dM["Extended-Forecast"]["icon-0"] = "Thunderstorms";
//        dM["Extended-Forecast"]["icon-1"] = "Mostly-Cloudy";
//        dM["Extended-Forecast"]["icon-2"] = "Snow-to-Rain";
//        dM["Extended-Forecast"]["city"] = "Moline";
//    }

//    void WS4::drawText()
//    {
//        // Update time/date strings
//        epoch = std::time(nullptr);
//        strftime(timeStr, sizeof(timeStr), "%-I:%M:%S", localtime(&epoch));
//        strftime(timeAPStr, sizeof(timeAPStr), "%p", localtime(&epoch));
//        strftime(dateStr, sizeof(dateStr), "%a %b %e", localtime(&epoch)); // %e is space-padded
//
//        // Check if clock positioning needs to be fixed (at 10 and 1)
//        if ((localtime(&epoch)->tm_min == 0) && (localtime(&epoch)->tm_sec <= 3))
//            nextScreenUpdate();
//    }


    void WS4::loadMusic()
    {
        // TODO define list of songs, select random?
        vector<string> songsPaths = 
        { };
        
        if (!musicPlayer.openFromFile(songsPaths[0]))
            return;

        musicPlayer.setVolume(20);
    }


    void WS4::changeSong()
    {

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
    
            // Check if time for scene change
            // if (sceneTimer.getElapsedTime().asSeconds() >= sceneTime)
            // {
            //     nextScreen();
            //     elapsedScene = sceneTimer.restart();
            // }


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
