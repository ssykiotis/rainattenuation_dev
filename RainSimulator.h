#ifndef RAINSIMULATOR_H
#define RAINSIMULATOR_H


#include <iostream>
#include <fstream>
#include <vector>

#include <stdlib.h>
#include "control.h"
#include "structs.h"


namespace rainprop{


class RainSimulator{

public:

    RainSimulator(Control controlSettings);

    std::vector<Koppen> ReadKoppen();
    std::vector<double> ReadCoordinates(const char* filename);

    char GetClimaticRegion();
    char DecideClimaticRegion();

    Cords GetLocation();
    Cords SetLocation(Cords loc);
    ITUR837_values ITUR837_calculation();

    void RainValues();
    void SplitInRainEvents();
    void SimulateRainYear();

    double GetR_001(int i);

    std::vector<std::vector<double> > GetSimulatedValues(int i);
    void RainPercentile();
private:

    //Helper functions for internal use
    int FindMinIndex(std::vector<double> map);
    std::vector<Cords> ClosestPoints(std::vector<double> latMap,std::vector<double> lonMap, int latMinIndex,int lonMinIndex);
    double BilinearInterpolation(std::vector<double> T, std::vector<Cords> sq, double lat,double lon, std::vector<double> latMap,std::vector<double>lonMap);
    double ReadCsvValue(const char* filename,int i,int latMinIndex,int lonMinIndex);

    std::vector<Matrix> ReadRainValues(const char* filename);
    std::vector<Matrix> ConvertRainValues(std::vector<Matrix> R_60);
   

    //
    
    Cords loc;
    char cl_region;
    ITUR837_values itu_v;
    Control control;
    std::vector<Matrix> R_01;
    std::vector< std::vector<RainEvent> > RainEvents;
    std::vector<Matrix> R_01_simulated;
    std::vector<double> R_001;

};

}

#endif