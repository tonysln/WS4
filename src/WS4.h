namespace ws4 
{
    std::array<sf::Vertex, 4> buildQuad(int x, int y, int w, int h, sf::Color col1, sf::Color col2);
    
    std::array<sf::Vertex, 4> buildQuad(int x1, int y1, int x2, int y2, 
                                            int x3, int y3, int x4, int y4, sf::Color col);
}