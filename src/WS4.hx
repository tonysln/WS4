import GfxClock;
import GfxLDL;
import GfxScreen;
import GfxLoader;
import MapCity;
import DataProc;
import AnimIcon;

import sys.FileSystem;


class WS4 {
	private static var ANIM_FRAMES: Int = 7;
    private static var FPS: Int = 30;
    private static var WIN_WIDTH: Int = 640;
    private static var WIN_HEIGHT: Int = 480;
    private static var SCALE: Float = 1.0;
    private static var window: Dynamic;
    private static var view: Dynamic;


    // Timers & Counters
    private static var iconFrame: Int = 0;
    private static var iconFrameCounter: Float = 0.0;
    private static var sceneTime: Float = 12.0;
    private static var LDLTime: Float = 5.0;
    private static var dispLDLTimes: Int = 2;
    private static var scrLDLTimes: Int = 1;

    private var sceneTimer: Dynamic;
    private var LDLTimer: Dynamic;

    private static var scrIdx: Int = 0;

    private var scr: Array<String>;

    // Graphics
    private var textureMap: Map<String, Dynamic>;
    private var iconPosMap: Map<String, Array<Int>>;
    private var screens: Array<GfxScreen>;
    private var regMapCities: Array<MapCity>;
    private var forcMapCities: Array<MapCity>;

    private static var showLogo: Bool = false;
    private var logo: Dynamic;
    
    private var clock: GfxClock;
    private var LDL: GfxLDL;


    // Data
    private var LDLStrIdx: Int = 0;
    private var LDLStrings: Array<String>;
    private var LDLScrollStr: Array<String>;
    private var cityROXValues: Array<String>;
    private var cityROYValues: Array<String>;
    private var cityRFXValues: Array<String>;
    private var cityRFYValues: Array<String>;
    private var data: Array<Array<String>>;


    // Music
    private var songsPaths: Array<String>;
    private var musicStarted: Bool = false;
    private var musicEnabled: Bool = true;
    private var volume: Float = 20.0;
    private var songIdx: Int = 0;
    private var musicPlayer: Dynamic;


