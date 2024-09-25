
class MapCity {

	private var icon: AnimIcon;
    private var name: TextLabel;
    private var temp: TextLabel;
    private var x: Int = 0;
    private var y: Int = 0;


    public function new(nameText: String, tempText: String, xs: String, ys: String, icoTxt: Dynamic, icoPos: Array<Int>)
    {
        x = Std.parseInt(xs);
        y = Std.parseInt(ys);

        name = new TextLabel(nameText, "Star4000", "#d7d7d7", 30, 2, 0.6, x, y, 1);
        temp = new TextLabel(tempText, "Star4000-Large-Compressed", "#cdb900", 34, 2, 1.0, x, y, 1);

        name.setPos(x, y - name.getHeight());
        temp.setPos(x - temp.getWidth(), y + name.getHeight() / 2 - 4);
        icon = new AnimIcon(icoTxt, icoPos, x + temp.getWidth() / 2, y + name.getHeight());
    }


    public function updateTemp(newTemp: String): Void {
        temp.updateText(newTemp);
    }


    public function updateIcon(): Void
    {

    }


    public function switchFrames(iconFrame: Int): Void
    {
        icon.switchFrame(iconFrame);
    }


    public function renderTo(window: Dynamic): Void
    {
        icon.renderTo(window);
        temp.renderTo(window);
        name.renderTo(window);
    }

}
