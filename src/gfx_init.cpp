#include <SFML/Graphics.hpp>
#include "gfx_init.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <codecvt>
#include <locale>
#include <array>


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


    map<string, sf::Color> parseColorData()
    {   
        map<string, sf::Color> cM;

        vector<string> lines = loadDatFile("../data/colors.dat");
        stringstream lnStream("");
        string seg;
        vector<string> lineSegs;

        for (auto &line : lines)
        {
            splitCLine(lineSegs, lnStream, seg, line);
            cM[lineSegs[0]] = sf::Color(stoi(lineSegs[1]), stoi(lineSegs[2]), stoi(lineSegs[3]));
        }

        return cM;
    }
    

    map<string, vector<array<sf::Vertex, 4>>> parseVertexData(map<string, sf::Color> &cM)
    {   
        map<string, vector<array<sf::Vertex, 4>>> vM;

        vector<string> lines = loadDatFile("../data/vertex_pos.dat");
        stringstream lnStream("");
        string seg;
        vector<string> lineSegs;

        string curScene;
        string partName;
        for (auto &line : lines) 
        {
            // New Scene
            if (line[0] == '[' && line[line.length()-1] == ']')
            {
                curScene = line.substr(1, line.length()-2);
                vM[curScene] = {};
                continue;
            }

            // Include already defined parts
            if (line[0] == '%' && line[line.length()-1] == '%')
            {   
                partName = line.substr(1, line.length()-2);

                vM[curScene].reserve(vM[curScene].size() + vM[partName].size());

                vM[curScene].insert(end(vM[curScene]), 
                                    begin(vM[partName]), 
                                    end(vM[partName]));
                continue;
            }

            splitCLine(lineSegs, lnStream, seg, line);

            if (size(lineSegs) == 6) // Build from 1 x,y, w,h and 2 colors
            {
                vM[curScene].push_back(
                    buildQuad(stoi(lineSegs[0]), stoi(lineSegs[1]), 
                              stoi(lineSegs[2]), stoi(lineSegs[3]), 
                                 cM[lineSegs[4]], cM[lineSegs[5]])
                );
            }
            else // Build from 4 x,y coordinates and 1 color
            {
                vM[curScene].push_back(
                    buildQuad(stoi(lineSegs[0]), stoi(lineSegs[1]), 
                              stoi(lineSegs[2]), stoi(lineSegs[3]),
                              stoi(lineSegs[4]), stoi(lineSegs[5]),
                              stoi(lineSegs[6]), stoi(lineSegs[7]), 
                                                  cM[lineSegs[8]])
                );
            }
        }

        return vM;
    }


    map<string, vector<sf::Text>> parseTextData(map<string, sf::Color> &cM, map<string, sf::Font> &fM, map<string, string> &dM)
    {        
        map<string, vector<sf::Text>> tM;

        vector<string> lines = loadDatFile("../data/text_pos.dat");
        stringstream lnStream("");
        string seg;
        vector<string> lineSegs;

        string curScene;
        string replVal;
        std::wstring textVal;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        for (auto &line : lines) 
        {
            // New Scene
            if (line[0] == '[' && line[line.length()-1] == ']')
            {
                curScene = line.substr(1, line.length()-2);
                tM[curScene] = {};
                continue;
            }

            splitCLine(lineSegs, lnStream, seg, line);

            // Text string    
            if (lineSegs[0][0] == '%')
            {
                // Replace with value in dM, else N/A
                replVal = lineSegs[0].substr(1, lineSegs[0][lineSegs[0].length()-1]);

                if (dM.contains(replVal))
                    lineSegs[0] = dM[replVal];
                else
                    lineSegs[0] = "N/A";
            }

            // Turn into wstring for degree sign support
            textVal = converter.from_bytes(lineSegs[0]);

            
            // First add shadow
            tM[curScene].push_back(sf::Text(textVal, fM[lineSegs[3]], stoi(lineSegs[1])*0.67));

            if (tM[curScene].size() < 1)
                return tM; // Avoid undefined behaviour

            tM[curScene].back().setFillColor(cM["cBlack2"]);
            tM[curScene].back().setPosition(sf::Vector2f(stoi(lineSegs[4])+3, stoi(lineSegs[5])+3));
            tM[curScene].back().setOutlineColor(cM["cBlack2"]);
            tM[curScene].back().setOutlineThickness(0);
            tM[curScene].back().setLetterSpacing(stod(lineSegs[6]));

            // Calculate origin/alignment
            char align = lineSegs[7][0];
            sf::Vector2f orig(0, 0);

            if (align == 'r')
                orig.x = tM[curScene].back().getLocalBounds().width;

            if (align == 'c')
                orig.x = tM[curScene].back().getLocalBounds().width / 2;

            tM[curScene].back().setOrigin(orig);
            tM[curScene].back().setScale(sf::Vector2f(1.5f, 1.5));

            // Then add text itself
            tM[curScene].push_back(sf::Text(textVal, fM[lineSegs[3]], stoi(lineSegs[1])*0.67));
            tM[curScene].back().setFillColor(cM[lineSegs[2]]);
            tM[curScene].back().setPosition(sf::Vector2f(stoi(lineSegs[4]), stoi(lineSegs[5])));
            tM[curScene].back().setOutlineColor(cM["cBlack1"]);
            tM[curScene].back().setOutlineThickness(1);
            tM[curScene].back().setLetterSpacing(stod(lineSegs[6]));
            tM[curScene].back().setOrigin(orig);
            tM[curScene].back().setScale(sf::Vector2f(1.5f, 1.5));
        }

        return tM;
    }

}
