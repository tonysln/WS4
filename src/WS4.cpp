#include <SFML/Graphics.hpp>
#include <vector>


int main()
{
    /*
     * VARIABLES & CONSTS
     */
    const char  TITLE[] = "WS4 v22.9.13";
    const short FPS = 30;

    const float SCALE = 1.f;
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
    const sf::Color cYellow(205, 185, 0);
    const sf::Color cOrange1(195, 91, 0);
    const sf::Color cOrange2(178, 82, 0);
    const sf::Color cOrange3(157, 75, 19);
    const sf::Color cOrange4(142, 66, 26);
    const sf::Color cOrange5(123, 56, 36);
    const sf::Color cOrange6(105, 46, 46);
    const sf::Color cOrange7(89, 42, 62);
    const sf::Color cOrange8(71, 34, 64);
    const sf::Color cLtBlue1(86, 91, 202);
    const sf::Color cLtBlue2(66, 78, 202);
    const sf::Color cLtBlue3(44, 66, 202);
    const sf::Color cLtBlue4(37, 57, 202);
    const sf::Color cLtBlue5(9, 49, 202);
    const sf::Color cLtBlue6(0, 40, 203);
    const sf::Color cLtBlue7(0, 36, 203);
    const sf::Color cLtBlue8(0, 34, 203);
    const sf::Color cRed(112, 35, 35);


    /*
     * WINDOW & VIDEOMODE
     */
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), TITLE, 
                                                sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(FPS);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width/2 - WIN_WIDTH/2, 
                                    desktop.height/2 - WIN_HEIGHT/2));
    
    // https://www.sfml-dev.org/tutorials/2.5/system-time.php



    /*
     * VERTEX ARRAYS & SHAPES
     */
    // TODO load these from somewhere or place into other files
    // TODO method to generate these automatically
    // Create Class that inits all shapes and icons,
    // extend for every scene

    sf::Vertex bottomBar[] =
    {
        sf::Vertex(sf::Vector2f(0, WIN_HEIGHT - 80), cDkBlue2),
        sf::Vertex(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT - 80), cDkBlue2),
        sf::Vertex(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT), cDkBlue2),
        sf::Vertex(sf::Vector2f(0, WIN_HEIGHT), cDkBlue2)
    };
    
    sf::Vertex bgGradient[] =
    {
        sf::Vertex(sf::Vector2f(0, 100), cOrange8),
        sf::Vertex(sf::Vector2f(WIN_WIDTH, 100), cOrange8),
        sf::Vertex(sf::Vector2f(WIN_WIDTH, 400), cOrange2),
        sf::Vertex(sf::Vector2f(0, 400), cOrange2)
    };

    sf::Vertex bgRect[] =
    {
        sf::Vertex(sf::Vector2f(50, 110), cDkBlue2),
        sf::Vertex(sf::Vector2f(50+WIN_WIDTH-100, 110), cDkBlue2),
        sf::Vertex(sf::Vector2f(50+WIN_WIDTH-100, 110+WIN_HEIGHT-200), cDkBlue2),
        sf::Vertex(sf::Vector2f(50, 110+WIN_HEIGHT-200), cDkBlue2)
    };

    sf::Vertex bgRect2[] =
    {
        sf::Vertex(sf::Vector2f(55, 115), cLtBlue4),
        sf::Vertex(sf::Vector2f(55+WIN_WIDTH-110, 115), cLtBlue4),
        sf::Vertex(sf::Vector2f(55+WIN_WIDTH-110, 115+WIN_HEIGHT-210), cLtBlue4),
        sf::Vertex(sf::Vector2f(55, 115+WIN_HEIGHT-210), cLtBlue4)
    };



    // FONTS
    sf::Font fStar4000;
    if (!fStar4000.loadFromFile("../fonts/Star4000.ttf"))
        return 2;
    

    // IMPORTANT! Feed in data; macros?

    std::vector< sf::Text > textObjects;

    sf::String textValues[] = { "Tartu", "Cloudy" };
    short textSizes[] = { 28, 30 }; // size in px
    sf::Color textColors[] = { cYellow, cWhite };
    short textPosX[] = { 200, 240 };
    short textPosY[] = { 130, 160 };

    for (short i = 0; i < std::size(textValues); i++) {
        textObjects.push_back(sf::Text(textValues[i], fStar4000, textSizes[i]));
        textObjects[i].setFillColor(textColors[i]);
        textObjects[i].setPosition(textPosX[i], textPosY[i]);
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

        window.draw(bgGradient, 4, sf::Quads);
        window.draw(bottomBar, 4, sf::Quads);
        window.draw(bgRect, 4, sf::Quads);
        window.draw(bgRect2, 4, sf::Quads);

        for (short i = 0; i < std::size(textObjects); i++){
            window.draw(textObjects[i]);
        }

        window.display();
    }

    return EXIT_SUCCESS;
};
