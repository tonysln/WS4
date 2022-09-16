#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "WS4.h"
#include "gfx_init.h"
#include "data_proc.h"
#include <vector>
#include <array>
#include <map>
#include <time.h>
#include <iostream>


using namespace ws4;
using std::to_string;
using std::localtime;
using std::strftime;


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



    /*
     * WINDOW & VIDEOMODE
     */
    const char  TITLE[] = "WS4 Build " __DATE__;
    const short FPS = 23;
    const float SCALE = 1.0f;
    const short WIN_WIDTH = 640;
    const short WIN_HEIGHT = 480;

    
    sf::ContextSettings sts;
    sts.antialiasingLevel = 0.0;
    sts.depthBits = 8;
    sts.sRgbCapable = false;

    // Renderer window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WIN_WIDTH*SCALE, WIN_HEIGHT*SCALE)), TITLE, 
                                                sf::Style::Titlebar | sf::Style::Close, sts);

    window.setFramerateLimit(FPS);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.size.x/4 - WIN_WIDTH*SCALE/2, 
                                    desktop.size.y/4 - WIN_HEIGHT*SCALE/2));

    // View settings for scaling 
    sf::View view;
    view.setSize(sf::Vector2f(window.getSize().x/SCALE, window.getSize().y/SCALE));
    view.setCenter(sf::Vector2f(view.getSize().x/2, view.getSize().y/2));
    window.setView(view);


    


    /*
     * CLOCK & TIMERS
     */
    sf::Clock clock;
    sf::Time currentTime;
    std::time_t epoch;
    char timeStr[12];
    char timeAPStr[6];
    char dateStr[12];



    /*
     * MUSIC
     */
    // sf::Music music;
    // if (!music.openFromFile("../audio/001.mp3"))
    //     return EXIT_FAILURE;

    // music.setVolume(30);
    // music.play();




    /*
     * FONTS
     */
    map<string, sf::Font> fM;

    if (!fM["fStar4000"].loadFromFile("../fonts/Star4000.ttf"))
        return 2;
    if (!fM["fStar4000Ext"].loadFromFile("../fonts/Star4000-Extended.ttf"))
        return 2;
    if (!fM["fStar4000Lg"].loadFromFile("../fonts/Star4000-Large.ttf"))
        return 2;
    if (!fM["fStar4000LgC"].loadFromFile("../fonts/Star4000-Large-Compressed.ttf"))
        return 2;
    if (!fM["fStar4000Sm"].loadFromFile("../fonts/Star4000-Small.ttf"))
        return 2;

    for (auto fontEl : fM)
    {
        // Disable smoothing for all fonts - TODO re-check this and scaling
        fontEl.second.setSmooth(false);
    }



    /*
     * READING DATA AND GRAPHICS FILES
     */
    map<string, string> dM;
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


    auto cM = parseColorData();
    auto tM = parseTextData(cM, fM, dM);
    auto vM = parseVertexData(cM);


    /*
     * ICONS
     */
    map<string, sf::Sprite> icons;

    // TODO load all textures and icons
    sf::Texture storm;
    if (!storm.loadFromFile("../icons/Current-Conditions/Thunder.gif"))
        return 3;
    
    icons["TStorm"].setTexture(storm);
    icons["TStorm"].setPosition(sf::Vector2f(176, 170));
    icons["TStorm"].setOrigin(sf::Vector2f(icons["TStorm"].getLocalBounds().width/2, 0));
    icons["TStorm"].setScale(sf::Vector2f(1.0, 1.0));

    map<string, vector<sf::Sprite>> iM;
    iM["Current-Conditions"] = { icons["TStorm"] };



    // List of screens
    short curScreen = 0;
    vector<string> screens = {
        "Current-Conditions",
        "Latest-Observations",
        "Local-Forecast",
        "Extended-Forecast",
        "Almanac",
        "Forecast-For",
        "Air-Quality"
    };


    // Time clock Text alignment fix - do not let it jump around due to 
    // different widths of symbols
    for (short i = 0; i < screens.size(); i++)
    {
        tM[screens[i]][1].setOrigin(sf::Vector2f(99.333, 0));
    }
    




    /*
     * MAIN LOOP
     */
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
                        curScreen = (curScreen + 1) % screens.size();
                        break;
                    case sf::Keyboard::O:
                        curScreen = (curScreen - 1 + screens.size()) % screens.size();
                        break;
                    case sf::Keyboard::R:
                        tM = parseTextData(cM, fM, dM);
                        break;
                    default:
                        break;
                }
            }
        }



        // DRAWING GRAPHICS
        // Purple BG
        window.clear(cM["cDkBlue1"]);

        // Vertices
        for (const auto& vObj : vM[screens[curScreen]])
        {
            // TODO handle other renderstates later
            window.draw(vObj.data(), vObj.size(), sf::TriangleStrip);
        }


        //Icons
        //TODO get from dM
        for (const auto& iObj : iM[screens[curScreen]])
        {
            window.draw(iObj);
        }


        // Text
        // Update time/date strings
        epoch = std::time(nullptr);
        strftime(timeStr, sizeof(timeStr), "%-I:%M:%S", localtime(&epoch));
        strftime(timeAPStr, sizeof(timeAPStr), "%p", localtime(&epoch));
        strftime(dateStr, sizeof(dateStr), "%a %b %e", localtime(&epoch)); // %e is space-padded
        
        // TODO clean up by specifying shadow ON or OFF in dat file
        // tM[screens[curScreen]][0].setString(timeStr);
        tM[screens[curScreen]][1].setString(timeStr);
        
        // tM[screens[curScreen]][2].setString(dateStr);
        tM[screens[curScreen]][3].setString(dateStr);
        tM[screens[curScreen]][3].setOrigin(sf::Vector2f(tM[screens[curScreen]][3].getLocalBounds().width, 0));
        
        // tM[screens[curScreen]][4].setString(timeStr);
        tM[screens[curScreen]][5].setString(timeAPStr);
        tM[screens[curScreen]][5].setOrigin(sf::Vector2f(tM[screens[curScreen]][5].getLocalBounds().width, 0));


        // Draw text
        for (const auto& tObj : tM[screens[curScreen]])
        {
            window.draw(tObj);
        }

        window.display();
    }

    return EXIT_SUCCESS;
};
