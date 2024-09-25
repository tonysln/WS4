

class AnimIcon {

	private var w: Int;
	private var h: Int;
	private var yPos: Int;
    private var sizeVec: Dynamic;
    private var frame: Dynamic;
    private var icon: Dynamic;


	public function new(texture: Dynamic, posVec: Array<Int>, x: Float, y: Float) 
	{
		w = posVec[0];
        h = posVec[2];
        yPos = posVec[1];
        untyped __cpp__('
        sizeVec = Vector2i(w, h);
        frame = IntRect(Vector2i(0, posVec[1]), sizeVec);
        icon = Sprite(texture);
        icon.setTextureRect(frame);
        icon.setOrigin(Vector2f(icon.getGlobalBounds().width/2, icon.getGlobalBounds().height/2));
        icon.setPosition(Vector2f(x, y));
        ');
	}


	public function update(): Void
    {

    }


    public function switchFrame(iconFrame: Int): Void
    {
        untyped __cpp__('frame = IntRect(Vector2i(w * iconFrame, yPos), sizeVec);');
        icon.setTextureRect(frame);
    }


    public function renderTo(window: Dynamic): Void
    {
        window.draw(icon);
    }


}
