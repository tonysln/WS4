package;

import flixel.FlxGame;
import openfl.display.Sprite;


class Main extends Sprite
{
	public function new()
	{
		super();
		addChild(new FlxGame(0, 0, StateManager, 30, 30, true));
	}
}
