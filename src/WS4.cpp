#include <SFML/Graphics.hpp>
#include "WS4.h"
#include "gfx_init.h"
#include <vector>
#include <array>

namespace ws4 
{
    std::array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col1, sf::Color col2)
    {
        std::array<sf::Vertex, 4> quad = 
        {
            sf::Vertex(sf::Vector2f(x+w, y), col1),
            sf::Vertex(sf::Vector2f(x, y), col1),
            sf::Vertex(sf::Vector2f(x+w, y+h), col2),
            sf::Vertex(sf::Vector2f(x, y+h), col2)
        };
        return quad;
    }

    std::array<sf::Vertex, 4> buildQuad(int x1, int y1, int x2, int y2, 
                                            int x3, int y3, int x4, int y4, sf::Color col)
    {
        std::array<sf::Vertex, 4> quad = 
        {
            sf::Vertex(sf::Vector2f(x4, y4), col),
            sf::Vertex(sf::Vector2f(x1, y1), col),
            sf::Vertex(sf::Vector2f(x3, y3), col),
            sf::Vertex(sf::Vector2f(x2, y2), col)
        };
        return quad;
    }
}

#include <iostream>


using namespace ws4;

int main()
{

    #ifdef __clang__
    std::cout << "Clang Version: ";
    std::cout << __clang__ << std::end;
    std::cout << "LLVM Version: ";
    std::cout << __llvm__ << std::endl;
    #else
    std::cout << "GCC Version: ";
    std::cout << __VERSION__ << std::endl;
    #endif

    initColors();
    initVertices();
    initText();

    /*
     * VARIABLES & CONSTS
     */
    const char  TITLE[] = "WS4 Build " __DATE__;
    const short FPS = 30;

    const float SCALE = 1.0f;
    const short WIN_WIDTH = 640;
    const short WIN_HEIGHT = 480;

    const sf::Color cBlack1(14, 14, 14);
    const sf::Color cBlack2(20, 20, 20);
    const sf::Color cWhite(215, 215, 215);
    const sf::Color cGray1(175, 175, 175);
    const sf::Color cGray2(61, 61, 61);
    const sf::Color cViolet1(130, 138, 245);
    const sf::Color cViolet2(153, 153, 153);

    const sf::Color cDkBlue1(28, 10, 87);
    const sf::Color cDkBlue2(35, 50, 112);

    const sf::Color cGPurple(46, 18, 81);
    const sf::Color cGOrange(192, 93, 2);

    const sf::Color cLtBlue1(86, 91, 202);
    const sf::Color cLtBlue2(66, 78, 202);
    const sf::Color cLtBlue3(44, 66, 202);
    const sf::Color cLtBlue4(37, 57, 202);
    const sf::Color cLtBlue5(9, 49, 202);
    const sf::Color cLtBlue6(0, 40, 203);
    const sf::Color cLtBlue7(0, 36, 203);
    const sf::Color cLtBlue8(0, 34, 203);

    const sf::Color cFgBlue1(38, 82, 178);
    const sf::Color cFgBlue2(37, 75, 163);
    const sf::Color cFgBlue3(37, 70, 152);
    const sf::Color cFgBlue4(36, 64, 140);
    const sf::Color cFgBlue5(35, 58, 128);
    const sf::Color cFgBlue6(34, 52, 116);
    const sf::Color cFgBlue7(34, 47, 105);
    const sf::Color cFgBlue8(33, 43, 96);
    const sf::Color cFgBlue9(33, 40, 90);

    const sf::Color cYellow(205, 185, 0);
    const sf::Color cOrange1(195, 91, 0);
    const sf::Color cOrange2(178, 82, 0);
    const sf::Color cOrange3(157, 75, 19);
    const sf::Color cOrange4(142, 66, 26);
    const sf::Color cOrange5(123, 56, 36);
    const sf::Color cOrange6(105, 46, 46);
    const sf::Color cOrange7(89, 42, 62);
    const sf::Color cOrange8(71, 34, 64);
    const sf::Color cRed(135, 35, 15);

    // air quality thingies
    // local radar bg and colors


    /*
     * WINDOW & VIDEOMODE
     */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0.0;
    settings.depthBits = 8;
    settings.sRgbCapable = false;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WIN_WIDTH*SCALE, WIN_HEIGHT*SCALE)), TITLE, 
                                                sf::Style::Titlebar | sf::Style::Close, settings);

    window.setFramerateLimit(FPS);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.size.x/4 - WIN_WIDTH*SCALE/2, 
                                    desktop.size.y/4 - WIN_HEIGHT*SCALE/2));

    sf::View view;
    view.setSize(sf::Vector2f(window.getSize().x/SCALE, window.getSize().y/SCALE));
    view.setCenter(sf::Vector2f(view.getSize().x/2, view.getSize().y/2));
    window.setView(view);


    
    // https://www.sfml-dev.org/tutorials/2.5/system-time.php



    /*
     * VERTEX ARRAYS & SHAPES
     */
    // TODO load these from somewhere or place into other files
    // TODO method to generate these automatically
    // Create Class that inits all shapes and icons,
    // extend for every scene
    
    std::vector< std::array<sf::Vertex, 4> > quadObjects = {
        // Current Conditions
        buildQuad(0, 90, WIN_WIDTH, 308, cGPurple, cGOrange),
        
        // Center window layers
        buildQuad(52, 90, 531, 308, cFgBlue1, cFgBlue1),
        buildQuad(55, 94, 527, 302, cFgBlue2, cFgBlue2),
        buildQuad(57, 96, 523, 298, cFgBlue3, cFgBlue3),
        buildQuad(59, 98, 519, 294, cFgBlue4, cFgBlue4),
        buildQuad(61, 100, 515, 290, cFgBlue5, cFgBlue5),
        buildQuad(63, 102, 511, 286, cFgBlue6, cFgBlue6),
        buildQuad(65, 104, 507, 282, cFgBlue7, cFgBlue7),
        buildQuad(66, 105, 506, 281, cFgBlue8, cFgBlue8),
        buildQuad(67, 106, 505, 280, cFgBlue9, cFgBlue9),
        
        // Almanac
        // buildQuad(0, 90, WIN_WIDTH, 191, cGPurple, cGOrange), // TODO colors and make gradient uneven
        // buildQuad(0, 192, WIN_WIDTH, 206, cGray2, cGray2),

        // Extended Forecast
        // Block 1
        // buildQuad(0, 90, WIN_WIDTH, 308, cGPurple, cGOrange),
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


        // Top orange bar
        buildQuad(0, 29, 499, 29, 494, 37, 0, 37, cOrange1),
        buildQuad(0, 37, 494, 37, 489, 45, 0, 45, cOrange2),
        buildQuad(0, 45, 489, 45, 483, 54, 0, 54, cOrange3),
        buildQuad(0, 54, 483, 54, 478, 61, 0, 61, cOrange4),
        buildQuad(0, 61, 478, 61, 471, 71, 0, 71, cOrange5),
        buildQuad(0, 71, 471, 71, 467, 77, 0, 77, cOrange6),
        buildQuad(0, 77, 467, 77, 461, 85, 0, 85, cOrange7),
        buildQuad(0, 85, 461, 85, 457, 90, 0, 90, cOrange8),

        // Bottom bar
        buildQuad(0, 399, WIN_WIDTH, 81, cBlack1, cBlack1), 
        buildQuad(0, 400, WIN_WIDTH, 80, cGray1, cGray1),
        buildQuad(0, 402, WIN_WIDTH, 78, cDkBlue2, cDkBlue2) 
    };



    // FONTS
    sf::Font fStar4000;
    if (!fStar4000.loadFromFile("../fonts/Star4000.ttf"))
        return 2;
    fStar4000.setSmooth(false);

    sf::Font fStar4000Ext;
    if (!fStar4000Ext.loadFromFile("../fonts/Star4000-Extended.ttf"))
        return 2;
    fStar4000Ext.setSmooth(false);

    sf::Font fStar4000Lg;
    if (!fStar4000Lg.loadFromFile("../fonts/Star4000-Large.ttf"))
        return 2;
    fStar4000Lg.setSmooth(false);

    sf::Font fStar4000LgC;
    if (!fStar4000LgC.loadFromFile("../fonts/Star4000-Large-Compressed.ttf"))
        return 2;
    fStar4000LgC.setSmooth(false);

    sf::Font fStar4000Sm;
    if (!fStar4000Sm.loadFromFile("../fonts/Star4000-Small.ttf"))
        return 2;
    fStar4000Sm.setSmooth(false);




    // TEXT
    std::vector< sf::Text > textShadows;
    std::vector< sf::Text > textObjects;

    sf::String textValues[] = { "Current", "Conditions", "Moline", "Humidity:", "Dewpoint:", "Ceiling:", 
                                "Visibility:", "Pressure:", "Wind:  WNW  38", "Gusts to  77",
                                "Conditions at Moline", "1:57:14 PM", "MON AUG 10", "68°", "T'Storm" };
    
    short textOrigins[] = {  };
    short textSizes[] = { 34, 34, 34, 33, 33, 33, 33, 33, 30, 30, 30, 31, 31, 39, 37 }; // size in px
    sf::Color textColors[] = { cYellow, cYellow, cYellow, cWhite, cWhite, cWhite, cWhite, cWhite, 
                                cWhite, cWhite, cWhite, cWhite, cWhite, cWhite, cWhite };
    sf::Font textFonts[] = { fStar4000, fStar4000, fStar4000, fStar4000, fStar4000, 
                                fStar4000, fStar4000, fStar4000, fStar4000Ext, fStar4000Ext, 
                                fStar4000, fStar4000Sm, fStar4000Sm, fStar4000Lg, fStar4000Ext };
    short textPosX[] = { 167, 167, 320, 348, 348, 348, 348, 348, 83, 83, 62, 428, 428, 167, 124 };
    short textPosY[] = { 21, 50, 92, 141, 181, 225, 267, 308, 308, 346, 398, 33, 53, 104, 148 };
    float textLS[] = { 1, 1, 0.55, 0.55, 0.55, 0.55, 0.55, 0.55, 1, 1, 1, 1, 1, 1, 1 };
 
    for (u_long i = 0; i < std::size(textValues); i++) {
        textShadows.push_back(sf::Text(textValues[i], textFonts[i], textSizes[i]*0.67));
        textShadows[i].setFillColor(cBlack2);
        textShadows[i].setPosition(sf::Vector2f(textPosX[i]+3, textPosY[i]+3));
        textShadows[i].setOutlineColor(cBlack2);
        textShadows[i].setOutlineThickness(0); // in px
        textShadows[i].setLetterSpacing(textLS[i]);
        textShadows[i].setScale(sf::Vector2f(1.5f,1.5f));

        textObjects.push_back(sf::Text(textValues[i], textFonts[i], textSizes[i]*0.67));
        textObjects[i].setFillColor(textColors[i]);
        textObjects[i].setPosition(sf::Vector2f(textPosX[i], textPosY[i]));
        textObjects[i].setOutlineColor(cBlack1);
        textObjects[i].setOutlineThickness(1); // in px
        textObjects[i].setLetterSpacing(textLS[i]);
        textObjects[i].setScale(sf::Vector2f(1.5f,1.5f));
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
        }


        // DRAWING GRAPHICS
        window.clear(cDkBlue1);

        for (u_long i = 0; i < std::size(quadObjects); i++){
            window.draw(quadObjects[i].data(), 4, sf::TriangleStrip);
        }

        for (u_long i = 0; i < std::size(textObjects); i++){
            window.draw(textShadows[i]);
            window.draw(textObjects[i]);
        }

        window.display();
    }

    return EXIT_SUCCESS;
};
