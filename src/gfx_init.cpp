#include <SFML/Graphics.hpp>
#include "gfx_init.h"
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <map>

namespace ws4
{
    void loadDatFile(std::string &&fname)
    {   
        std::string ln;
        std::ifstream datFile(fname);
        if (datFile.is_open())
        {
            while (getline(datFile, ln))
            {
                if (ln.length() < 1 || ln.at(0) == '!')
                    continue;

                // TODO probably do stuff right here
                std::cout << ln << '\n';
            }

            datFile.close();
        }
        return;
    }

    void initColors()
    {   
        std::map<std::string, sf::Color> cM;

        //name, r, g, b  NEWLINE
        loadDatFile("../data/colors.dat");
        return;
    }
    
    void initVertices()
    {   
        std::map<std::string, std::array<sf::Vertex, 4>> vM;

        //[Name of object/class/scene]
        //if row len == 8:
        //  x,  y,  w,  h,  col1,  col2,    # of vertices   NEWLINE
        //elif row len == 10
        //  x1,y1, x2,y2, x3,y3, x4,y4,  col, # of vertices NEWLINE

        // if row starts and ends with % NEWLINE -> inlude that [object/class]
        loadDatFile("../data/vertex_pos.dat");
        return;
    }

    void initText()
    {
        std::map<std::string, sf::Text> tM;

        // text val, size, color, font, x, y, lttr spcng, orig_x, orig_y   NEWLINE
        // if text val starts and ends with %%, replace with corresponding value
        // from values dict, not found -> "N/A"
        loadDatFile("../data/text_pos.dat");
        return;
    }

}