	public function new() 
	{
        untyped __cpp__('window.create(VideoMode(WIN_WIDTH*SCALE, WIN_HEIGHT*SCALE), "WS4", Style.None);

        window.setFramerateLimit(FPS);
        var desktop = VideoMode.getDesktopMode();
        window.setPosition(Vector2i(desktop.width/4 - WIN_WIDTH*SCALE/2,
                                        desktop.height/4 - WIN_HEIGHT*SCALE/2));

        // View settings for scaling 
        view.setSize(Vector2f(window.getSize().x/SCALE, window.getSize().y/SCALE));
        view.setCenter(Vector2f(view.getSize().x/2, view.getSize().y/2));
        window.setView(view);');

        this.scr = [
	        "Current-Conditions",
	        "Latest-Observations",
	        "Regional-Observations",
	        "Local-Forecast-1",
	        "Local-Forecast-2",
	        "Local-Forecast-3",
	        "Forecast-For",
	        "Extended-Forecast",
	        "Almanac"
        ];

        this.screens = [];
        this.regMapCities = [];
        forcMapCities = [];
        this.LDLStrings = [];
        this.LDLScrollStr = [];
        this.cityROXValues = [];
        this.cityROYValues = [];
        this.cityRFXValues = [];
        this.cityRFYValues = [];
        this.data = [];
        this.songsPaths = [];
	}


	public function nextScreen(): Void
    {
        scrIdx = (scrIdx + 1) % scr.length;
    }


    public function prevScreen(): Void
    {
        scrIdx = (scrIdx - 1 + scr.length) % scr.length;
    }


    public function loadGraphics(): Void
    {
    	// Load mappings for all graphics
        textureMap = GfxLoader.loadTextureMap();
        iconPosMap = GfxLoader.loadIconPositionsMap();

        // [0] Current Conditions
        GfxLoader.loadCurrentConditions(this.screens);
        // [1] Latest Observations
        GfxLoader.loadLatestObservations(this.screens);
        // [2] Regional Observations
        GfxLoader.loadRegionalObservations(this.screens);
        // [3,4,5] Local (36-Hour) Forecast
        GfxLoader.loadLocalForecast(this.screens);
        // [6] Regional Forecast
        GfxLoader.loadRegionalForecast(this.screens);
        // [7] Extended Forecast
        GfxLoader.loadExtendedForecast(this.screens);
        // [8] Almanac
        GfxLoader.loadAlmanac(this.screens);

        this.LDL = new GfxLDL(" ");
        this.clock = new GfxClock();

        if (showLogo)
        {
        	untyped __cpp__('
            logo = Sprite(textureMap["Logo"]);
            logo.setPosition(Vector2f(45.f, 24.f));');
        }
    }


    public function getNewData(): Void
    {
        DataProc.fetchNewData();
        var valid = DataProc.runValidator();
        if (valid != 0)
        {
            trace("NB! Validator value: ", valid);
            // Run corrector / handle somehow
        }

        DataProc.createMapRegion(1780, 430);
        
        this.data = DataProc.readyFormatLatestData();
        this.cityROXValues = ["160", "530", "350", "490", "340", "90", "320"];
        this.cityROYValues = ["140", "120", "170", "220", "270", "300", "340"];
        this.cityRFXValues = ["160", "530", "350", "490", "340", "90", "320"];
        this.cityRFYValues = ["140", "120", "170", "220", "270", "300", "340"];
    }


    public function loadData(): Void
    {
        // Create MapCity icon vectors
        var roMapCities: Array<MapCity> = [];
        for (i in 0...cityROXValues.length) {
            roMapCities.push(new MapCity(data[4][i], data[5][i], cityROXValues[i], cityROYValues[i],
                                     textureMap["RF"], iconPosMap[data[6][i]]));
        }

        var rfMapCities: Array<MapCity> = [];
        for (i in 0...cityRFXValues.length) {
            rfMapCities.push(new MapCity(data[11][i], data[12][i], cityRFXValues[i], cityRFYValues[i],
                                     textureMap["RF"], iconPosMap[data[13][i]]));
        } 


        // [0] Current Conditions
        screens[0].updateText(data[0]);
        screens[0].setPressureArrow(GfxLoader.buildPressureArrow(data[1][0], "#cdb900", "#0e0e0e"));
        screens[0].loadIcons([
            new AnimIcon(textureMap["CC"], iconPosMap[data[2][0]], 184, 218)
        ]);

        screens[1].updateText(data[3]);

        // [2] Regional Observations
        screens[2].loadMap(textureMap["Map"], 0, 0);
        screens[2].loadCities(roMapCities);

        screens[3].updateText(data[7]);
        screens[4].updateText(data[8]);
        screens[5].updateText(data[9]);

        // [6] Regional Forecast
        screens[6].loadMap(textureMap["Map"], 0, 0);
        screens[6].loadCities(rfMapCities);
        screens[6].updateText(data[10]);

        // [7] Extended Forecast
        screens[7].updateText(data[14]);
        screens[7].loadIcons([
            new AnimIcon(textureMap["EF"], iconPosMap[data[15][0]], 122, 200),
            new AnimIcon(textureMap["EF"], iconPosMap[data[15][1]], 320, 200),
            new AnimIcon(textureMap["EF"], iconPosMap[data[15][2]], 514, 200),
        ]);

        // [8] Almanac
        screens[8].updateText(data[16]);
        screens[8].loadIcons([
            new AnimIcon(textureMap["Moon"], iconPosMap[data[17][0]], 134, 318),
            new AnimIcon(textureMap["Moon"], iconPosMap[data[17][1]], 256, 318),
            new AnimIcon(textureMap["Moon"], iconPosMap[data[17][2]], 378, 318),
            new AnimIcon(textureMap["Moon"], iconPosMap[data[17][3]], 504, 318)
        ]);

        LDLStrings = data[18];
        LDLScrollStr = data[19];
        LDL.setText(LDLStrings[LDLStrIdx]);
    }


    public function loadMusic(): Void
    {
        if (!musicEnabled)
            return;

        // Open folder and load all songs
        for (entry in sys.FileSystem.readDirectory("../music"))
        {
            if (entry.indexOf(".mp3") > 0)
                songsPaths.push(entry);
        }

        if (songsPaths.length == 0)
            return;

        songIdx = songsPaths.length;
        musicPlayer.setVolume(volume);
        changeSong();
        musicStarted = true;
    }


    public function changeSong(): Void
    {
        songIdx++;
        if (songIdx >= songsPaths.length)
        {
            // Shuffle
            // unsigned seed = std.chrono.system_clock.now().time_since_epoch().count();
            // std.shuffle(songsPaths.begin(), songsPaths.end(),std.mt19937(seed));
            songIdx = 0;
        }

        if (!musicPlayer.openFromFile(songsPaths[songIdx]))
            return;

        musicPlayer.play();
    }


    public function runLoop(): Void
    {
    	while (window.isOpen())
        {
            // EVENTS
            untyped __cpp__('
            var event: Event;
            while (window.pollEvent(event))
            {
                if (event.type == Event.Closed)
                    window.close();

                if (event.type == Event.KeyPressed)
                {
                    switch(event.key.code)
                    {
                        case Keyboard.Escape:
                        case Keyboard.Q:
                        case Keyboard.Space:
                            window.close(); 
                            break;
                        case Keyboard.P:
                            nextScreen();
                            break;
                        case Keyboard.O:
                            prevScreen();
                            break;
                        case Keyboard.S:
                            changeSong();
                            break;
                        default:
                            break;
                    }
                }
            }');


            // Scene change timer
            if (sceneTimer.getElapsedTime().asSeconds() >= sceneTime)
            {
                nextScreen();
                sceneTimer.restart();
            }

            // Update LDL text string-by-string in display mode
            if (!LDL.isUsingScroll() && LDLTimer.getElapsedTime().asSeconds() >= LDLTime)
            {
                LDLStrIdx++;
                if (LDLStrIdx >= LDLStrings.length)
                {
                    LDL.displays++;
                    LDLStrIdx = 0;
                }
                LDL.setText(LDLStrings[LDLStrIdx]);
                LDLTimer.restart();
            }

            // Switch between displaying and scrolling LDL text
            if (!LDL.isUsingScroll() && LDL.displays >= dispLDLTimes)
            {
                LDL.useScroll(true);
                LDL.setText(LDLScrollStr[0]);
            }
            if (LDL.isUsingScroll() && LDL.scrolls >= scrLDLTimes)
            {
                LDL.useScroll(false);
                LDLStrIdx = 0;
                LDL.setText(LDLStrings[LDLStrIdx]);
                LDLTimer.restart();
            }


            // Clear window
            untyped __cpp__('window.clear(Color(28,10,87));');

            // Advance through icon animation
            iconFrameCounter++;
            if (iconFrameCounter >= FPS / ANIM_FRAMES)
            {
                iconFrame = (iconFrame + 1) % ANIM_FRAMES;
                screens[scrIdx].switchIconFrames(iconFrame);
                iconFrameCounter = 0;
            }

            // Render current scene
            screens[scrIdx].renderTo(window);

            // Render time & date
            clock.update();
            clock.renderTo(window);

            // Render LDL
            LDL.renderTo(window);

            // Render the logo (if enabled)
            if (showLogo)
                window.draw(logo);

            // Display window
            window.display();


            // Check if time to change song
            if (musicEnabled && musicStarted) {
            	untyped __cpp__('
            		if (musicPlayer.getStatus() == Music.Status.Stopped) {
            			changeSong();
            		}');
            }
        }
    }

}
