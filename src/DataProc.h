#ifndef WS4_DATAPROC_H
#define WS4_DATAPROC_H

namespace ws4p
{
    double tempCtoF(double tempC);
    double tempFtoC(double tempF);
    double windMstoMph(double windMs);
    double windMphtoMs(double windMph);
    double presMbtoInHg(double presMb);
    double presInHgtoMb(double presInHg);
    double calcDewPoint(double tempC, double relHum);
    double calcWindChill(double tempC, double windMs);
    double calcHeatIndex(double tempC, double relHum);
    bool todayHasMoonEvent();
    void nextMoonPhases();
}

#endif //WS4_DATAPROC_H