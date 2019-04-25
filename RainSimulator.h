#ifndef RAINSIMULATOR_H
#define RAINSIMULATOR_H


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "control.h"
#include "structs.h"

namespace rainprop{


class RainSimulator{

public:

    RainSimulator(Control controlSettings);

    std::vector<Koppen> ReadKoppen();
    std::vector<double> ReadCoordinates(const char* filename);

    //Helper functions for internal use
    int FindMinIndex(std::vector<double> map);
    std::vector<Cords> ClosestPoints(std::vector<double> latMap,std::vector<double> lonMap, int latMinIndex,int lonMinIndex);
    double BilinearInterpolation(std::vector<double> T, std::vector<Cords> sq, double lat,double lon, std::vector<double> latMap,std::vector<double>lonMap);
    double ReadCsvValue(const char* filename,int i,int latMinIndex,int lonMinIndex);

    char GetClimaticRegion();
    char DecideClimaticRegion();
    
    Cords SetLocation(Cords loc);
    Cords GetLocation();
    ITUR837_values ITUR837_calculation();

private:
    char cl_region;
    Cords loc;
    ITUR837_values itu_v;
    Control control;
};

}

#endif