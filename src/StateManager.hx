package;

import flixel.FlxState;
import flixel.FlxSubState;
import flixel.FlxG;
import flixel.util.FlxColor;
import states.CurrentConditionsState;

import lime.system.System;


class StateManager extends FlxState
{
	var states: Array<Class<FlxSubState>> = [CurrentConditionsState];
	var switchInterval: Array<Float> = [15.0];
    var current: Int = 0;
    var timer: Float = 0;


	override public function create()
	{
		super.create();
		openSubState(Type.createInstance(states[current], []));
		this.exists = true;
		this.active = true;
	}

	override public function update(elapsed: Float)
	{
		if (FlxG.keys.anyPressed([ESCAPE, Q])) { System.exit(0); }
		else if (FlxG.keys.justPressed.O){ nextState(); }
		else if (FlxG.keys.justPressed.I){ prevState(); }

		super.update(elapsed);
		timer += elapsed;
        if (timer >= switchInterval[current]) {
            nextState();
        }
	}

	function nextState()
	{
        current = (current + 1) % states.length;
        stateChange();
	}

	function prevState()
	{
        current = (current - 1) % states.length;
        stateChange();
	}

	function stateChange()
	{
		timer = 0;
		closeSubState();
        openSubState(Type.createInstance(states[current], []));
        this.exists = true;
		this.active = true;
	}
}
