using std::vector;
using std::string;
using std::array;
using std::map;


namespace ws4 
{
    class WS4 
    {
        const short FPS = 7;
        const float SCALE = 1.0f;
        const short WIN_WIDTH = 640;
        const short WIN_HEIGHT = 480;
        const short ANIM_FRAMES = 7;

        sf::ContextSettings sts;
        sf::View view;

        std::time_t epoch = std::time(nullptr);
        char timeStr[12];
        char timeAPStr[6];
        char dateStr[12];

        map<string, sf::Font> fM;
        map<string, sf::Color> cM;
        map<string, vector<sf::Text>> tM;
        map<string, vector<array<sf::Vertex, 4>>> vM;
        map<string, map<string, vector<int>>> iconPos;
        map<string, vector<sf::Sprite>> iM;
        
        sf::Texture moonPhasesTexture;
        sf::Texture curCondTexture;
        sf::Texture extForcTexture;
        sf::Texture regMapsTexture;
        int animFrame;


    public:
        sf::RenderWindow window;
        sf::Music musicPlayer;
        map<string, map<string, string>> dM;
        
        const vector<string> scr = 
        {
            "Current-Conditions",
            "Latest-Observations",
            "Local-Forecast-1",
            "Local-Forecast-2",
            "Extended-Forecast",
            "Almanac",
            "Forecast-For",
            "Air-Quality"
        };
        short cur = 0;
        short icoCt = 0;

        WS4();
        void nextScreen();
        void prevScreen();
        void nextScreenUpdate();
        void loadFonts();
        void loadGraphics();
        void loadData();
        void drawGraphics();
        void drawText();
        void loadMusic();
        void changeSong();
    };

    
}