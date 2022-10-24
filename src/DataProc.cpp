#include "DataProc.h"
#include <cstdlib>
#include <cmath>


/*
 * Calculation Sources:
 * - M. Wanielista, R. Kersten and R. Eaglin. 1997. Hydrology Water Quantity and Quality Control
 * - https://www.weather.gov/media/epz/wxcalc/tempConvert.pdf
 * - https://www.weather.gov/media/epz/wxcalc/windConversion.pdf
 * - https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
 * - https://www.weather.gov/media/epz/wxcalc/pressureConversion.pdf
 */


namespace ws4p {
    double tempCtoF(double tempC)
    {
        return (9.0/5.0) * tempC + 32.0;
    }

    double tempFtoC(double tempF)
    {
        return (5.0/9.0) * (tempF - 32.0);
    }

    double windMstoMph(double windMs)
    {
        return 2.23694 * windMs;
    }

    double windMphtoMs(double windMph)
    {
        return 0.44704 * windMph;
    }

    double presMbtoInHg(double presMb)
    {
        return 0.0295300 * presMb;
    }

    double presInHgtoMb(double presInHg)
    {
        return 33.8639 * presInHg;
    }

    double calcDewPoint(double tempC, double relHum)
    {
        return pow(relHum/100.0, 1.0/8.0) * (112.0+0.9*tempC) + 0.1*tempC - 112.0;
    }

    double calcWindChill(double tempC, double windMs)
    {
        double tempF = tempFtoC(tempC);
        double windMph = windMstoMph(windMs);

        double windChillF = 35.74 + (0.6215 * tempF) - (35.75 * pow(windMph, 0.16)) +
                                                (0.4275 * tempF * pow(windMph, 0.16));

        return tempCtoF(windChillF);
    }

    double calcHeatIndex(double tempC, double relHum)
    {
        double tempF = tempCtoF(tempC);
        double HI_simple = 0.5 * (tempF + 61.0 + ((tempF-68.0)*1.2) + (relHum*0.094));
        if (HI_simple < 80)
            return HI_simple;

        double heatIdx = -42.379 + 2.04901523*tempF + 10.14333127*relHum -
                0.22475541*tempF*relHum - 0.00683783*tempF*tempF - 0.05481717*relHum*relHum + 
                0.00122874*tempF*tempF*relHum + 
                0.00085282*tempF*relHum*relHum - 0.00000199*tempF*tempF*relHum*relHum;


        if ((relHum < 13.0) & (tempF > 80.0) & (tempF < 112.0))
            heatIdx -= ((13.0-relHum)/4.0) * sqrt((17-abs(tempF-95.0))/17.0);
        else if ((relHum > 85.0) & (tempF > 80.0) & (tempF < 87.0))
            heatIdx += ((relHum-85.0)/10.0) * ((87-tempF)/5.0);


        return tempFtoC(heatIdx);
    }

    bool todayHasMoonEvent()
    {
        return false;
    }

    void nextMoonPhases()
    {

    }


    int runValidator()
    {
        int valid = std::system("python3 ../scripts/validate.py");
        return valid;
    }

    void createMapRegion(int x, int y)
    {
        char *cmd = new char[100];
        sprintf(cmd, "python3 ../scripts/map_region.py %d %d", x, y);
        cmd[99] = '\0';

        std::system(cmd);
        delete[] cmd;
    }

    void fetchNewData()
    {

    }

