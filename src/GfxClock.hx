
// import Date;


class GfxClock {

    private var timeStr: String;
    private var timeAPStr: String;
    private var dateStr: String;
    private var time: TextLabel;
    private var ampm: TextLabel;
    private var date: TextLabel;


    public function new() 
    {
    	update();
        time = new TextLabel(timeStr, "Star4000-Small", "#d7d7d7", 32, 1,  0.9, 412, 33, 0);
        ampm = new TextLabel(timeAPStr, "Star4000-Small", "#d7d7d7", 32, 1,  0.9, 575, 33, 2);
        date = new TextLabel(dateStr, "Star4000-Small", "#d7d7d7", 32, 1, 0.9, 575, 53, 2);
    }


    public function update(): Void
    {
        var epoch = Date.now(); // Equivalent to the current date and time

		// Formatting the time string (hour:minute:second)
		var hour = epoch.getHours() % 12;
		if (hour == 0) hour = 12; // Handle 12-hour format
		var timeStr = if (hour < 10) ' ' + hour + ':' + epoch.getMinutes() + ':' + epoch.getSeconds()
		              else hour + ':' + epoch.getMinutes() + ':' + epoch.getSeconds();

		// Formatting the AM/PM string
		var timeAPStr = epoch.getHours() < 12 ? "AM" : "PM";

		// Formatting the date string (day of the week, month, day of the month)
		var days = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
		var months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
		var dateStr = days[epoch.getDay()] + " " + months[epoch.getMonth()] + " " + epoch.getDate();


        time.updateTextInPlace(timeStr);
        ampm.updateTextInPlace(timeAPStr);
        date.updateTextInPlace(dateStr);
    }


    public function renderTo(window: Dynamic): Void
    {
        time.renderTo(window);
        ampm.renderTo(window);
        date.renderTo(window);
    }

}
