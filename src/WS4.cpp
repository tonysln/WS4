#include <SFML/Graphics.hpp>
#include "WS4.h"
#include "gfx_init.h"
#include <vector>
#include <array>
#include <map>
#include <iostream>


using namespace ws4;
using std::cout;
using std::endl;


int main()
{
    // Print version info
    #ifdef __clang__
    cout << "Clang Version: ";
    cout << __clang__ << endl;
    cout << "LLVM Version: ";
    cout << __llvm__ << endl;
    #else
    cout << "GCC Version: ";
    cout << __VERSION__ << endl;
    #endif



    /*
     * SETUP VARIABLES
     */
    const char  TITLE[] = "WS4 Build " __DATE__;
    const short FPS = 30;
    const float SCALE = 1.0f;
    const short WIN_WIDTH = 640;
    const short WIN_HEIGHT = 480;




    /*
     * WINDOW & VIDEOMODE
     */
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
    // TODO
    sf::Clock clock;
    sf::Time currentTime;





    // Extended Forecast TEMP TODO
    // buildQuad(56, 110, 180, 280, cBlack1, cBlack1),
    // buildQuad(58, 112, 176, 276, cViolet1, cViolet1),
    // buildQuad(63, 117, 166, 266, cBlack1, cBlack1),
    // buildQuad(65, 119, 162, 46, cLtBlue1, cLtBlue1),
    // buildQuad(65, 165, 162, 54, cLtBlue2, cLtBlue2),
    // buildQuad(65, 219, 162, 54, cLtBlue3, cLtBlue3),
    // buildQuad(65, 271, 162, 52, cLtBlue4, cLtBlue4),
    // buildQuad(65, 165, 162, 54, cLtBlue5, cLtBlue5),
    // buildQuad(65, 165, 162, 54, cLtBlue6, cLtBlue6),
    // buildQuad(65, 165, 162, 54, cLtBlue7, cLtBlue7),
    // buildQuad(65, 165, 162, 54, cLtBlue8, cLtBlue8),




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
    // auto dM = collectLatestData();
    auto cM = parseColorData();
    auto tM = parseTextData(cM, fM);
    auto vM = parseVertexData(cM);
   
    short curScreen = 0;
    vector<string> screens = {
        "Current-Conditions",
        "Latest-Observations",
        "Extended-Forecast",
        "Almanac"
    };
    





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
                        tM = parseTextData(cM, fM);
                        break;
                }
            }
        }



        // DRAWING GRAPHICS
        // Purple BG
        window.clear(cM["cDkBlue1"]);

        // Vertices
        for (auto &vObj : vM[screens[curScreen]])
        {
            // TODO handle other renderstates later
            window.draw(vObj.data(), vObj.size(), sf::TriangleStrip);
        }

        // Text
        for (auto &tObj : tM[screens[curScreen]])
        {
            window.draw(tObj);
        }

        // TODO draw CLOCK



        window.display();

        // Update clock and timers
    }

    return EXIT_SUCCESS;
};