    vector<vector<string>> readyFormatLatestData()
    {
        /*
         * data:
         *    00 - ccText               [city, temp, cond, hum, dewp, ceil, visib, press, Wind:  DIR XX,
         *                                                  Gusts to  XX?, Wind Chill:/Heat Index:?, WC/HI value]
         *    01 - ccPressureArrowUp    [up/down]
         *    02 - ccIcon               [CC_XXXX]
         *    03 - loText               [(city, temp, cond, wind) * 7]
         *    04 - roCities             [city, city, ...]
         *    05 - roTemps              [temp, temp, ...]
         *    06 - roIcons              [RF_XXX, RF_XXX, ...]
         *    07 - roXCoords            [X, X, ...]
         *    08 - roYCoords            [Y, Y, ...]
         *    09 - lf1Text              ["LINE 1", "LINE 2", ..., "LINE 7"]
         *    10 - lf2Text              ["LINE 1", "LINE 2", ..., "LINE 7"]
         *    11 - lf3Text              ["LINE 1", "LINE 2", ..., "LINE 7"]
         *    12 - rfText               [forecast weekday]
         *    13 - rfCities             [city, city, ...]
         *    14 - rfTemps              [temp, temp, ...]
         *    15 - rfIcons              [RF_XXX, RF_XXX, ...]
         *    16 - rfXCoords            [X, X, ...]
         *    17 - rfYCoords            [Y, Y, ...]
         *    18 - efText               [city, DAY1, DAY2, DAY3, cond11, cond12, cond21, cond22, cond31, cond32, lo1, hi1, lo2, h2, lo3, h3]
         *    19 - efIcons              [EF_XXX, EF_XXX, EF_XXX]
         *    20 - aText                [day1, day2, sunrise1, sunrise2, sunset1, sunset2, mphase1, mphase2, mphase3, mphase4, mday1, mday2, mday3, mday4]
         *    21 - aMoons               [M_Phase1, M_Phase2, M_Phase3, M_Phase4]
         *    22 - LDLStrings           ["Conditions at city", cond, "Temp: XX°F", "Humidity:  XX%,
         *                                     Dewpoint: XX°", "Barometric Pressure: XX.XX F", "Wind: DIR  XX MPH",
         *                                     "Visib: X.X mi.  Ceiling: XXXX ft.", "MONTH Precipitation: X.XX in"]
         *    23 - LDLScrollStr         ["Scrolling text..."]
         */

        vector<vector<string>> data =
        {
            {"Moline", "56°", "Ice Snow", "66%", "53°", "0.8 mi.", "3300 ft.", "29.93", "Wind:  WNW  38", "Gusts to  77", "Wind Chill:", "52°"},
            {"up"},
            {"CC_Ice-Snow"},
            {"Altus", "71", "M Cloudy", "SE16",
             "Enid", "59", "T Shower", "NE22",
             "Gage", "59", "T Shower", "NE22",
             "Oklahoma City", "62", "Lgt Rain", "SE17",
             "Ponca City", "61", "Fair", "E 24",
             "Tinker AFB", "62", "T Shower", "SE10",
             "Tulsa", "65", "Cloudy", "NE14"},
            {"Oklahoma", "Ponca City", "Tulsa", "Altus", "Gage", "Tinker AFB"},
            {"62", "61", "65", "71", "59", "62"},
            {"RF_Rain", "RF_Sunny", "RF_Cloudy", "RF_Mostly-Cloudy", "RF_Thunderstorm", "RF_Thunderstorm"},
            {"80", "140", "290", "230", "410", "400"},
            {"330", "250", "110", "180", "130", "310"},
            {"RAIN IN THE AFTERNOON. HIGHS IN",
              "THE UPPER 70S. SOUTHEAST WINDS",
              "10 TO 15 MPH. CHANCE OF RAIN 50",
              "PERCENT.",
              "",
              "TONIGHT...PARTLY CLOUDY IN THE",
              "EVENING, THEN BECOMING MOSTLY"},
            {"CLOUDY. LOWS IN THE UPPER 60S.",
              "SOUTH WINDS 5 TO 10 MPH.",
              "",
              "WEDNESDAY...MOSTLY CLOUDY.",
              "CHANCE OF RAIN IN THE MORNING",
              "THEN SHOWERS LIKELY AND CHANCE",
              "OF THUNDERSTORMS IN THE"},
            {"EVENING.",
              "",
              "",
              "",
              "",
              "",
              ""},
            {"Monday"},
            {"Oklahoma", "Ponca City", "Tulsa", "Altus", "Gage", "Tinker AFB"},
            {"68", "69", "62", "63", "51", "65"},
            {"RF_Sunny", "RF_Sunny", "RF_Cloudy", "RF_Cloudy", "RF_Rain-Wind", "RF_Rain"},
            {"80", "140", "290", "230", "410", "400"},
            {"330", "250", "110", "180", "130", "310"},
            {"Moline", "TUE", "WED", "THU",
             "T'Storms", "",
             "Mostly", "Cloudy",
             "Showers", "",
             "77", "87",
             "76", "89",
             "76", "88"},
            {"EF_Thunderstorms", "EF_Mostly-Cloudy", "EF_Snow-to-Rain"},
            {"Saturday", "Sunday",
            "7:57 am", "7:58 am",
            "5:25 pm", "5:26 pm",
            "New", "First", "Full", "Last",
            "Jan 1", "Jan 8", "Jan 16", "Jan 24"},
            {"M_New", "M_First", "M_Full", "M_Last"},
            {"Conditions at Moline", "Ice Snow",
              "Temp: 56°F",
              "Humidity:  66%   Dewpoint: 53°",
              "Barometric Pressure: 29.93 F",
              "Wind: WNW  38 MPH",
              "Visib:   0.8 mi.  Ceiling:3300 ft.",
              "October Precipitation: 0.09 in"},
            {"Ministry: Rail Baltica progress slowed by poor design work, bad management."}
        };
        return data;
    }
}
