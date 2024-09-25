
class TextLabel {


	private var label: Dynamic;
    private var shadowVec: Array<Dynamic>;

    // 0 - None, 1 - A bit larger than outline, 2.. 3..
    private var shadowLevel: Int = 1;
    private var scaleFactor: Float = 0.67;
    private var dir: Int = 0;


    public function new(text: String, fontName: String, colorName: String, charSize: Int, shLevel: Int, spacing: Float, x: Int, y: Int, dir: Int)
    {
    	untyped __cpp__('
        label = Text(toUtf8String(text), fontMap[fontName], charSize * scaleFactor);
        label.setFillColor(GfxLoader.colorMap[colorName]);
        label.setPosition(Vector2f(x, y));
        label.setOutlineColor(GfxLoader.colorMap["#0e0e0e"]);
        label.setOutlineThickness(1);
        label.setLetterSpacing(spacing);
        label.setScale(new Vector2f(1.5, 1.5));
        ');

        // Set origin based on dir (0 = L, 1 = C, 2 = R)
        this.dir = dir;
        alignLeft(label, 0);
        if (dir > 1)
            alignRight(label, 0);
        else if (dir > 0)
            alignCenter(label, 0);


        shadowLevel = shLevel;
        for (i in 0...shadowLevel)
        {
        	var shadow = null;
        	untyped __cpp__('
            shadow = Text(toUtf8String(text), fontMap[fontName], charSize * scaleFactor);
            shadow.setFillColor(GfxLoader.colorMap["#0e0e0e"]);
            shadow.setPosition(Vector2f(x + shadowLevel, y + shadowLevel));
            shadow.setOutlineColor(GfxLoader.colorMap["#0e0e0e"]);
            shadow.setOutlineThickness(0);
            shadow.setLetterSpacing(spacing);
            shadow.setScale(new Vector2f(1.5, 1.5));
            shadow.setOrigin(label.getOrigin());
            ');

            alignLeft(shadow, i-shadowLevel+2);
            if (dir > 1)
                alignRight(shadow, shadowLevel);
            else if (dir > 0)
                alignCenter(shadow, shadowLevel);

            shadowVec.push(shadow);
        }
    }

    public function alignRight(lbl: Dynamic, offset: Int): Void
    {
    	var orig = null;
        untyped __cpp__('orig = Vector2f(lbl.getLocalBounds().width + offset, 0);');
        lbl.setOrigin(orig);
    }

    public function alignLeft(lbl: Dynamic, offset: Int): Void
    {
    	var orig = null;
        untyped __cpp__('orig = Vector2f(0 + offset, 0);');
        lbl.setOrigin(orig);
    }

    public function alignCenter(lbl: Dynamic, offset: Int): Void
    {
    	var orig = null;
        untyped __cpp__('orig = Vector2f(lbl.getLocalBounds().width / 2 + offset, 0);');
        lbl.setOrigin(orig);
    }


    public function setPos(x: Float, y: Float): Void
    {
        untyped __cpp__('label.setPosition(Vector2f(x, y));');
        for (i in 0...shadowLevel)
        {
        	untyped __cpp__('
            shadowVec[i].setPosition(Vector2f(x + shadowLevel, y + shadowLevel));
            ');
        }
    }


    public function updateText(text: String): Void
    {
        label.setString(toUtf8String(text));

        alignLeft(label, 0);
        if (dir > 1)
            alignRight(label, 0);
        else if (dir > 0)
            alignCenter(label, 0);

        var i = 0;
        for (shadow in shadowVec)
        {
            shadow.setString(toUtf8String(text));

            alignLeft(shadow, i-shadowLevel+2);
            if (dir > 1)
                alignRight(shadow, shadowLevel);
            else if (dir > 0)
                alignCenter(shadow, shadowLevel);

            i++;
        }
    }


    public function updateTextInPlace(text: String): Void
    {
        label.setString(toUtf8String(text));

        for (shadow in shadowVec)
            shadow.setString(toUtf8String(text));
    }


    private function toUtf8String(text: String): Dynamic
    {
        return untyped __cpp__('String.fromUtf8(text.begin(), text.end());');
    }


    public function getWidth(): Float
    {
        return label.getGlobalBounds().width;
    }

    public function getHeight(): Float
    {
        return label.getGlobalBounds().height;
    }


    public function renderTo(window: Dynamic): Void
    {
        for (sObj in shadowVec)
            window.draw(sObj);

        window.draw(label);
    }

}