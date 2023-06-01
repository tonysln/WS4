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
    vector<array<sf::Vertex, 4>> buildPressureArrow(string dir, string col, string shadow);
    map<string, vector<int>> loadIconPositionsMap();

    // NB fix as soon as possible
    static map<string, sf::Font> fontMap = loadFontMap();
    static map<string, sf::Color> colorMap = loadColorMap();

    // Create vectors of vertices, textlabels and animicons for all screens.
    // Vectors fed into GfxScreen classes and saved into main screens vector in GfxManager.
    void loadCurrentConditions(vector<GfxScreen> &stScrVec);
    void loadLatestObservations(vector<GfxScreen> &stScrVec);
    void loadRegionalObservations(vector<GfxScreen> &stScrVec);
    void loadLocalForecast(vector<GfxScreen> &stScrVec);
    void loadRegionalForecast(vector<GfxScreen> &stScrVec);
    void loadExtendedForecast(vector<GfxScreen> &stScrVec);
    void loadAlmanac(vector<GfxScreen> &stScrVec);

    // Construct an array of Vertices at (x,y) with size (w,h) and gradient of given colors
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col1, sf::Color col2);

    // Construct an array of Vertices at (x,y) with size (w,h) and a single color
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, string col);

    // Construct an array of Vertices at four given (x,y) points and given color
    array<sf::Vertex, 4> buildQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, sf::Color col);
}

#endif //WS4_GFXLOADER_H