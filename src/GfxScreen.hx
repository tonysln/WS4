
class GfxScreen {

	private var staticBgVertices: Array<Array<Dynamic>>;
    private var pressureArrow: Array<Array<Dynamic>>;
    private var dynamicText: Array<TextLabel>;
    private var staticText: Array<TextLabel>;
    private var icons: Array<AnimIcon>;
    private var cities: Array<MapCity>;
    private var map: Dynamic;
    private var mapScr: Bool = false;


    public function new(sbv: Array<Array<Dynamic>>, st: Array<TextLabel>, ?dt: Array<TextLabel>)
    {
    	staticBgVertices = sbv.copy();
    	staticText = st.copy();

    	if (dt != null) {
        	dynamicText = dt.copy();
    	}
    }


    public function updateText(newText: Array<String>): Void
    {
        var i = 0;
        for (textStr in newText)
            dynamicText[i++].updateText(textStr);
    }


    public function updateIcons(): Void
    {

    }


    public function loadMap(texture: Dynamic, xPos: Int, yPos: Int): Void
    {
        untyped __cpp__('
        map = Sprite(texture);
        map.setTextureRect(IntRect(Vector2i(xPos, yPos), Vector2i(640, 308)));
        map.setPosition(Vector2f(0, 90));
        ');
        mapScr = true;
    }


    public function loadIcons(iconVec: Array<AnimIcon>): Void
    {
        icons = iconVec.copy();
    }


    public function loadCities(cityVec: Array<MapCity>): Void
    {
        cities = cityVec.copy();
    }


    public function switchIconFrames(iconFrame: Int): Void
    {
        for (iObj in icons)
            iObj.switchFrame(iconFrame);

        for (cObj in cities)
            cObj.switchFrames(iconFrame);
    }


    public function setPressureArrow(presArrw: Array<Array<Dynamic>>): Void
    {
        pressureArrow = presArrw.copy();
    }


    public function renderTo(window: Dynamic): Void
    {
        for (vObj in staticBgVertices) {
            untyped __cpp__('window.draw(vObj, 4, PrimitiveType.TriangleStrip);');
        }

        if (pressureArrow.length != 0) {
            for (aObj in pressureArrow) {
                untyped __cpp__('window.draw(aObj, 4, PrimitiveType.TriangleStrip);');
            }
        }

        if (mapScr)
            window.draw(map);

        for (cObj in cities)
            cObj.renderTo(window);

        for (iObj in icons)
            iObj.renderTo(window);

        for (tObj in staticText)
            tObj.renderTo(window);

        for (tObj in dynamicText)
            tObj.renderTo(window);
    }

}
