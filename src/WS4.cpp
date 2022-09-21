#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <array>
#include <map>
#include <time.h>
#include <iostream>

#include "WS4.h"
#include "gfx_init.h"
#include "data_proc.h"

using namespace ws4;
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
        for (short i = 0; i < scr.size(); i++)
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


    void WS4::loadGraphics()
    {
        cM = parseColorData();
        tM = parseTextData(cM, fM, dM);
        vM = parseVertexData(cM);

        if (!moonPhasesTexture.loadFromFile("../icons/Moon-Phases.png"))
            return;
        if (!curCondTexture.loadFromFile("../icons/Current-Conditions.png"))
            return;
        if (!extForcTexture.loadFromFile("../icons/Extended-Forecast.png"))
            return;
        if (!regMapsTexture.loadFromFile("../icons/Regional-Maps.png"))
            return;

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
        dM["Current-Conditions"]["wind"] = "Wind:  WNW  38";
        dM["Current-Conditions"]["gusts"] = "Gusts to  77"; 
        dM["Current-Conditions"]["scroller"] = "Conditions at Moline";

        dM["Forecast-For"]["forecast-day"] = "Saturday";
        dM["Air-Quality"]["airq-day"] = "Friday";
        dM["Almanac"]["icon-0"] = "Full";
        dM["Almanac"]["icon-1"] = "Last";
        dM["Almanac"]["icon-2"] = "New";
        dM["Almanac"]["icon-3"] = "First";

        dM["Extended-Forecast"]["icon-0"] = "Fog";
        dM["Extended-Forecast"]["icon-1"] = "Mostly-Cloudy";
        dM["Extended-Forecast"]["icon-2"] = "Snow-to-Rain";
        dM["Extended-Forecast"]["city"] = "Moline";
    }


    void WS4::loadIcons()
    {
        iconPos["Current-Conditions"] = 
        {
            {"Blowing-Snow", {138, 0, 99}},
            {"Clear", {100, 99, 65}},
            {"Cloudy", {118, 164, 83}},
            {"Freezing-Rain-Sleet", {126, 247, 113}},
            {"Freezing-Rain", {124, 360, 113}},
            {"Heavy-Snow", {136, 473, 103}},
            {"Ice-Snow", {146, 577, 117}},
            {"Light-Snow", {108, 695, 91}},
            {"Mostly-Clear", {94, 787, 69}},
            {"Mostly-Cloudy", {142, 856, 85}},
            {"Partly-Clear", {138, 940, 69}},
            {"Partly-Cloudy", {130, 1010, 85}},
            {"Rain-Snow", {138, 1094, 117}},
            {"Rain", {124, 1212, 113}},
            {"Shower", {124, 1326, 101}},
            {"Sleet", {70, 1427, 91}},
            {"Snow-Sleet", {108, 1519, 91}},
            {"Sunny", {112, 1611, 107}},
            {"Thunder", {148, 1718, 123}},
            {"ThunderSnow", {142, 1841, 93}},
            {"Thunderstorm", {142, 1935, 117}},
            {"Wintry-Mix", {134, 2053, 105}},
        };

        iconPos["Extended-Forecast"] = 
        {
            {"Cloudy", {96, 0, 69}},
            {"Fog", {112, 70, 91}},
            {"Freezing-Rain", {100, 161, 91}},
            {"Heavy-Snow", {114, 253, 85}},
            {"Isolated-Tstorms", {116, 339, 103}},
            {"Light-Snow", {86, 443, 75}},
            {"Mostly-Cloudy", {122, 518, 69}},
            {"Partly-Cloudy", {106, 588, 69}},
            {"Rain-Snow", {116, 657, 97}},
            {"Rain", {100, 755, 89}},
            {"Scattered-Showers", {132, 845, 97}},
            {"Scattered-Snow-Showers", {112, 943, 71}},
            {"Scattered-Tstorms", {130, 1015, 101}},
            {"Showers", {100, 1117, 81}},
            {"Snow-to-Rain", {116, 1199, 91}},
            {"Sunny", {90, 1290, 87}},
            {"Thunderstorms", {118, 1378, 97}},
            {"Windy", {88, 1475, 63}},
            {"Wintry-Mix", {106, 1538, 83}},
        };

        iconPos["Forecast-For"] = 
        {
            {"AM-Snow", {52, 0, 39}},
            {"Blowing-Snow", {56, 40, 49}},
            {"Clear", {36, 89, 37}},
            {"Cloudy-Wind", {66, 126, 57}},
            {"Cloudy", {52, 184, 35}},
            {"Fog", {48, 220, 45}},
            {"Freezing-Rain-Sleet", {60, 266, 61}},
            {"Freezing-Rain-Snow", {50, 328, 45}},
            {"Freezing-Rain", {50, 374, 35}},
            {"Heavy-Snow", {48, 409, 47}},
            {"Light-Snow", {44, 457, 45}},
            {"Mostly-Clear", {46, 502, 37}},
            {"Mostly-Cloudy", {60, 540, 55}},
            {"Partly-Clear", {66, 596, 37}},
            {"Partly-Cloudy", {60, 633, 55}},
            {"Rain-Sleet", {62, 689, 63}},
            {"Rain-Snow", {46, 753, 53}},
            {"Rain-Wind", {64, 807, 55}},
            {"Rain", {44, 863, 39}},
            {"Scattered-Showers", {60, 902, 55}},
            {"Scattered-Snow-Showers", {60, 958, 71}},
            {"Scattered-Tstorms", {64, 1030, 57}},
            {"Shower", {42, 1088, 30}},
            {"Sleet", {46, 1118, 43}},
            {"Snow-Sleet", {48, 1161, 47}},
            {"Sunny-Wind", {66, 1209, 55}},
            {"Sunny", {60, 1265, 55}},
            {"Thunder", {62, 1321, 63}},
            {"ThunderSnow", {62, 1385, 59}},
            {"Thunderstorm", {58, 1445, 59}},
            {"Wind", {56, 1504, 45}},
            {"Wintry-Mix", {56, 1544, 51}},
        };

        iconPos["Almanac"] = 
        {
            {"New", {100, 0, 93}},
            {"First", {100, 94, 93}},
            {"Full", {100, 188, 93}},
            {"Last", {100, 282, 93}},
        };

        // TODO automate all of this

        // Current Conditions Icon
        iM["Current-Conditions"].push_back(sf::Sprite(curCondTexture));
        iM["Current-Conditions"][0].setPosition(sf::Vector2f(178, 174));
        iM["Current-Conditions"][0].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][0], 
                        iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][1]), 
            sf::Vector2i(iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][0], 
                        iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][2])
        ));
        iM["Current-Conditions"][0].setOrigin(sf::Vector2f(
            iM["Current-Conditions"][0].getGlobalBounds().width/2, 0
        ));

        // Moon Icons
        iM["Almanac"].push_back(sf::Sprite(moonPhasesTexture));
        iM["Almanac"][0].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Almanac"][dM["Almanac"]["icon-0"]][0], iconPos["Almanac"][dM["Almanac"]["icon-0"]][1]), 
            sf::Vector2i(iconPos["Almanac"][dM["Almanac"]["icon-0"]][0], iconPos["Almanac"][dM["Almanac"]["icon-0"]][2])
        ));
        iM["Almanac"][0].setOrigin(sf::Vector2f(iM["Almanac"][0].getGlobalBounds().width/2, 0));
        iM["Almanac"][0].setPosition(sf::Vector2f(135, 270));
        iM["Almanac"].push_back(sf::Sprite(moonPhasesTexture));
        iM["Almanac"][1].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Almanac"][dM["Almanac"]["icon-1"]][0], iconPos["Almanac"][dM["Almanac"]["icon-1"]][1]), 
            sf::Vector2i(iconPos["Almanac"][dM["Almanac"]["icon-1"]][0], iconPos["Almanac"][dM["Almanac"]["icon-1"]][2])
        ));
        iM["Almanac"][1].setOrigin(sf::Vector2f(iM["Almanac"][1].getGlobalBounds().width/2, 0));
        iM["Almanac"][1].setPosition(sf::Vector2f(255, 270));
        iM["Almanac"].push_back(sf::Sprite(moonPhasesTexture));
        iM["Almanac"][2].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Almanac"][dM["Almanac"]["icon-2"]][0], iconPos["Almanac"][dM["Almanac"]["icon-2"]][1]), 
            sf::Vector2i(iconPos["Almanac"][dM["Almanac"]["icon-2"]][0], iconPos["Almanac"][dM["Almanac"]["icon-2"]][2])
        ));
        iM["Almanac"][2].setOrigin(sf::Vector2f(iM["Almanac"][2].getGlobalBounds().width/2, 0));
        iM["Almanac"][2].setPosition(sf::Vector2f(375, 270));
        iM["Almanac"].push_back(sf::Sprite(moonPhasesTexture));
        iM["Almanac"][3].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Almanac"][dM["Almanac"]["icon-3"]][0], iconPos["Almanac"][dM["Almanac"]["icon-3"]][1]), 
            sf::Vector2i(iconPos["Almanac"][dM["Almanac"]["icon-3"]][0], iconPos["Almanac"][dM["Almanac"]["icon-3"]][2])
        ));
        iM["Almanac"][3].setOrigin(sf::Vector2f(iM["Almanac"][3].getGlobalBounds().width/2, 0));
        iM["Almanac"][3].setPosition(sf::Vector2f(495, 270));


        // Extended Forecast Icons
        iM["Extended-Forecast"].push_back(sf::Sprite(extForcTexture));
        iM["Extended-Forecast"][0].setPosition(sf::Vector2f(120, 150));
        iM["Extended-Forecast"][0].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-0"]][0], 
                        iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-0"]][1]), 
            sf::Vector2i(iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-0"]][0], 
                        iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-0"]][2])
        ));
        iM["Extended-Forecast"][0].setOrigin(sf::Vector2f(
            iM["Extended-Forecast"][0].getGlobalBounds().width/2, 0
        ));
        iM["Extended-Forecast"].push_back(sf::Sprite(extForcTexture));
        iM["Extended-Forecast"][1].setPosition(sf::Vector2f(320, 150));
        iM["Extended-Forecast"][1].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-1"]][0], 
                        iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-1"]][1]), 
            sf::Vector2i(iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-1"]][0], 
                        iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-1"]][2])
        ));
        iM["Extended-Forecast"][1].setOrigin(sf::Vector2f(
            iM["Extended-Forecast"][1].getGlobalBounds().width/2, 0
        ));
        iM["Extended-Forecast"].push_back(sf::Sprite(extForcTexture));
        iM["Extended-Forecast"][2].setPosition(sf::Vector2f(510, 150));
        iM["Extended-Forecast"][2].setTextureRect(sf::IntRect(
            sf::Vector2i(animFrame*iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-2"]][0], 
                        iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-2"]][1]), 
            sf::Vector2i(iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-2"]][0], 
                        iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-2"]][2])
        ));
        iM["Extended-Forecast"][2].setOrigin(sf::Vector2f(
            iM["Extended-Forecast"][2].getGlobalBounds().width/2, 0
        ));
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
        {
            "../audio/001.mp3",
            "../audio/002.mp3",
            "../audio/003.mp3",
            "../audio/004.mp3",
            "../audio/005.mp3"
        };
        
        if (!musicPlayer.openFromFile(songsPaths[0]))
            return;

        musicPlayer.setVolume(20);
    }


    void WS4::changeSong()
    {

    }
}



