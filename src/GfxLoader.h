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
using sf::Color;
using sf::Font;
using std::map;


#ifndef WS4_GFXLOADER_H
#define WS4_GFXLOADER_H


namespace ws4
{
    map<string, sf::Font> loadFontMap();
    map<string, sf::Color> loadColorMap();
    map<string, sf::Texture> loadTextureMap();
    vector<array<sf::Vertex, 4>> buildPressureArrow(bool dirUp, sf::Color col, sf::Color shadow);
    map<string, vector<int>> loadIconPositionsMap();

    // Create vectors of vertices, textlabels and animicons for all screens.
    // Vectors fed into GfxScreen classes and saved into main screens vector in GfxManager.
    void loadCurrentConditions(vector<GfxScreen> &stScrVec, map<string, Font> &fontMap, map<string, Color> &colorMap);
    void loadLatestObservations(vector<GfxScreen> &stScrVec, map<string, Font> &fontMap, map<string, Color> &colorMap);
    void loadRegionalObservations(vector<GfxScreen> &stScrVec, map<string, Font> &fontMap, map<string, Color> &colorMap);
    void loadLocalForecast(vector<GfxScreen> &stScrVec, map<string, Font> &fontMap, map<string, Color> &colorMap);
    void loadRegionalForecast(vector<GfxScreen> &stScrVec, map<string, Font> &fontMap, map<string, Color> &colorMap);
    void loadExtendedForecast(vector<GfxScreen> &stScrVec, map<string, Font> &fontMap, map<string, Color> &colorMap);
    void loadAlmanac(vector<GfxScreen> &stScrVec, map<string, Font> &fontMap, map<string, Color> &colorMap);

    // Construct an array of Vertices at (x,y) with size (w,h) and gradient of given colors
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col1, sf::Color col2);

    // Construct an array of Vertices at (x,y) with size (w,h) and a single color
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col);

    // Construct an array of Vertices at four given (x,y) points and given color
    array<sf::Vertex, 4> buildQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, sf::Color col);
}

#endif //WS4_GFXLOADER_H