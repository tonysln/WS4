#include "DataProc.h"
#include <stdio.h>
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
        snprintf(cmd, 100, "python3 ../scripts/map_region.py %d %d", x, y);
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
         *
         *    09 - lf1Text              ["LINE 1", "LINE 2", ..., "LINE 7"]
         *    10 - lf2Text              ["LINE 1", "LINE 2", ..., "LINE 7"]
         *    11 - lf3Text              ["LINE 1", "LINE 2", ..., "LINE 7"]
         *    12 - rfText               [forecast weekday]
         *    13 - rfCities             [city, city, ...]
         *    14 - rfTemps              [temp, temp, ...]
         *    15 - rfIcons              [RF_XXX, RF_XXX, ...]
         *
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
            {"Wilmington", "31°", "Cloudy", "43%", "11°", "10mi.", "6500 ft.", "30.41", "Wind:  ENE  5", " ", "Wind Chill:", "29°"},
            {"down"},
            {"CC_Cloudy"},
            {"Atlantic City", "35", "M Cloudy", "E  8",
             "Baltimore", "31", "Cloudy", "ENE7",
             "Dover", "33", "Cloudy", "NNE1",
             "Philadelphia", "32", "Cloudy", "NE 6",
             "Salisbury", "40", "M Cloudy", "N  6",
             "Wash/National", "36", "Cloudy", "NNE3",
             "Wilmington", "31", "Cloudy", "ENE5"},
            {"Pittsburgh", "New York", "Harrisburg", "Atl City", "Washington DC", "Charleston", "Richmond"},
            {"25", "32", "27", "35", "36", "39", "43"},
            {"RF_Rain", "RF_Sunny", "RF_Cloudy", "RF_Mostly-Cloudy", "RF_Thunderstorm", "RF_Thunderstorm", "RF_Thunderstorm"},
            {""},
            {""},
            {"THIS AFTERNOON...MOSTLY CLOUDY.",
              "HIGHS IN THE MID 30S. NORTHEAST",
              "WINDS 10 MPH.",
              " ",
              " ",
              " ",
              " "},
            {"TONIGHT...CLOUDY WITH CHANCE OF",
              "FLURRIES. LOWS 20 TO 25. LIGHT",
              "NORTHEAST WINDS.",
              " ",
              " ",
              " ",
              " "},
            {"WEDNESDAY...CLOUDY WITH A 30",
              "PERCENT CHANCE OF LIGHT RAIN OR",
              "FREEZING RAIN. HIGHS IN THE",
              "UPPER 30S. LIGHT EAST WINDS.",
              " ",
              " ",
              " "},
            {"Wednesday"},
            {"Pittsburgh", "New York", "Harrisburg", "Atl City", "Washington DC", "Charleston", "Richmond"},
            {"42", "34", "36", "41", "45", "54", "50"},
            {"RF_Sunny", "RF_Sunny", "RF_Cloudy", "RF_Cloudy", "RF_Rain-Wind", "RF_Rain", "RF_Thunderstorm"},
            {""},
            {""},
            {"New Castle County", "THU", "FRI", "SAT",
             "Showers", " ",
             "Scattered", "Showers",
             "Scattered", "Showers",
             "35", "45",
             "44", "55",
             "44", "54"},
            {"EF_Showers", "EF_Scattered-Showers", "EF_Scattered-Showers"},
            {"Tuesday", "Wednesday",
            "7:19 am", "7:19 am",
            "4:59 pm", "5:00 pm",
            "Full", "Last", "New", "First",
            "Jan 16", "Jan 23", "Jan 30", "Feb 7"},
            {"M_Full", "M_Last", "M_New", "M_First"},
            {"Conditions at Wilmington", "Cloudy",
              "Temp: 31°F     Wind Chill: 29°F",
              "Humidity:  43%    Dewpoint: 11°F",
              "Barometric Pressure: 30.41 F",
              "Wind: ENE  5 MPH",
              "Visib:  10 mi.   Ceiling: 6500 ft."},
            {"TURN TO CHANNEL 22-THE CLASSIFIED CHANNEL FOR THE BEST DEALS IN REAL ESTATE, AUTOMOBILES AND RETAIL SERVICES.  FOR ADVERTISING INFO CALL 575-0100.  CHANNEL 22-THE CLASSIFIED CHANNEL...MADE FOR YOU!"}
        };
        return data;
    }
}
