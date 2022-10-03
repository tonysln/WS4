# WS4

About...

Make sure to read the Documentation & Reference in `/doc` for a full overview and explanation of the system.

## Project Structure

```shell
/
├── *bin                          # Compiled binary files
├── config                        # System configuration files
├── data                          # Data files for graphics and weather info
├── doc                           # Documentation & reference
├── extlibs                       # External libraries
├── fonts                         # Font files
├── graphics                      # Graphical elements
│     ├── icons
│     └── maps
├── *music                        # Background music
├── *obj                          # Compiled object files
├── src                           # Source and header files
├── .gitignore
├── Makefile
└── README.md
```

*Folders marked with an asterisk (\*) are ignored by git*.

## Requirements

Should work on any OS... (TODO experiment)

| Library Name  | Version  |
| ------------- |----------|
| G++           | >= 11    |
| SFML          | >= 2.6.0 |
| libcurl       | >= 7.58.0|



### Build & Run

```bash
$ make clean
$ make
$ ./bin/WS4
```

...

## Configuration

To be updated...

## TODOs

- Pressure up/down arrows on CC screen
- Music playback loop fix
- Finalize basemap loading
- Pretty much all of data gathering stuff

## Temp links

https://forecast.weather.gov/MapClick.php?lat=47.6218&lon=-122.35&unit=0&lg=english&FcstType=text&TextType=2

https://forecast.weather.gov/MapClick.php?CityName=Medford&state=NY&site=OKX&lat=40.8224&lon=-72.9847

https://forecast.weather.gov/product.php?site=NWS&issuedby=OKX&product=RWR&format=CI&version=1&glossary=1&highlight=off

https://tgftp.nws.noaa.gov/data/forecasts/zone/

https://airquality.weather.gov/

https://graphical.weather.gov/xml/

https://graphical.weather.gov/xml/xml_fields_icon_weather_conditions.php

https://alerts.weather.gov/

https://www.aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=xml&hoursBeforeNow=3&mostRecent=true&stationString=EETU

