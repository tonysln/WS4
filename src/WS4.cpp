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
    }


    void WS4::nextScreen()
    {
        curScreen = (curScreen + 1) % screens.size();
        nextScreenUpdate();
    }

    void WS4::prevScreen()
    {
        curScreen = (curScreen - 1 + screens.size()) % screens.size();
        nextScreenUpdate();
    }


    void WS4::nextScreenUpdate()
    {
        // Time clock Text alignment fix - do not let it jump around due to 
        // different widths of symbols
        // NB! TODO! call this at 10:00:00 and 12:00:00 !!
        for (short i = 0; i < screens.size(); i++)
        {
            double xCoordFix = 99.333;
            if (localtime(&epoch)->tm_hour % 12 < 10)
                xCoordFix = 94;

            tM[screens[i]][1].setOrigin(sf::Vector2f(xCoordFix, 0));
        }
    }


    void WS4::loadFonts()
    {
        int f1 = fM["fStar4000"].loadFromFile("../fonts/Star4000.ttf");
        int f2 = fM["fStar4000Ext"].loadFromFile("../fonts/Star4000-Extended.ttf");
        int f3 = fM["fStar4000Lg"].loadFromFile("../fonts/Star4000-Large.ttf");
        int f4 = fM["fStar4000LgC"].loadFromFile("../fonts/Star4000-Large-Compressed.ttf");
        int f5 = fM["fStar4000Sm"].loadFromFile("../fonts/Star4000-Small.ttf");

        if (!f1||!f2||!f3||!f4||!f4||!f5) return;

        // for (auto &fontEl : fM)
            // fontEl.second.setSmooth(false);
    }


    void WS4::loadGraphics()
    {
        cM = parseColorData();
        tM = parseTextData(cM, fM, dM);
        vM = parseVertexData(cM);
        nextScreenUpdate();
    }


    void WS4::loadData()
    {
        dM["city"] = "Moline";
        dM["temp"] = "68°";
        dM["cond"] = "T'Storm";
        dM["humidity"] = "87%";
        dM["dewpoint"] = "64°";
        dM["ceiling"] = "0.8 mi.";
        dM["visib"] = "3300 ft.";
        dM["pressure"] = "29.93";
        dM["wind"] = "Wind:  WNW  38"; // TODO split?
        dM["gusts"] = "Gusts to  77";  // TODO split?
        dM["scroller"] = "Conditions at Moline";

        dM["forecast-day"] = "Saturday";
        dM["airq-day"] = "Friday";
    }


    void WS4::drawGraphics()
    {
        window.clear(cM["cDkBlue1"]);

        // Vertices
        for (const auto& vObj : vM[screens[curScreen]])
        {
            window.draw(vObj.data(), vObj.size(), sf::TriangleStrip);
        }

        //Icons
        // for (const auto& iObj : iM[screens[curScreen]])
        // {
            // window.draw(iObj);
        // }
    }


    void WS4::drawText()
    {
        // Update time/date strings
        epoch = std::time(nullptr);
        strftime(timeStr, sizeof(timeStr), "%-I:%M:%S", localtime(&epoch));
        strftime(timeAPStr, sizeof(timeAPStr), "%p", localtime(&epoch));
        strftime(dateStr, sizeof(dateStr), "%a %b %e", localtime(&epoch)); // %e is space-padded
        
        // TODO clean up by specifying shadow ON or OFF in dat file
        // tM[screens[curScreen]][0].setString(timeStr);
        // tM[screens[curScreen]][2].setString(dateStr);
        // tM[screens[curScreen]][4].setString(timeStr);

        tM[screens[curScreen]][1].setString(timeStr);
        tM[screens[curScreen]][3].setString(dateStr);
        tM[screens[curScreen]][3].setOrigin(
            sf::Vector2f(tM[screens[curScreen]][3].getLocalBounds().width, 0)
        );
        tM[screens[curScreen]][5].setString(timeAPStr);
        tM[screens[curScreen]][5].setOrigin(
            sf::Vector2f(tM[screens[curScreen]][5].getLocalBounds().width, 0)
        );

        // Draw text
        for (const auto& tObj : tM[screens[curScreen]])
        {
            window.draw(tObj);
        }
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
    

    /*
     * MUSIC
     */
    sf::Music music;
    if (!music.openFromFile("../audio/001.mp3"))
        return EXIT_FAILURE;
    music.setVolume(20);
    music.play();


    /*
     * ICONS
     */
    map<string, sf::Sprite> icons;
    sf::Texture storm;
    if (!storm.loadFromFile("../icons/Current-Conditions/Thunder.gif"))
        return 3;
    
    icons["TStorm"].setTexture(storm);
    icons["TStorm"].setPosition(sf::Vector2f(176, 170));
    icons["TStorm"].setOrigin(sf::Vector2f(icons["TStorm"].getLocalBounds().width/2, 0));
    icons["TStorm"].setScale(sf::Vector2f(1.0, 1.0));

    map<string, sf::Sprite> iM;
    iM["Current-Conditions"] = icons["TStorm"];



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

        // DRAWING GRAPHICS
        ws4Engine.drawGraphics();

        // Icons
        ws4Engine.window.draw(iM[ws4Engine.screens[ws4Engine.curScreen]]);
        
        ws4Engine.drawText();

        ws4Engine.window.display();
    }

    return EXIT_SUCCESS;
};
