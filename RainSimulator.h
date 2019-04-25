#ifndef RAINSIMULATOR_H
#define RAINSIMULATOR_H


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "structs.h"

namespace rainprop{


class RainSimulator{

public:

    RainSimulator(double lon,double lat);

    std::vector<Koppen> ReadKoppen();
    std::vector<double> ReadCoordinates(const char* filename);
    int FindMinIndex(std::vector<double> map);
    void ReadCsvValue(std::string target, const char* filename,int latMinIndex,int lonMinIndex);

    char GetClimaticRegion();
    char DecideClimaticRegion();
    
    Cords SetLocation(Cords loc);
    Cords GetLocation();
    ITUR837_values ITUR837_calculation();

private:
    char cl_region;
    Cords loc;
    ITUR837_values itu_v;
};

}

#endif