
import WS4;


@:buildXml("
<xml>
    <include name='SFML/Graphics.hpp'/>
    <include name='SFML/Window.hpp'/>
    <link name='sfml-graphics'/>
    <link name='sfml-window'/>
    <link name='sfml-system'/>
</xml>")
class Main {

    public static function main(): Void {
        var ws4 = new WS4();
 
        ws4.getNewData();
        ws4.loadGraphics();
        ws4.loadData();
        ws4.loadMusic();

        ws4.runLoop();
    }
}

