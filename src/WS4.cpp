#include <SFML/Graphics.hpp>
#include <vector>
#include <array>



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



int main()
{
    /*
     * VARIABLES & CONSTS
     */
    const char  TITLE[] = "WS4 v22.9.14";
    const short FPS = 30;

    const float SCALE = 1.5f;
    const short WIN_WIDTH = 640;
    const short WIN_HEIGHT = 480;

    const sf::Color cBlack1(14, 14, 14);
    const sf::Color cBlack2(20, 20, 20);
    const sf::Color cWhite(215, 215, 215);
    const sf::Color cGray(175, 175, 175);
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
    const sf::Color cRed(112, 35, 35);


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
    window.setPosition(sf::Vector2i(desktop.size.x/2 - WIN_WIDTH/2, 
                                    desktop.size.y/2 - WIN_HEIGHT/2));

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
        buildQuad(0, 90, WIN_WIDTH, 308, cGPurple, cGOrange),                  // Main Gradient
        buildQuad(0, 399, WIN_WIDTH, 81, cBlack1, cBlack1),                    // Bottom bar Black BG
        buildQuad(0, 401, WIN_WIDTH, 79, cGray, cGray),                        // Bottom bar Silver BG
        buildQuad(0, 403, WIN_WIDTH, 77, cDkBlue2, cDkBlue2),                  // Bottom bar Blue BG
        // Center window layers
        buildQuad(52, 90, 531, 308, cFgBlue1, cFgBlue1),
        buildQuad(55, 94, 527, 302, cFgBlue2, cFgBlue2),
        buildQuad(57, 96, 523, 298, cFgBlue3, cFgBlue3),
        buildQuad(59, 98, 519, 294, cFgBlue4, cFgBlue4),
        buildQuad(61, 100, 515, 290, cFgBlue5, cFgBlue5),
        buildQuad(63, 102, 511, 286, cFgBlue6, cFgBlue6),
        buildQuad(65, 104, 507, 282, cFgBlue7, cFgBlue7),
        buildQuad(66, 105, 506, 281, cFgBlue8, cFgBlue8),
        buildQuad(67, 106, 505, 280, cFgBlue9, cFgBlue9),                   // TODO possibly double-check
        // Top bar orange -- TODO fix ends (add triangle)
        buildQuad(0, 29, 499, 7, cOrange1, cOrange1),
        buildQuad(0, 36, 494, 8, cOrange2, cOrange2),
        buildQuad(0, 44, 494, 9, cOrange3, cOrange3),
        buildQuad(0, 53, 482, 7, cOrange4, cOrange4), //!
        buildQuad(0, 60, 475, 10, cOrange5, cOrange5), //!
        buildQuad(0, 70, 466, 6, cOrange6, cOrange6),
        buildQuad(0, 76, 459, 8, cOrange7, cOrange7), //!
        buildQuad(0, 84, 455, 5, cOrange8, cOrange8)  //!
    };




    // FONTS
    sf::Font fStar4000;
    if (!fStar4000.loadFromFile("../fonts/Star4000.ttf"))
        return 2;

    fStar4000.setSmooth(false);

    // IMPORTANT! Feed in data

    std::vector< sf::Text > textShadows;
    std::vector< sf::Text > textObjects;

    sf::String textValues[] = { "Current", "Conditions", "Tartu", "Humidity:", "Dewpoint:", "Ceiling:", 
                                "Visibility:", "Pressure:", "Wind:", "Gusts to" };
    short textSizes[] = { 26, 26, 24, 25, 25, 25, 25, 25, 25, 25 }; // size in px
    sf::Color textColors[] = { cYellow, cYellow, cYellow, cWhite, cWhite, cWhite, cWhite, cWhite, cWhite, cWhite };
    short textPosX[] = { 167, 167, 316, 340, 340, 340, 340, 340, 83, 83 };
    short textPosY[] = { 30, 57, 98, 141, 181, 225, 267, 308, 308, 351 };

    for (u_long i = 0; i < std::size(textValues); i++) {
        textShadows.push_back(sf::Text(textValues[i], fStar4000, textSizes[i]));
        textShadows[i].setFillColor(cBlack2);
        textShadows[i].setPosition(sf::Vector2f(textPosX[i]+2, textPosY[i]+2));
        textShadows[i].setOutlineColor(cBlack2);
        textShadows[i].setOutlineThickness(1); // in px

        textObjects.push_back(sf::Text(textValues[i], fStar4000, textSizes[i]));
        textObjects[i].setFillColor(textColors[i]);
        textObjects[i].setPosition(sf::Vector2f(textPosX[i], textPosY[i]));
        textObjects[i].setOutlineColor(cBlack1);
        textObjects[i].setOutlineThickness(1); // in px
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
