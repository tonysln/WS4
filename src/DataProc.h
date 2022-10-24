#include <vector>
#include <string>

using std::vector;
using std::string;

#ifndef WS4_DATAPROC_H
#define WS4_DATAPROC_H


namespace ws4p
{
    vector<vector<string>> readyFormatLatestData();
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
    void fetchNewData();
    int runValidator();
    void createMapRegion(int x, int y);
    void nextMoonPhases();
}

#endif //WS4_DATAPROC_H