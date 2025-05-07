package states;

import flixel.FlxState;
import flixel.group.FlxSpriteGroup;


class CurrentConditionsState extends BaseState
{
	var boxes: FlxSpriteGroup;


	override public function create()
	{
		super.create();

		boxes = new FlxSpriteGroup();

		// Background gradient
        boxes.add(buildQuadGradient(0, 90, 640, 308, "#2e1251", "#c05d02"));
        // Center blue panel
        boxes.add(buildQuadRect(52, 90, 531, 308, "#2652b2"));
        boxes.add(buildQuadRect(55, 94, 527, 302, "#254ba3"));
        boxes.add(buildQuadRect(57, 96, 523, 298, "#254698"));
        boxes.add(buildQuadRect(59, 98, 519, 294, "#24408c"));
        boxes.add(buildQuadRect(61, 100, 515, 290, "#233a80"));
        boxes.add(buildQuadRect(63, 102, 511, 286, "#223474"));
        boxes.add(buildQuadRect(65, 104, 507, 282, "#222f69"));
        boxes.add(buildQuadRect(66, 105, 506, 281, "#212b60"));
        boxes.add(buildQuadRect(67, 106, 505, 280, "#21285a"));
        // Top bar
        boxes.add(buildQuadPolygon(0, 29, 499, 29, 494, 37, 0, 37, "#c35b00"));
        boxes.add(buildQuadPolygon(0, 37, 494, 37, 489, 45, 0, 45, "#b25200"));
        boxes.add(buildQuadPolygon(0, 45, 489, 45, 483, 54, 0, 54, "#9d4b13"));
        boxes.add(buildQuadPolygon(0, 54, 483, 54, 478, 61, 0, 61, "#8e421a"));
        boxes.add(buildQuadPolygon(0, 61, 478, 61, 471, 71, 0, 71, "#7b3824"));
        boxes.add(buildQuadPolygon(0, 71, 471, 71, 467, 77, 0, 77, "#692e2e"));
        boxes.add(buildQuadPolygon(0, 77, 467, 77, 461, 85, 0, 85, "#592a3e"));
        boxes.add(buildQuadPolygon(0, 85, 461, 85, 457, 90, 0, 90, "#472240"));

        // LDL
        boxes.add(buildQuadRect(0, 399, 640, 81, "#141414"));
        boxes.add(buildQuadRect(0, 400, 640, 80, "#afafaf"));
        boxes.add(buildQuadRect(0, 402, 640, 78, "#233270"));

        add(boxes);
	}

	override public function update(elapsed: Float)
	{
		super.update(elapsed);
	}
}