int main()
{
    // Print version info
    #ifdef __clang__
    std::cout << "Clang Version: ";
    std::cout << __clang__ << std::endl;
    std::cout << "LLVM Version: ";
    std::cout << __llvm__ << std::endl;
    #else
    std::cout << "GCC Version: ";
    std::cout << __VERSION__ << std::endl;
    #endif


    WS4 ws4Engine;
    ws4Engine.loadData();
    ws4Engine.loadFonts();
    ws4Engine.loadGraphics();
    ws4Engine.loadIcons();
    
    // ws4Engine.musicPlayer.play();

    // sf::Clock sceneTimer;
    // sf::Time elapsedScene;
    float sceneTime = 10.f;




    /*
     * MAIN LOOP
     */
    while (ws4Engine.window.isOpen())
    {
        // EVENTS
        sf::Event event;
        while (ws4Engine.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                ws4Engine.window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                    case sf::Keyboard::Q:
                    case sf::Keyboard::Space:
                        ws4Engine.window.close(); 
                        break;
                    case sf::Keyboard::P:
                        ws4Engine.nextScreen();
                        break;
                    case sf::Keyboard::O:
                        ws4Engine.prevScreen();
                        break;
                    case sf::Keyboard::R:
                        ws4Engine.loadGraphics();
                        break;
                    default:
                        break;
                }
            }
        }
 
        // Check if time for scene change
        // if (sceneTimer.getElapsedTime().asSeconds() >= sceneTime)
        // {
        //     ws4Engine.nextScreen();
        //     elapsedScene = sceneTimer.restart();
        // }


        // DRAWING GRAPHICS
        ws4Engine.drawGraphics();
        ws4Engine.drawText();
        ws4Engine.window.display();


        // Check if time to change song
        // if (ws4Engine.musicPlayer.getStatus() == sf::Music::Status::Stopped)
        //     ws4Engine.changeSong();

    }

    return EXIT_SUCCESS;
};
