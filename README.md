# WS4

C++ 20

libsfml-dev >= 2.6.0

gcc 11+

cmake 3+

OpenGL ?

OpenAL ?

### Build

Make sure that the correct path is set in the Makefile for SFML files.

```bash
$ cd src
$ make clean
$ make
```

### TODOs

- Pressure up/down arrows on CC screen
- Music playback loop fix
- Finalize basemap loading
- Pretty much all of data gathering stuff

https://forecast.weather.gov/MapClick.php?lat=47.6218&lon=-122.35&unit=0&lg=english&FcstType=text&TextType=2

https://forecast.weather.gov/MapClick.php?CityName=Medford&state=NY&site=OKX&lat=40.8224&lon=-72.9847

https://forecast.weather.gov/product.php?site=NWS&issuedby=OKX&product=RWR&format=CI&version=1&glossary=1&highlight=off

https://tgftp.nws.noaa.gov/data/forecasts/zone/

https://airquality.weather.gov/

https://graphical.weather.gov/xml/

https://graphical.weather.gov/xml/xml_fields_icon_weather_conditions.php

https://alerts.weather.gov/

https://www.aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=xml&hoursBeforeNow=3&mostRecent=true&stationString=EETU

