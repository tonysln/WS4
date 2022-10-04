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
        sts.antialiasingLevel = 0.0;
        sts.depthBits = 8;
        sts.sRgbCapable = false;

        // RenderWindow
        window.create(sf::VideoMode(sf::Vector2u(WIN_WIDTH*SCALE, WIN_HEIGHT*SCALE)),
                                        TITLE, sf::Style::Titlebar | sf::Style::Close, sts);

        window.setFramerateLimit(FPS);
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.setPosition(sf::Vector2i(desktop.size.x/4 - WIN_WIDTH*SCALE/2, 
                                        desktop.size.y/4 - WIN_HEIGHT*SCALE/2));

        // View settings for scaling 
        view.setSize(sf::Vector2f(window.getSize().x/SCALE, window.getSize().y/SCALE));
        view.setCenter(sf::Vector2f(view.getSize().x/2, view.getSize().y/2));
        window.setView(view);

        animFrame = 0;

        gfxManager = GfxManager();
    }

    void WS4::nextScreen()
    {
        cur = (cur + 1) % scr.size();
        nextScreenUpdate();
    }

    void WS4::prevScreen()
    {
        cur = (cur - 1 + scr.size()) % scr.size();
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

            tM[scr[i]][1].setOrigin(sf::Vector2f(xCoordFix, 0));
        }
    }


    void WS4::loadFonts()
    {
        if(!fM["fStar4000"].loadFromFile("../fonts/Star4000.ttf"))
            return;
        if(!fM["fStar4000Ext"].loadFromFile("../fonts/Star4000-Extended.ttf"))
            return;
        if(!fM["fStar4000Lg"].loadFromFile("../fonts/Star4000-Large.ttf"))
            return;
        if(!fM["fStar4000LgC"].loadFromFile("../fonts/Star4000-Large-Compressed.ttf"))
            return;
        if(!fM["fStar4000Sm"].loadFromFile("../fonts/Star4000-Small.ttf"))
            return;

        // for (auto &fontEl : fM)
            // fontEl.second.setSmooth(false);
    }

    void WS4::loadTextures()
    {
        if (!moonPhasesTexture.loadFromFile("../graphics/icons/Moon-Phases.png"))
            return;
        if (!curCondTexture.loadFromFile("../graphics/icons/Current-Conditions.png"))
            return;
        if (!extForcTexture.loadFromFile("../graphics/icons/Extended-Forecast.png"))
            return;
        if (!regMapsTexture.loadFromFile("../graphics/icons/Regional-Maps.png"))
            return;
        // if (!regBaseMapTexture.loadFromFile("../graphics/maps/basemap-2.png"))
        //     return;
    }


    void WS4::loadGraphics()
    {
        cM = parseColorData();
        tM = parseTextData(cM, fM, dM);
        vM = parseVertexData(cM);
        iconPos = loadIconPos();
        iM = loadIcons(iconPos, dM, moonPhasesTexture, curCondTexture, extForcTexture, regMapsTexture);
        nextScreenUpdate();
    }


    void WS4::loadData()
    {
        dM["Current-Conditions"]["city"] = "Moline";
        dM["Current-Conditions"]["temp"] = "56";
        dM["Current-Conditions"]["cond"] = "Ice Snow";
        dM["Current-Conditions"]["icon-0"] = "Ice-Snow";
        dM["Current-Conditions"]["humidity"] = "66%";
        dM["Current-Conditions"]["dewpoint"] = "53";
        dM["Current-Conditions"]["ceiling"] = "0.8 mi.";
        dM["Current-Conditions"]["visib"] = "3300 ft.";
        dM["Current-Conditions"]["pressure"] = "29.93";
        dM["Current-Conditions"]["pressure-arrow"] = "up";
        dM["Current-Conditions"]["wind"] = "Wind:  WNW  38";
        dM["Current-Conditions"]["gusts"] = "Gusts to  77"; 
        dM["Current-Conditions"]["scroller"] = "Conditions at Moline";

        // TODO Text positions
        dM["Forecast-For"]["forecast-day"] = "Saturday";
        dM["Forecast-For"]["num-cities"] = "5";
        dM["Forecast-For"]["map-x"] = "400";
        dM["Forecast-For"]["map-y"] = "1900";
        dM["Forecast-For"]["icon-0"] = "Mostly-Clear";
        dM["Forecast-For"]["icon-0-x"] = "100";
        dM["Forecast-For"]["icon-0-y"] = "120";
        dM["Forecast-For"]["icon-1"] = "Mostly-Cloudy";
        dM["Forecast-For"]["icon-1-x"] = "220";
        dM["Forecast-For"]["icon-1-y"] = "240";
        dM["Forecast-For"]["icon-2"] = "Rain";
        dM["Forecast-For"]["icon-2-x"] = "290";
        dM["Forecast-For"]["icon-2-y"] = "270";
        dM["Forecast-For"]["icon-3"] = "Rain-Wind";
        dM["Forecast-For"]["icon-3-x"] = "350";
        dM["Forecast-For"]["icon-3-y"] = "300";
        dM["Forecast-For"]["icon-4"] = "Partly-Clear";
        dM["Forecast-For"]["icon-4-x"] = "460";
        dM["Forecast-For"]["icon-4-y"] = "130";
        dM["Forecast-For"]["city-0"] = "Tulsa";
        dM["Forecast-For"]["city-1"] = "Fort Smith";
        dM["Forecast-For"]["city-2"] = "OK City";
        dM["Forecast-For"]["city-3"] = "Amarillo";
        dM["Forecast-For"]["city-4"] = "Dallas";
        dM["Forecast-For"]["city-0-temp"] = "67";
        dM["Forecast-For"]["city-1-temp"] = "54";
        dM["Forecast-For"]["city-2-temp"] = "58";
        dM["Forecast-For"]["city-3-temp"] = "66";
        dM["Forecast-For"]["city-4-temp"] = "70";
        
        dM["Travel-Forecast"]["forecast-day"] = "For Saturday";
        dM["Air-Quality"]["airq-day"] = "Friday";
        dM["Almanac"]["icon-0"] = "Full";
        dM["Almanac"]["icon-1"] = "Last";
        dM["Almanac"]["icon-2"] = "New";
        dM["Almanac"]["icon-3"] = "First";

        dM["Extended-Forecast"]["icon-0"] = "Thunderstorms";
        dM["Extended-Forecast"]["icon-1"] = "Mostly-Cloudy";
        dM["Extended-Forecast"]["icon-2"] = "Snow-to-Rain";
        dM["Extended-Forecast"]["city"] = "Moline";
    }

    void WS4::drawGraphics()
    {
        window.clear(cM["cDkBlue1"]);

        // Vertices and Shapes
        for (const auto& vObj : vM[scr[cur]])
            window.draw(vObj.data(), vObj.size(), sf::TriangleStrip);

        // Icons & Animation
        animFrame = (animFrame + 1) % ANIM_FRAMES;
        icoCt = 0;
        for (auto& iObj : iM[scr[cur]])
        {
            window.draw(iObj);
            iObj.setTextureRect(sf::IntRect(
                sf::Vector2i(animFrame * iconPos[scr[cur]][dM[scr[cur]]["icon-" + to_string(icoCt)]][0], 
                                         iconPos[scr[cur]][dM[scr[cur]]["icon-" + to_string(icoCt)]][1]), 
                sf::Vector2i(iconPos[scr[cur]][dM[scr[cur]]["icon-" + to_string(icoCt)]][0], 
                             iconPos[scr[cur]][dM[scr[cur]]["icon-" + to_string(icoCt)]][2])
            ));
            icoCt++;
        }
    }


    void WS4::drawText()
    {
        // Update time/date strings
        epoch = std::time(nullptr);
        strftime(timeStr, sizeof(timeStr), "%-I:%M:%S", localtime(&epoch));
        strftime(timeAPStr, sizeof(timeAPStr), "%p", localtime(&epoch));
        strftime(dateStr, sizeof(dateStr), "%a %b %e", localtime(&epoch)); // %e is space-padded

        // Check if clock positioning needs to be fixed (at 10 and 1)
        if ((localtime(&epoch)->tm_min == 0) && (localtime(&epoch)->tm_sec <= 3))
            nextScreenUpdate();

        tM[scr[cur]][1].setString(timeStr);
        tM[scr[cur]][3].setString(dateStr);
        tM[scr[cur]][3].setOrigin(sf::Vector2f(tM[scr[cur]][3].getLocalBounds().width, 0));
        tM[scr[cur]][5].setString(timeAPStr);
        tM[scr[cur]][5].setOrigin(sf::Vector2f(tM[scr[cur]][5].getLocalBounds().width, 0));

        // Draw text
        for (const auto& tObj : tM[scr[cur]])
            window.draw(tObj);
    }


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
    { }


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
                        case sf::Keyboard::R:
                            loadData();
                            loadGraphics();
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

            drawGraphics();
            drawText();

            // Render everything to window
            gfxManager.renderAllTo(window, cur);

            // Display window
            window.display();


            // Check if time to change song
            // if (musicPlayer.getStatus() == sf::Music::Status::Stopped)
            //     changeSong();

        }

        return EXIT_SUCCESS;
    }
}
