#include <math.h>

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


        if (relHum < 13.0 & 80.0 < tempF < 112.0)
            heatIdx -= ((13.0-relHum)/4.0) * sqrt((17-abs(tempF-95.0))/17.0);
        else if (relHum > 85.0 & 80.0 < tempF < 87.0)
            heatIdx += ((relHum-85.0)/10.0) * ((87-tempF)/5.0);


        return tempFtoC(heatIdx);
    }

    bool todayHasMoonEvent()
    {
        return false;
    }

    void nextMoonPhases()
    {
        return;
    }
}