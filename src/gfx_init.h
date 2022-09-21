#include <map>

using std::stringstream;
using std::vector;
using std::string;
using std::array;
using std::map;


namespace ws4
{
    // Construct an array of Vertices at (x,y) with size (w,h) and gradient of given colors
    array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col1, sf::Color col2);

    // Construct an array of Vertices at four given (x,y) points and given color
    array<sf::Vertex, 4> buildQuad(int x1, int y1, int x2, int y2, 
                                            int x3, int y3, int x4, int y4, sf::Color col);

    // Load data file and return as a vector of strings
    vector<string> loadDatFile(string &&fname);
    
    // Read in colors data file and return mapping [color name] -> [sf::Color]
    map<string, sf::Color> parseColorData();
    
    // Read in vertex data (shapes and screen layouts), return mapping
    // [screen name] -> [vector of Vertex arrays]
    map<string, vector<array<sf::Vertex, 4>>> parseVertexData(map<string, sf::Color> &cM);
    
    // Read in text data and return mapping [screen name] -> [vector of sf::Text]
    map<string, vector<sf::Text>> parseTextData(map<string, sf::Color> &cM, map<string, sf::Font> &fM, map<string, map<string, string>> &dM);

    // Use stringstream to split string by comma, trim spaces around values and save to vector
    void splitCLine(vector<string> &lineSegs, stringstream &lnStream, string &seg, string &line);
}
