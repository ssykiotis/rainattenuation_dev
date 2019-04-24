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

    char GetClimaticRegion();
    char DecideClimaticRegion();
    std::vector<Koppen> ReadKoppen();
    Cords SetLocation(Cords loc);
    Cords GetLocation();

private:
    char cl_region;
    Cords loc;

};

}

#endif