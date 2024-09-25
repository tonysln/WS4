
import haxe.Json;


class GfxLoader {

    // Create vectors of vertices, textlabels and animicons for all screens.
    // Vectors fed into GfxScreen classes and saved into main screens vector in GfxManager.

    public static var fontMap:  Map<String, Dynamic>  = loadFontMap();
    public static var colorMap: Map<String, Dynamic>  = loadColorMap();


    public static function buildQuad(x: Int, y: Int, w: Int, h: Int, col1: Dynamic, ?col2: Dynamic): Array<Dynamic>
    {
    	// Construct an Array of Vertices at (x,y) with size (w,h) and gradient of given colors

    	if (col2 == null) {
    		var col2 = col1;
    	}

        var quad = [];

        untyped __cpp__(' 
        quad = [
            Vertex(Vector2f(x+w, y), col1),
            Vertex(Vector2f(x, y), col1),
            Vertex(Vector2f(x+w, y+h), col2),
            Vertex(Vector2f(x, y+h), col2)
        ];');
        return quad;
    }

    public static function buildQuad2(x1: Int, y1: Int, x2: Int, y2: Int, 
                                            x3: Int, y3: Int, x4: Int, y4: Int, col: Dynamic): Array<Dynamic>
    {
    	// Construct an Array of Vertices at four given (x,y) points and given color
        var quad = [];
        untyped __cpp__('
        quad = [
            Vertex(Vector2f(x4, y4), col),
            Vertex(Vector2f(x1, y1), col),
            Vertex(Vector2f(x3, y3), col),
            Vertex(Vector2f(x2, y2), col)
        ];');
        return quad;
    }


    public static function buildPressureArrow(dir: String, col: String, shadow: String): Array<Array<Dynamic>>
    {
    	// Hard-coded, might want to specify origin (x,y) in arguments

        var arrow = [];

        if (dir == "up")
        {
            arrow =
            [
                buildQuad2(547-1, 317-2, 555+1, 307-2, 563+3, 317+1, 547-2, 316+1, colorMap[shadow]),
                buildQuad2(553-1, 315-1, 557+3, 315+2, 557+3, 330+2, 553-1, 330+2, colorMap[shadow]),
                buildQuad2(547, 317, 555, 307, 563, 317, 547, 316, colorMap[col]),
                buildQuad2(553, 315, 557, 315, 557, 330, 553, 330, colorMap[col])
            ];
        }
        else if (dir == "down")
        {
            arrow =
            [
                buildQuad2(547-1, 320-2, 555+2, 331+2, 563+3, 320+1, 547-2, 320+1, colorMap[shadow]),
                buildQuad2(553-1, 307-1, 557+3, 307+2, 557+3, 320+2, 553-1, 320+2, colorMap[shadow]),
                buildQuad2(547, 320, 555, 331, 563, 320, 547, 320, colorMap[col]),
                buildQuad2(553, 307, 557, 307, 557, 320, 553, 320, colorMap[col])
            ];
        }

        return arrow;
    }



    public static function loadFontMap(): Map<String, Dynamic>
    {
        var fM: Map<String, Dynamic> = [];

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


    public static function loadColorMap(): Map<String, Dynamic>
    {

    	// var cM = Json.parse(...); 
    	// TODO for and re-create Color objects

    	var cM: Map<String, Dynamic> = [];

    	untyped __cpp__('
        cM =
        [
            "#0e0e0e" => Color(14,14,14),
            "#141414" => Color(20,20,20),
            "#d7d7d7" => Color(215,215,215),
            "#afafaf" => Color(175,175,175),
            "#3d3d3d" => Color(61,61,61),
            "#1c0a57" => Color(28,10,87),
            "#233270" => Color(35,50,112),
            "#2e1251" => Color(46,18,81),
            "#c05d02" => Color(192,93,2),
            "#2652b2" => Color(38,82,178),
            "#254ba3" => Color(37,75,163),
            "#254698" => Color(37,70,152),
            "#24408c" => Color(36,64,140),
            "#233a80" => Color(35,58,128),
            "#223474" => Color(34,52,116),
            "#222f69" => Color(34,47,105),
            "#212b60" => Color(33,43,96),
            "#21285a" => Color(33,40,90),
            "#c35b00" => Color(195,91,0),
            "#b25200" => Color(178,82,0),
            "#9d4b13" => Color(157,75,19),
            "#8e421a" => Color(142,66,26),
            "#7b3824" => Color(123,56,36),
            "#692e2e" => Color(105,46,46),
            "#592a3e" => Color(89,42,62),
            "#472240" => Color(71,34,64),
            "#cdb900" => Color(205,185,0),
            "#7d3c28" => Color(125,60,40),
            "#828af5" => Color(130,138,245),
            "#8385cb" => Color(131,133,203),

            "#565bca" => Color(86,91,202),
            "#424eca" => Color(66,78,202),
            "#2c42ca" => Color(44,66,202),
            "#2539ca" => Color(37,57,202),
            "#0931ca" => Color(9,49,202),
            "#0028cb" => Color(0,40,203),
            "#0024cb" => Color(0,36,203),
            "#0022cb" => Color(0,34,203),

            "#f0dc0a" => Color(240,220,10),
            "#f09600" => Color(240,150,0),
            "#fa6405" => Color(250,100,5),
            "#f52805" => Color(245,40,5)
        ];
        ');

        return cM;
    }


    public static function loadTextureMap(): Map<String, Dynamic>
    {
        var tM: Map<String, Dynamic> = [];
        
        if (!tM["Moon"].loadFromFile("../graphics/icons/Moon-Phases.png"))
            return tM;
        tM["Moon"].setSmooth(false);
        if (!tM["CC"].loadFromFile("../graphics/icons/Current-Conditions.png"))
            return tM;
        tM["CC"].setSmooth(false);
        if (!tM["EF"].loadFromFile("../graphics/icons/Extended-Forecast.png"))
            return tM;
        tM["EF"].setSmooth(false);
        if (!tM["RF"].loadFromFile("../graphics/icons/Regional-Maps.png"))
            return tM;
        tM["RF"].setSmooth(false);
        if (!tM["Map"].loadFromFile("../data/map.png"))
            return tM;
        tM["Map"].setSmooth(false);
        if (!tM["Logo"].loadFromFile("../graphics/logo.png"))
            return tM;
        tM["Logo"].setSmooth(false);

        return tM;
    }


    public static function loadIconPositionsMap(): Map<String, Array<Int>>
    {

    	// var cM = Json.parse(...); 
    	// TODO for and re-create arrays?

        var iPM =
        [
                "CC_Blowing-Snow" => [138, 0, 99],
                "CC_Clear" => [100, 99, 65],
                "CC_Cloudy" => [118, 164, 83],
                "CC_Freezing-Rain-Sleet" => [126, 247, 113],
                "CC_Freezing-Rain" => [124, 360, 113],
                "CC_Heavy-Snow" => [136, 473, 103],
                "CC_Ice-Snow" => [146, 577, 117],
                "CC_Light-Snow" => [108, 695, 91],
                "CC_Mostly-Clear" => [94, 787, 69],
                "CC_Mostly-Cloudy" => [142, 856, 85],
                "CC_Partly-Clear" => [138, 940, 69],
                "CC_Partly-Cloudy" => [130, 1010, 85],
                "CC_Rain-Snow" => [138, 1094, 117],
                "CC_Rain" => [124, 1212, 113],
                "CC_Shower" => [124, 1326, 101],
                "CC_Sleet" => [70, 1427, 91],
                "CC_Snow-Sleet" => [108, 1519, 91],
                "CC_Sunny" => [112, 1611, 107],
                "CC_Thunder" => [148, 1718, 123],
                "CC_ThunderSnow" => [142, 1841, 93],
                "CC_Thunderstorm" => [142, 1935, 117],
                "CC_Wintry-Mix" => [134, 2053, 105],
                "EF_Cloudy" => [96, 0, 69],
                "EF_Fog" => [112, 70, 91],
                "EF_Freezing-Rain" => [100, 161, 91],
                "EF_Heavy-Snow" => [114, 253, 85],
                "EF_Isolated-Tstorms" => [116, 339, 103],
                "EF_Light-Snow" => [86, 443, 75],
                "EF_Mostly-Cloudy" => [122, 518, 69],
                "EF_Partly-Cloudy" => [106, 588, 69],
                "EF_Rain-Snow" => [116, 657, 97],
                "EF_Rain" => [100, 755, 89],
                "EF_Scattered-Showers" => [132, 845, 97],
                "EF_Scattered-Snow-Showers" => [112, 943, 71],
                "EF_Scattered-Tstorms" => [130, 1015, 101],
                "EF_Showers" => [100, 1117, 81],
                "EF_Snow-to-Rain" => [116, 1199, 91],
                "EF_Sunny" => [90, 1290, 87],
                "EF_Thunderstorms" => [118, 1378, 97],
                "EF_Windy" => [88, 1475, 63],
                "EF_Wintry-Mix" => [106, 1538, 83],
                "RF_AM-Snow" => [52, 0, 39],
                "RF_Blowing-Snow" => [56, 40, 49],
                "RF_Clear" => [36, 89, 37],
                "RF_Cloudy-Wind" => [66, 126, 57],
                "RF_Cloudy" => [52, 184,35],
                "RF_Fog" => [48, 220, 45],
                "RF_Freezing-Rain-Sleet" => [60, 266, 61],
                "RF_Freezing-Rain-Snow" => [50, 328, 45],
                "RF_Freezing-Rain" => [50, 374, 35],
                "RF_Heavy-Snow" => [48, 409, 47],
                "RF_Light-Snow" => [44, 457, 45],
                "RF_Mostly-Clear" => [46, 502, 37],
                "RF_Mostly-Cloudy" => [60, 540, 55],
                "RF_Partly-Clear" => [66, 596, 37],
                "RF_Partly-Cloudy" => [60, 633, 55],
                "RF_Rain-Sleet" => [62, 689, 63],
                "RF_Rain-Snow" => [46, 753, 53],
                "RF_Rain-Wind" => [64, 807, 55],
                "RF_Rain" => [44, 863, 39],
                "RF_Scattered-Showers" => [60, 902, 55],
                "RF_Scattered-Snow-Showers" => [60, 958, 71],
                "RF_Scattered-Tstorms" => [64, 1030, 57],
                "RF_Shower" => [42, 1088, 30],
                "RF_Sleet" => [46, 1118, 43],
                "RF_Snow-Sleet" => [48, 1161, 47],
                "RF_Sunny-Wind" => [66, 1209, 55],
                "RF_Sunny" => [60, 1265, 55],
                "RF_Thunder" => [62, 1321, 63],
                "RF_ThunderSnow" => [62, 1385, 59],
                "RF_Thunderstorm" => [58, 1445, 59],
                "RF_Wind" => [56, 1504, 45],
                "RF_Wintry-Mix" => [56, 1544, 51],
                "M_New" => [100, 0, 93],
                "M_First" => [100, 94, 93],
                "M_Full" => [100, 188, 93],
                "M_Last" => [100, 282, 93],
        ];

        return iPM;
    }


    public static function loadCurrentConditions(vec: Array<GfxScreen>): Void
    {
        vec.push
        (
            new GfxScreen(
                [
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, "#2652b2"),
                    buildQuad(55, 94, 527, 302, "#254ba3"),
                    buildQuad(57, 96, 523, 298, "#254698"),
                    buildQuad(59, 98, 519, 294, "#24408c"),
                    buildQuad(61, 100, 515, 290, "#233a80"),
                    buildQuad(63, 102, 511, 286, "#223474"),
                    buildQuad(65, 104, 507, 282, "#222f69"),
                    buildQuad(66, 105, 506, 281, "#212b60"),
                    buildQuad(67, 106, 505, 280, "#21285a"),
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Current", "Star4000", "#cdb900", 34, 3, 0.9, 157, 21, 0),
                    new TextLabel("Conditions", "Star4000", "#cdb900", 34, 3, 0.9, 157, 50, 0),
                    new TextLabel("Humidity:", "Star4000", "#d7d7d7", 33, 1, 0.5, 338, 131, 0),
                    new TextLabel("Dewpoint:", "Star4000", "#d7d7d7", 33, 1, 0.5, 338, 171, 0),
                    new TextLabel("Ceiling:", "Star4000", "#d7d7d7", 33, 1, 0.5, 338, 215, 0),
                    new TextLabel("Visibility:", "Star4000", "#d7d7d7", 33, 1, 0.4, 338, 257, 0),
                    new TextLabel("Pressure:", "Star4000", "#d7d7d7", 33, 1, 0.5, 338, 298, 0),
                ],
                [
                    new TextLabel("", "Star4000", "#cdb900", 34, 2, 0.55, 320, 92, 0),
                    new TextLabel("", "Star4000-Large", "#d7d7d7", 35, 1, 1.0, 200, 100, 1),
                    new TextLabel("", "Star4000-Extended", "#d7d7d7", 34, 1, 0.8, 185, 128, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.4, 568, 131, 2),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.4, 568, 171, 2),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.4, 568, 257, 2),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.4, 568, 215, 2),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.4, 542, 298, 2),
                    new TextLabel("", "Star4000-Extended", "#d7d7d7", 32, 1, 1.0, 75, 298, 0),
                    new TextLabel("", "Star4000-Extended", "#d7d7d7", 33, 1, 1.0, 75, 336, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.5, 338, 336, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.4, 568, 336, 2),
                ]
            )
        );
    }

    public static function loadLatestObservations(vec: Array<GfxScreen>): Void
    {
        vec.push
        (
            new GfxScreen (
                [
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, "#2652b2"),
                    buildQuad(55, 94, 527, 302, "#254ba3"),
                    buildQuad(57, 96, 523, 298, "#254698"),
                    buildQuad(59, 98, 519, 294, "#24408c"),
                    buildQuad(61, 100, 515, 290, "#233a80"),
                    buildQuad(63, 102, 511, 286, "#223474"),
                    buildQuad(65, 104, 507, 282, "#222f69"),
                    buildQuad(66, 105, 506, 281, "#212b60"),
                    buildQuad(67, 106, 505, 280, "#21285a"),
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Latest Observations", "Star4000", "#cdb900", 34, 3, 0.4, 157, 35, 0),
                    new TextLabel("F°", "Star4000-Small", "#d7d7d7", 30, 0, 1.0, 306, 78, 0),
                    new TextLabel("WEATHER", "Star4000-Small", "#d7d7d7", 30, 0, 1.0, 365, 78, 0),
                    new TextLabel("WIND", "Star4000-Small", "#d7d7d7", 30, 0, 1.0, 505, 78, 0),
                ],
                [
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 72, 110, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 305, 110, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 365, 110, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 505, 110, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 72, 150, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 305, 150, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 365, 150, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 505, 150, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 72, 190, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 305, 190, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 365, 190, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 505, 190, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 72, 230, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 305, 230, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 365, 230, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 505, 230, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 72, 270, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 305, 270, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 365, 270, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 505, 270, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 72, 310, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 305, 310, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 365, 310, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 505, 310, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 72, 350, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 305, 350, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 365, 350, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 0.8, 505, 350, 0),
                ]
           	)
        );
    }


    public static function loadRegionalObservations(vec: Array<GfxScreen>): Void
    {
        vec.push
        (
            new GfxScreen (
                [
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Regional", "Star4000", "#cdb900", 34, 3, 0.6, 157, 21, 0),
                    new TextLabel("Observations", "Star4000", "#cdb900", 34, 3, 0.6, 157, 50, 0),
                ]
            )
        );
    }


    public static function loadLocalForecast(vec: Array<GfxScreen>): Void
    {
        // Screen 1/3
        vec.push
        (
            new GfxScreen (
                [
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, "#2652b2"),
                    buildQuad(55, 94, 527, 302, "#254ba3"),
                    buildQuad(57, 96, 523, 298, "#254698"),
                    buildQuad(59, 98, 519, 294, "#24408c"),
                    buildQuad(61, 100, 515, 290, "#233a80"),
                    buildQuad(63, 102, 511, 286, "#223474"),
                    buildQuad(65, 104, 507, 282, "#222f69"),
                    buildQuad(66, 105, 506, 281, "#212b60"),
                    buildQuad(67, 106, 505, 280, "#21285a"),
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Local Forecast", "Star4000", "#cdb900", 34, 3, 0.6, 157, 35, 0),
                ],
                [
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 105, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 145, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 185, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 225, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 265, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 305, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 345, 0),
                ]
            )
        );
        // Screen 2/3
        vec.push
        (
            new GfxScreen (
                [
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, "#2652b2"),
                    buildQuad(55, 94, 527, 302, "#254ba3"),
                    buildQuad(57, 96, 523, 298, "#254698"),
                    buildQuad(59, 98, 519, 294, "#24408c"),
                    buildQuad(61, 100, 515, 290, "#233a80"),
                    buildQuad(63, 102, 511, 286, "#223474"),
                    buildQuad(65, 104, 507, 282, "#222f69"),
                    buildQuad(66, 105, 506, 281, "#212b60"),
                    buildQuad(67, 106, 505, 280, "#21285a"),
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Local Forecast", "Star4000", "#cdb900", 34, 3, 0.6, 157, 35, 0),
                ],
                [
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 105, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 145, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 185, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 225, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 265, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 305, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 345, 0),
                ]
            )
        );
        // Screen 3/3
        vec.push
        (
            new GfxScreen (
                [
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Center blue panel
                    buildQuad(52, 90, 531, 308, "#2652b2"),
                    buildQuad(55, 94, 527, 302, "#254ba3"),
                    buildQuad(57, 96, 523, 298, "#254698"),
                    buildQuad(59, 98, 519, 294, "#24408c"),
                    buildQuad(61, 100, 515, 290, "#233a80"),
                    buildQuad(63, 102, 511, 286, "#223474"),
                    buildQuad(65, 104, 507, 282, "#222f69"),
                    buildQuad(66, 105, 506, 281, "#212b60"),
                    buildQuad(67, 106, 505, 280, "#21285a"),
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Local Forecast", "Star4000", "#cdb900", 34, 3, 0.6, 157, 35, 0),
                ],
                [
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 105, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 145, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 185, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 225, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 265, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 305, 0),
                    new TextLabel("", "Star4000", "#d7d7d7", 33, 1, 1.0, 70, 345, 0),
                ]
            )
        );
    }


    public static function loadRegionalForecast(vec: Array<GfxScreen>): Void
    {
        vec.push
        (
            new GfxScreen (
                [
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Forecast For", "Star4000", "#cdb900", 34, 3, 0.6, 157, 21, 0),
                ],
                [
                    new TextLabel("", "Star4000", "#cdb900", 34, 3, 0.6, 157, 50, 0),
                ]
            )
        );
    }


    public static function loadExtendedForecast(vec: Array<GfxScreen>): Void
    {
        vec.push
        (
            new GfxScreen (
                [
                    // Background gradient
                    buildQuad(0, 90, 640, 308, colorMap["#2e1251"], colorMap["#c05d02"]),
                    // Left panel
                    buildQuad(37, 100, 175, 296,"#0e0e0e"),
                    buildQuad(40, 103, 169, 290,"#828af5"),
                    buildQuad(44, 106, 161, 284,"#0e0e0e"),
                    buildQuad(46, 108, 157, 32, "#565bca"),
                    buildQuad(46, 140, 157, 35, "#424eca"),
                    buildQuad(46, 175, 157, 36, "#2c42ca"),
                    buildQuad(46, 211, 157, 34, "#2539ca"),
                    buildQuad(46, 245, 157, 34, "#0931ca"),
                    buildQuad(46, 279, 157, 37, "#0028cb"),
                    buildQuad(46, 316, 157, 36, "#0024cb"),
                    buildQuad(46, 352, 157, 36, "#0022cb"),
                    // Center panel
                    buildQuad(231, 100, 175, 296,"#0e0e0e"),
                    buildQuad(234, 103, 169, 290,"#828af5"),
                    buildQuad(238, 106, 161, 284,"#0e0e0e"),
                    buildQuad(240, 108, 157, 32, "#565bca"),
                    buildQuad(240, 140, 157, 35, "#424eca"),
                    buildQuad(240, 175, 157, 36, "#2c42ca"),
                    buildQuad(240, 211, 157, 34, "#2539ca"),
                    buildQuad(240, 245, 157, 34, "#0931ca"),
                    buildQuad(240, 279, 157, 37, "#0028cb"),
                    buildQuad(240, 316, 157, 36, "#0024cb"),
                    buildQuad(240, 352, 157, 36, "#0022cb"),
                    // Right panel
                    buildQuad(426, 100, 175, 296,"#0e0e0e"),
                    buildQuad(429, 103, 169, 290,"#828af5"),
                    buildQuad(433, 106, 161, 284,"#0e0e0e"),
                    buildQuad(435, 108, 157, 32, "#565bca"),
                    buildQuad(435, 140, 157, 35, "#424eca"),
                    buildQuad(435, 175, 157, 36, "#2c42ca"),
                    buildQuad(435, 211, 157, 34, "#2539ca"),
                    buildQuad(435, 245, 157, 34, "#0931ca"),
                    buildQuad(435, 279, 157, 37, "#0028cb"),
                    buildQuad(435, 316, 157, 36, "#0024cb"),
                    buildQuad(435, 352, 157, 36, "#0022cb"),
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Extended Forecast", "Star4000", "#cdb900", 34, 2, 0.5, 157, 50, 0),
                    new TextLabel("Lo", "Star4000", "#8385cb", 33, 1, 0.7, 86, 311, 1),
                    new TextLabel("Hi", "Star4000", "#cdb900", 33, 1, 0.7, 158, 311, 1),
                    new TextLabel("Lo", "Star4000", "#8385cb", 33, 1, 0.7, 284, 311, 1),
                    new TextLabel("Hi", "Star4000", "#cdb900", 33, 1, 0.7, 358, 311, 1),
                    new TextLabel("Lo", "Star4000", "#8385cb", 33, 1, 0.7, 476, 311, 1),
                    new TextLabel("Hi", "Star4000", "#cdb900", 33, 1, 0.7, 554, 311, 1),
                ],
                [
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 0.5, 156, 21, 0),
                    new TextLabel("", "Star4000", "#cdb900", 34, 2, 1.0, 122, 100, 1),
                    new TextLabel("", "Star4000", "#cdb900", 34, 2, 1.0, 320, 100, 1),
                    new TextLabel("", "Star4000", "#cdb900", 34, 2, 1.0, 514, 100, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 1, 1.0, 122, 238, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 1, 1.0, 122, 274, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 1, 1.0, 320, 238, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 1, 1.0, 320, 274, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 1, 1.0, 514, 238, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 1, 1.0, 514, 274, 1),
                    new TextLabel("", "Star4000-Large", "#d7d7d7", 36, 1, 1.0, 86, 350, 1),
                    new TextLabel("", "Star4000-Large", "#d7d7d7", 36, 1, 1.0, 158, 350, 1),
                    new TextLabel("", "Star4000-Large", "#d7d7d7", 36, 1, 1.0, 284, 350, 1),
                    new TextLabel("", "Star4000-Large", "#d7d7d7", 36, 1, 1.0, 358, 350, 1),
                    new TextLabel("", "Star4000-Large", "#d7d7d7", 36, 1, 1.0, 476, 350, 1),
                    new TextLabel("", "Star4000-Large", "#d7d7d7", 36, 1, 1.0, 554, 350, 1),
                ]
            )
        );
    }


    public static function loadAlmanac(vec: Array<GfxScreen>): Void
    {
        vec.push
        (
            new GfxScreen (
                [
                    // Top gradient
                    buildQuad(0, 90, 640, 40, colorMap["#2e1251"], colorMap["#7d3c28"]),
                    buildQuad(0, 130, 640, 62, colorMap["#7d3c28"], colorMap["#c35b00"]),
                    // Gray background
                    buildQuad(0, 192, 640, 206, "#3d3d3d"),
                    // Top bar
                    buildQuad2(0, 29, 499, 29, 494, 37, 0, 37, colorMap["#c35b00"]),
                    buildQuad2(0, 37, 494, 37, 489, 45, 0, 45, colorMap["#b25200"]),
                    buildQuad2(0, 45, 489, 45, 483, 54, 0, 54, colorMap["#9d4b13"]),
                    buildQuad2(0, 54, 483, 54, 478, 61, 0, 61, colorMap["#8e421a"]),
                    buildQuad2(0, 61, 478, 61, 471, 71, 0, 71, colorMap["#7b3824"]),
                    buildQuad2(0, 71, 471, 71, 467, 77, 0, 77, colorMap["#692e2e"]),
                    buildQuad2(0, 77, 467, 77, 461, 85, 0, 85, colorMap["#592a3e"]),
                    buildQuad2(0, 85, 461, 85, 457, 90, 0, 90, colorMap["#472240"]),
                ],
                [
                    new TextLabel("Almanac", "Star4000", "#cdb900", 34, 3, 0.9, 156, 35, 0),
                    new TextLabel("Sunrise:", "Star4000", "#d7d7d7", 34, 2, 1.0, 194, 116, 2),
                    new TextLabel("Sunset:", "Star4000", "#d7d7d7", 34, 2, 1.0, 194, 149, 2),
                    new TextLabel("Moon Data:", "Star4000", "#cdb900", 34, 2, 0.9, 78, 190, 0),
                ],
                [
                    new TextLabel("", "Star4000", "#cdb900", 34, 2, 1.0, 320, 84, 1),
                    new TextLabel("", "Star4000", "#cdb900", 34, 2, 1.0, 500, 84, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 320, 116, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 500, 116, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 320, 149, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 500, 149, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 134, 226, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 256, 226, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 378, 226, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 504, 226, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 134, 356, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 256, 356, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 378, 356, 1),
                    new TextLabel("", "Star4000", "#d7d7d7", 34, 2, 1.0, 504, 356, 1),
                ]
            )
        );
    }

}
