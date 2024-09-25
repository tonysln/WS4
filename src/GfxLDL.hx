
import GfxLoader;
import TextLabel;

class GfxLDL {

	private var vertexObjs: Array<Array<Dynamic>>;
    private var textLabel: TextLabel;
    private var scrollMode: Bool = false;
    private var wordBuf: Array<String>;
    private var bufStrFull: String;
    private var bufTimer: Dynamic;
    private var bufIdx: Int = -1;
    private var scrSpeed: Int = 3;
    private var x: Int = 64;
    private var y: Int = 399;
    private var offsetPxRight: Int = 70;
    private var offsetPxLeft: Int = 90;
    private var lagTime: Float = 17.0;

  	public var scrolls: Int = 0;
    public var displays: Int = 0;


    public function new(text: String = "")
    {
    	vertexObjs = 
        [
            GfxLoader.buildQuad(0, 399, 640, 81, "#141414"),
            GfxLoader.buildQuad(0, 400, 640, 80, "#afafaf"),
            GfxLoader.buildQuad(0, 402, 640, 78, "#233270")
        ];

        textLabel = new TextLabel("", "Star4000", "#d7d7d7", 30, 1, 1.0, x, y, 0);
        setText(text);
    }


    public function setText(text: String): Void
    {
        if (scrollMode)
        {
            textLabel.updateText(text);
            return;
        }

        wordBuf = [];
        bufStrFull = "";
        var seg: String;
		var wordBuf: Array<String> = [];
		var lnStream: Array<String> = text.split(" ");

		for (seg in lnStream) {
		    wordBuf.push(seg);
}

        bufIdx = 0;
        bufStrFull = wordBuf[bufIdx];
        textLabel.updateText(bufStrFull);
        bufTimer.restart();
    }


    public function useScroll(scroll: Bool): Void
    {
        scrollMode = scroll;
        if (scrollMode)
        {
            scrolls = 0;
            textLabel.updateText("");
            x = 640 + offsetPxRight;
            textLabel.setPos(x, y);
        }
        else
        {
            displays = 0;
            bufIdx = -1;
            x = 64;
            textLabel.setPos(x, y);
        }
    }


    public function isUsingScroll(): Bool
    {
        return scrollMode;
    }


    public function renderTo(window: Dynamic): Void
    {
        // Drawing vertex objects
        for (vObj in vertexObjs) {
            untyped __cpp__('window.draw(vObj, 4, PrimitiveType.TriangleStrip);');
        }

        // Animating text
        if (scrollMode)
        {
            x -= scrSpeed;
            textLabel.setPos(x, y);

            if (x + textLabel.getWidth() <= -offsetPxLeft)
            {
                x = 640 + offsetPxRight;
                scrolls++;
            }
        }
        else if (wordBuf.length != 0 && bufIdx > -1 && bufIdx < wordBuf.length-1)
        {
            if (bufTimer.getElapsedTime().asMilliseconds() > lagTime)
            {
                bufIdx++;
                bufStrFull += " ";
                bufStrFull += wordBuf[bufIdx];
                textLabel.updateText(bufStrFull);
                bufTimer.restart();
            }
        }

        // Drawing text
        textLabel.renderTo(window);
    }

}
