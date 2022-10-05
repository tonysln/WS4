#include "GfxLoader.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>


using std::to_string;
using std::stoi;


namespace ws4
{
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col1, sf::Color col2)
    {
        array<sf::Vertex, 4> quad = 
        {
            sf::Vertex(sf::Vector2f(x+w, y), col1),
            sf::Vertex(sf::Vector2f(x, y), col1),
            sf::Vertex(sf::Vector2f(x+w, y+h), col2),
            sf::Vertex(sf::Vector2f(x, y+h), col2)
        };
        return quad;
    }


    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col)
    {
        return buildQuad(x, y, w, h, col, col);
    }


    array<sf::Vertex, 4> buildQuad(int x1, int y1, int x2, int y2, 
                                            int x3, int y3, int x4, int y4, sf::Color col)
    {
        array<sf::Vertex, 4> quad = 
        {
            sf::Vertex(sf::Vector2f(x4, y4), col),
            sf::Vertex(sf::Vector2f(x1, y1), col),
            sf::Vertex(sf::Vector2f(x3, y3), col),
            sf::Vertex(sf::Vector2f(x2, y2), col)
        };
        return quad;
    }


    map<string, sf::Font> loadFontMap()
    {
        map<string, sf::Font> fM;

        if(!fM["Star4000"].loadFromFile("../fonts/Star4000.ttf"))
            return fM;
        if(!fM["Star4000-Extended"].loadFromFile("../fonts/Star4000-Extended.ttf"))
            return fM;
        if(!fM["Star4000-Large"].loadFromFile("../fonts/Star4000-Large.ttf"))
            return fM;
        if(!fM["Star4000-Large-Compressed"].loadFromFile("../fonts/Star4000-Large-Compressed.ttf"))
            return fM;
        if(!fM["Star4000-Small"].loadFromFile("../fonts/Star4000-Small.ttf"))
            return fM;

        return fM;
    }


    map<string, sf::Color> loadColorMap()
    {
        map<string, sf::Color> cM =
        {
            {"#0e0e0e", sf::Color(14,14,14)},
            {"#141414", sf::Color(20,20,20)},
            {"#d7d7d7", sf::Color(215,215,215)},
            {"#afafaf", sf::Color(175,175,175)},
            {"#3d3d3d", sf::Color(61,61,61)},
            {"#1c0a57", sf::Color(28,10,87)},
            {"#233270", sf::Color(35,50,112)},
            {"#2e1251", sf::Color(46,18,81)},
            {"#c05d02", sf::Color(192,93,2)},
            {"#2652b2", sf::Color(38,82,178)},
            {"#254ba3", sf::Color(37,75,163)},
            {"#254698", sf::Color(37,70,152)},
            {"#24408c", sf::Color(36,64,140)},
            {"#233a80", sf::Color(35,58,128)},
            {"#223474", sf::Color(34,52,116)},
            {"#222f69", sf::Color(34,47,105)},
            {"#212b60", sf::Color(33,43,96)},
            {"#21285a", sf::Color(33,40,90)},
            {"#c35b00", sf::Color(195,91,0)},
            {"#b25200", sf::Color(178,82,0)},
            {"#9d4b13", sf::Color(157,75,19)},
            {"#8e421a", sf::Color(142,66,26)},
            {"#7b3824", sf::Color(123,56,36)},
            {"#692e2e", sf::Color(105,46,46)},
            {"#592a3e", sf::Color(89,42,62)},
            {"#472240", sf::Color(71,34,64)},
            {"#cdb900", sf::Color(205,185,0)},
            {"#7d3c28", sf::Color(125,60,40)},
            {"#828af5", sf::Color(130,138,245)},

            {"#565bca", sf::Color(86,91,202)},
            {"#424eca", sf::Color(66,78,202)},
            {"#2c42ca", sf::Color(44,66,202)},
            {"#2539ca", sf::Color(37,57,202)},
            {"#0931ca", sf::Color(9,49,202)},
            {"#0028cb", sf::Color(0,40,203)},
            {"#0024cb", sf::Color(0,36,203)},
            {"#0022cb", sf::Color(0,34,203)},

            {"#f0dc0a", sf::Color(240,220,10)},
            {"#f09600", sf::Color(240,150,0)},
            {"#fa6405", sf::Color(250,100,5)},
            {"#f52805", sf::Color(245,40,5)}
        };

        return cM;
    }


    map<string, sf::Texture> loadTextureMap()
    {
        map<string, sf::Texture> tM;
        
        if (!tM["Moon"].loadFromFile("../graphics/icons/Moon-Phases.png"))
            return tM;
        if (!tM["CC"].loadFromFile("../graphics/icons/Current-Conditions.png"))
            return tM;
        if (!tM["EF"].loadFromFile("../graphics/icons/Extended-Forecast.png"))
            return tM;
        if (!tM["RF"].loadFromFile("../graphics/icons/Regional-Maps.png"))
            return tM;

        return tM;
    }


    void loadStaticScreenVec(vector<GfxScreen> &stScrVec, map<string, sf::Font> &fontMap, 
                                                            map<string, sf::Color> &colorMap)
    {
        stScrVec.push_back
        (
            // Screen 0 - "Current Conditions"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, colorMap["#2652b2"]),
                    buildQuad(55, 94, 527, 302, colorMap["#254ba3"]),
                    buildQuad(57, 96, 523, 298, colorMap["#254698"]),
                    buildQuad(59, 98, 519, 294, colorMap["#24408c"]),
                    buildQuad(61, 100, 515, 290, colorMap["#233a80"]),
                    buildQuad(63, 102, 511, 286, colorMap["#223474"]),
                    buildQuad(65, 104, 507, 282, colorMap["#222f69"]),
                    buildQuad(66, 105, 506, 281, colorMap["#212b60"]),
                    buildQuad(67, 106, 505, 280, colorMap["#21285a"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Current", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 21, colorMap, 0),
                    TextLabel("Conditions", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                    TextLabel("Humidity:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 141, colorMap, 0),
                    TextLabel("Dewpoint:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 181, colorMap, 0),
                    TextLabel("Ceiling:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 225, colorMap, 0),
                    TextLabel("Visibility:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 267, colorMap, 0),
                    TextLabel("Pressure:", fontMap["Star4000"], "#d7d7d7", 33, 1, 0.55, 330, 308, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 1 - "Latest Observations"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, colorMap["#2652b2"]),
                    buildQuad(55, 94, 527, 302, colorMap["#254ba3"]),
                    buildQuad(57, 96, 523, 298, colorMap["#254698"]),
                    buildQuad(59, 98, 519, 294, colorMap["#24408c"]),
                    buildQuad(61, 100, 515, 290, colorMap["#233a80"]),
                    buildQuad(63, 102, 511, 286, colorMap["#223474"]),
                    buildQuad(65, 104, 507, 282, colorMap["#222f69"]),
                    buildQuad(66, 105, 506, 281, colorMap["#212b60"]),
                    buildQuad(67, 106, 505, 280, colorMap["#21285a"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Latest Observations", fontMap["Star4000"], "#cdb900", 34, 3, 0.5, 163, 35, colorMap, 0),
                    TextLabel("F°", fontMap["Star4000-Small"], "#d7d7d7", 30, 0, 1.0, 305, 78, colorMap, 0),
                    TextLabel("WEATHER", fontMap["Star4000-Small"], "#d7d7d7", 30, 0, 1.0, 365, 78, colorMap, 0),
                    TextLabel("WIND", fontMap["Star4000-Small"], "#d7d7d7", 30, 0, 1.0, 505, 78, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 2 - "Regional Observations"
            GfxScreen {
                vector {
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Regional", fontMap["Star4000"], "#cdb900", 34, 3, 0.6, 163, 21, colorMap, 0),
                    TextLabel("Observations", fontMap["Star4000"], "#cdb900", 34, 3, 0.6, 163, 50, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 3 - "36-Hour Forecast 1/3"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, colorMap["#2652b2"]),
                    buildQuad(55, 94, 527, 302, colorMap["#254ba3"]),
                    buildQuad(57, 96, 523, 298, colorMap["#254698"]),
                    buildQuad(59, 98, 519, 294, colorMap["#24408c"]),
                    buildQuad(61, 100, 515, 290, colorMap["#233a80"]),
                    buildQuad(63, 102, 511, 286, colorMap["#223474"]),
                    buildQuad(65, 104, 507, 282, colorMap["#222f69"]),
                    buildQuad(66, 105, 506, 281, colorMap["#212b60"]),
                    buildQuad(67, 106, 505, 280, colorMap["#21285a"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Local Forecast", fontMap["Star4000"], "#cdb900", 34, 3, 0.6, 163, 35, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 4 - "36-Hour Forecast 2/3"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, colorMap["#2652b2"]),
                    buildQuad(55, 94, 527, 302, colorMap["#254ba3"]),
                    buildQuad(57, 96, 523, 298, colorMap["#254698"]),
                    buildQuad(59, 98, 519, 294, colorMap["#24408c"]),
                    buildQuad(61, 100, 515, 290, colorMap["#233a80"]),
                    buildQuad(63, 102, 511, 286, colorMap["#223474"]),
                    buildQuad(65, 104, 507, 282, colorMap["#222f69"]),
                    buildQuad(66, 105, 506, 281, colorMap["#212b60"]),
                    buildQuad(67, 106, 505, 280, colorMap["#21285a"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Local Forecast", fontMap["Star4000"], "#cdb900", 34, 3, 0.6, 163, 35, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 5 - "36-Hour Forecast 3/3"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, colorMap["#2652b2"]),
                    buildQuad(55, 94, 527, 302, colorMap["#254ba3"]),
                    buildQuad(57, 96, 523, 298, colorMap["#254698"]),
                    buildQuad(59, 98, 519, 294, colorMap["#24408c"]),
                    buildQuad(61, 100, 515, 290, colorMap["#233a80"]),
                    buildQuad(63, 102, 511, 286, colorMap["#223474"]),
                    buildQuad(65, 104, 507, 282, colorMap["#222f69"]),
                    buildQuad(66, 105, 506, 281, colorMap["#212b60"]),
                    buildQuad(67, 106, 505, 280, colorMap["#21285a"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Local Forecast", fontMap["Star4000"], "#cdb900", 34, 3, 0.6, 163, 35, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 6 - "Regional Forecast Map"
            GfxScreen {
                vector {
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Forecast For", fontMap["Star4000"], "#cdb900", 34, 3, 0.6, 163, 21, colorMap, 0),
                    TextLabel("Weekday", fontMap["Star4000"], "#cdb900", 34, 3, 0.6, 163, 50, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 7 - "Extended Forecast"
            GfxScreen {
                vector {
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Left panel
                    buildQuad(37, 100, 175, 296, colorMap["#0e0e0e"]),
                    buildQuad(40, 103, 169, 290, colorMap["#828af5"]),
                    buildQuad(44, 106, 161, 284, colorMap["#0e0e0e"]),
                    buildQuad(46, 108, 157, 32, colorMap["#565bca"]),
                    buildQuad(46, 140, 157, 35, colorMap["#424eca"]),
                    buildQuad(46, 175, 157, 36, colorMap["#2c42ca"]),
                    buildQuad(46, 211, 157, 34, colorMap["#2539ca"]),
                    buildQuad(46, 245, 157, 34, colorMap["#0931ca"]),
                    buildQuad(46, 279, 157, 37, colorMap["#0028cb"]),
                    buildQuad(46, 316, 157, 36, colorMap["#0024cb"]),
                    buildQuad(46, 352, 157, 36, colorMap["#0022cb"]),
                    // Center panel
                    buildQuad(231, 100, 175, 296, colorMap["#0e0e0e"]),
                    buildQuad(234, 103, 169, 290, colorMap["#828af5"]),
                    buildQuad(238, 106, 161, 284, colorMap["#0e0e0e"]),
                    buildQuad(240, 108, 157, 32, colorMap["#565bca"]),
                    buildQuad(240, 140, 157, 35, colorMap["#424eca"]),
                    buildQuad(240, 175, 157, 36, colorMap["#2c42ca"]),
                    buildQuad(240, 211, 157, 34, colorMap["#2539ca"]),
                    buildQuad(240, 245, 157, 34, colorMap["#0931ca"]),
                    buildQuad(240, 279, 157, 37, colorMap["#0028cb"]),
                    buildQuad(240, 316, 157, 36, colorMap["#0024cb"]),
                    buildQuad(240, 352, 157, 36, colorMap["#0022cb"]),
                    // Right panel
                    buildQuad(426, 100, 175, 296, colorMap["#0e0e0e"]),
                    buildQuad(429, 103, 169, 290, colorMap["#828af5"]),
                    buildQuad(433, 106, 161, 284, colorMap["#0e0e0e"]),
                    buildQuad(435, 108, 157, 32, colorMap["#565bca"]),
                    buildQuad(435, 140, 157, 35, colorMap["#424eca"]),
                    buildQuad(435, 175, 157, 36, colorMap["#2c42ca"]),
                    buildQuad(435, 211, 157, 34, colorMap["#2539ca"]),
                    buildQuad(435, 245, 157, 34, colorMap["#0931ca"]),
                    buildQuad(435, 279, 157, 37, colorMap["#0028cb"]),
                    buildQuad(435, 316, 157, 36, colorMap["#0024cb"]),
                    buildQuad(435, 352, 157, 36, colorMap["#0022cb"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Area", fontMap["Star4000"], "#d7d7d7", 34, 2, 0.5, 163, 21, colorMap, 0),
                    TextLabel("Extended Forecast", fontMap["Star4000"], "#cdb900", 34, 2, 0.5, 163, 50, colorMap, 0),
                    // TextLabel("Lo", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                    // TextLabel("Hi", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                    // TextLabel("Lo", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                    // TextLabel("Hi", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                    // TextLabel("Lo", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                    // TextLabel("Hi", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 50, colorMap, 0),
                }
            }
        );
        stScrVec.push_back
        (
            // Screen 8 - "Almanac"
            GfxScreen {
                vector {
                    // Top gradient
                    buildQuad(0, 90, 640, 40, colorMap["#2e1251"], colorMap["#7d3c28"]),
                    buildQuad(0, 130, 640, 62, colorMap["#7d3c28"], colorMap["#c35b00"]),
                    // Gray background
                    buildQuad(0, 192, 640, 206, colorMap["#3d3d3d"]),
                    // Top bar
                    buildQuad(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                },
                vector {
                    TextLabel("Almanac", fontMap["Star4000"], "#cdb900", 34, 3, 0.9, 163, 35, colorMap, 0),
                    // TextLabel("Sunrise:", fontMap["Star4000"], "#d7d7d7", 34, 1, 0.9, 163, 35, colorMap, 2),
                    // TextLabel("Sunset:", fontMap["Star4000"], "#d7d7d7", 34, 1, 0.9, 163, 35, colorMap, 2),
                    // TextLabel("Moon Data:", fontMap["Star4000"], "#cdb900", 34, 1, 0.9, 163, 35, colorMap, 0),
                }
            }
        );
    }





    vector<string> loadDatFile(string &&fname)
    {   
        vector<string> datFileLines;
        string ln;
        std::ifstream datFile(fname);
        if (datFile.is_open())
        {
            while (getline(datFile, ln))
            {
                if (ln.length() < 1 || ln[0] == '!')
                    continue;

                datFileLines.push_back(ln);
            }
            datFile.close();
        }
        return datFileLines;
    }


    void splitCLine(vector<string> &lineSegs, stringstream &lnStream, string &seg, string &line)
    {   
        lineSegs.clear();
        lnStream << line;

        while(getline(lnStream, seg, ','))
        {   
            seg.erase(0, seg.find_first_not_of(' '));
            seg.erase(seg.find_last_not_of(' ') + 1);
            lineSegs.push_back(seg);
        }

        lnStream.str("");
        lnStream.clear();
    }
    



    map<string, map<string, vector<int>>> loadIconPos()
    {
        map<string, map<string, vector<int>>> iconPos;

        vector<string> lines = loadDatFile("../data/icon_pos.dat");
        string curScene;
        stringstream lnStream("");
        string seg;
        vector<string> lineSegs;

        for (auto &line : lines) 
        {
            // New Scene
            if (line[0] == '[' && line[line.length()-1] == ']')
            {
                curScene = line.substr(1, line.length()-2);
                iconPos[curScene] = {};
                continue;
            }

            splitCLine(lineSegs, lnStream, seg, line);
            iconPos[curScene][lineSegs[0]] = {stoi(lineSegs[1]), stoi(lineSegs[2]), stoi(lineSegs[3])};
        }

        return iconPos;
    }


    map<string, vector<sf::Sprite>> loadIcons(map<string, map<string, vector<int>>> &iconPos,
                                                map<string, map<string, string>> dM,
                                                sf::Texture &moonPhasesTexture,
                                                sf::Texture &curCondTexture,
                                                sf::Texture &extForcTexture,
                                                sf::Texture &regMapsTexture)
    {
        map<string, vector<sf::Sprite>> iM;
        
        // Current Conditions Icon
        iM["Current-Conditions"].push_back(sf::Sprite(curCondTexture));
        iM["Current-Conditions"][0].setPosition(sf::Vector2f(178, 174));
        iM["Current-Conditions"][0].setTextureRect(sf::IntRect(
            sf::Vector2i(0*iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][0], 
                        iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][1]), 
            sf::Vector2i(iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][0], 
                        iconPos["Current-Conditions"][dM["Current-Conditions"]["icon-0"]][2])
        ));
        iM["Current-Conditions"][0].setOrigin(sf::Vector2f(
            iM["Current-Conditions"][0].getGlobalBounds().width/2, 0
        ));

        // Moon Icons
        short moonXPos[] = {135, 255, 375, 495};
        for (short i = 0; i < 4; ++i)
        {
            iM["Almanac"].push_back(sf::Sprite(moonPhasesTexture));
            iM["Almanac"][i].setTextureRect(sf::IntRect(
                sf::Vector2i(0*iconPos["Almanac"][dM["Almanac"]["icon-" + to_string(i)]][0], 
                                iconPos["Almanac"][dM["Almanac"]["icon-" + to_string(i)]][1]), 
                sf::Vector2i(iconPos["Almanac"][dM["Almanac"]["icon-" + to_string(i)]][0], 
                                iconPos["Almanac"][dM["Almanac"]["icon-"  + to_string(i)]][2])
            ));
            iM["Almanac"][i].setOrigin(sf::Vector2f(iM["Almanac"][i].getGlobalBounds().width/2, 0));
            iM["Almanac"][i].setPosition(sf::Vector2f(moonXPos[i], 270));
        }


        // Extended Forecast Icons
        short extForcXPos[] = {120, 320, 510};
        for (short i = 0; i < 3; ++i)
        {
            iM["Extended-Forecast"].push_back(sf::Sprite(extForcTexture));
            iM["Extended-Forecast"][i].setPosition(sf::Vector2f(extForcXPos[i], 150));
            iM["Extended-Forecast"][i].setTextureRect(sf::IntRect(
                sf::Vector2i(0*iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-" + to_string(i)]][0], 
                            iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-" + to_string(i)]][1]), 
                sf::Vector2i(iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-" + to_string(i)]][0], 
                            iconPos["Extended-Forecast"][dM["Extended-Forecast"]["icon-" + to_string(i)]][2])
            ));
            iM["Extended-Forecast"][i].setOrigin(sf::Vector2f(
                iM["Extended-Forecast"][i].getGlobalBounds().width/2, 0
            )); 
        }


        // Regional Forecast Map Icons
        short numCities = std::stoi(dM["Forecast-For"]["num-cities"]);
        for (short i = 0; i < numCities; ++i)
        {
            iM["Forecast-For"].push_back(sf::Sprite(regMapsTexture));
            iM["Forecast-For"][i].setPosition(sf::Vector2f(
                stoi(dM["Forecast-For"]["icon-" + to_string(i) + "-x"]), 
                stoi(dM["Forecast-For"]["icon-" + to_string(i) + "-y"])
            ));
            iM["Forecast-For"][i].setTextureRect(sf::IntRect(
                sf::Vector2i(0*iconPos["Forecast-For"][dM["Forecast-For"]["icon-" + to_string(i)]][0], 
                            iconPos["Forecast-For"][dM["Forecast-For"]["icon-" + to_string(i)]][1]), 
                sf::Vector2i(iconPos["Forecast-For"][dM["Forecast-For"]["icon-" + to_string(i)]][0], 
                            iconPos["Forecast-For"][dM["Forecast-For"]["icon-" + to_string(i)]][2])
            ));
            iM["Forecast-For"][i].setOrigin(sf::Vector2f(
                iM["Forecast-For"][i].getGlobalBounds().width/2, 0
            )); 
        }


        return iM;
    }

}
