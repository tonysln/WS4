#include <SFML/Graphics.hpp>
#include "GfxScreen.h"
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <map>

using std::stringstream;
using std::vector;
using std::string;
using std::array;
using std::map;


#ifndef WS4_GFXLOADER_H
#define WS4_GFXLOADER_H


namespace ws4
{
    map<string, sf::Font> loadFontMap();
    map<string, sf::Color> loadColorMap();
    map<string, sf::Texture> loadTextureMap();
    void loadStaticScreenVec(vector<GfxScreen> &stScrVec, 
                            map<string, sf::Font> &fontMap, map<string, sf::Color> &colorMap);



    // Construct an array of Vertices at (x,y) with size (w,h) and gradient of given colors
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col1, sf::Color col2);

    // Construct an array of Vertices at (x,y) with size (w,h) and a single color
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col);

    // Construct an array of Vertices at four given (x,y) points and given color
    array<sf::Vertex, 4> buildQuad(int x1, int y1, int x2, int y2, 
                                            int x3, int y3, int x4, int y4, sf::Color col);

    // Load data file and return as a vector of strings
    vector<string> loadDatFile(string &&fname);
    


    // Use stringstream to split string by comma, trim spaces around values and save to vector
    void splitCLine(vector<string> &lineSegs, stringstream &lnStream, string &seg, string &line);

    // Load icon positions (in sprite sheet) and return mapping [screen name] -> map<[icon name] -> [vector of position and size]>
    map<string, map<string, vector<int>>> loadIconPos();

    // Create sprites for icons and return mapping [sprite/icon name] -> [sf::Sprite]
    map<string, vector<sf::Sprite>> loadIcons(map<string, map<string, vector<int>>> &iconPos,
                                                map<string, map<string, string>> dM,
                                                sf::Texture &moonPhasesTexture,
                                                sf::Texture &curCondTexture,
                                                sf::Texture &extForcTexture,
                                                sf::Texture &regMapsTexture);
}

#endif //WS4_GFXLOADER_H