package states;

import flixel.FlxSubState;
import flixel.FlxSprite;
import flixel.FlxG;
import flixel.text.FlxText;
import flixel.util.FlxColor;
import flixel.math.FlxPoint;
import flixel.group.FlxSpriteGroup;

using flixel.util.FlxSpriteUtil;
using flixel.util.FlxGradient;


class BaseState extends FlxSubState
{
	override public function create()
	{
		super.create();
		bgColor = FlxColor.fromString("#1c0a57");
	}

	override public function update(elapsed: Float)
	{
		super.update(elapsed);
	}


	function buildQuadRect(x: Float, y: Float, w: Int, h: Int, color: String): FlxSprite
	{
		var box = new FlxSprite(x, y);
		box.makeGraphic(w, h, FlxColor.fromString(color));
		return box;
	}

	function buildQuadGradient(x: Float, y: Float, w: Int, h: Int, color1: String, color2: String): FlxSprite 
	{
		var box = new FlxSprite(x, y);
		box.makeGraphic(w, h, FlxColor.TRANSPARENT);
		var gradient = FlxGradient.overlayGradientOnFlxSprite(box, w, h, [FlxColor.fromString(color1), FlxColor.fromString(color2)], 0, 0, 1, 90, false);
		return gradient;
	}

	function buildQuadPolygon(x1: Float, y1: Float, x2: Float, y2: Float, x3: Float, y3: Float, x4: Float, y4: Float, color: String): FlxSprite
	{
		var box = new FlxSprite();
		box.makeGraphic(FlxG.width, FlxG.height, FlxColor.TRANSPARENT);
		var vertices = new Array<FlxPoint>();
		vertices[0] = new FlxPoint(x1, y1);
		vertices[1] = new FlxPoint(x2, y2);
		vertices[2] = new FlxPoint(x3, y3);
		vertices[3] = new FlxPoint(x4, y4);
		
		var lineStyle: LineStyle = {color: FlxColor.fromString(color), thickness: 1};
		var drawStyle: DrawStyle = {smoothing: false};
		box.drawPolygon(vertices, FlxColor.fromString(color), lineStyle, drawStyle);
		return box;
	}
}
