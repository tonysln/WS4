#include <SFML/Graphics.hpp>


int main()
{
    /*
     * VARIABLES & CONSTS
     */
    short WIN_WIDTH = 640;
    short WIN_HEIGHT = 480;

    sf::Color bgPurple = sf::Color( 28,  10,  87);
    sf::Color fgPurple = sf::Color(255,   0,   0);
    sf::Color bgBlue   = sf::Color( 33,  40,  90);
    sf::Color fgBlue   = sf::Color( 35,  50, 112);
    sf::Color fgBlue2  = sf::Color( 43,  60, 128);
    sf::Color yellow   = sf::Color(255,   0,   0);
    sf::Color bgOrange = sf::Color(192,  91,   2);
    sf::Color fgOrange = sf::Color(255,   0,   0);




    /*
     * WINDOW & VIDEOMODE
     */
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "WS4 v22.9.13", 
                                                sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(60);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width/2 - WIN_WIDTH/2, desktop.height/2 - WIN_HEIGHT/2));
    
    // https://www.sfml-dev.org/tutorials/2.5/system-time.php



    /*
     * VERTEX ARRAYS & SHAPES
     */
    // TODO load these from somewhere or place into other files
    // TODO place into array, specify where to draw (x,y)
    // https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
    // https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
    // https://en.sfml-dev.org/forums/index.php?topic=6750.0
    sf::RectangleShape bottomBar(sf::Vector2f(WIN_WIDTH, 80.f));
    bottomBar.setFillColor(fgBlue);
    bottomBar.setPosition(0.f, WIN_HEIGHT - bottomBar.getSize().y);

    sf::RectangleShape bgGradient(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT-180));
    bgGradient.setFillColor(bgOrange);
    bgGradient.setPosition(0, 100);

    sf::RectangleShape bgRect(sf::Vector2f(WIN_WIDTH-100, WIN_HEIGHT-200));
    bgRect.setFillColor(bgBlue);
    bgRect.setPosition(50, 110);

    sf::RectangleShape bgRect2(sf::Vector2f(WIN_WIDTH-110, WIN_HEIGHT-210));
    bgRect2.setFillColor(fgBlue2);
    bgRect2.setPosition(55, 115);



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
        window.clear(bgPurple);
        window.draw(bgGradient);
        window.draw(bottomBar);
        window.draw(bgRect);
        window.draw(bgRect2);
        window.display();
    }

    return EXIT_SUCCESS;
}
