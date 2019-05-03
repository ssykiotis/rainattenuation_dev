#ifndef RAINPROPAGATION_H
#define RAINPROPAGATION

#include "structs.h"

namespace rainprop{
class RainPropagation{

public:
    RainPropagation(double f);

    double SpecificAttenuation();
    std::vector<Matrix> SpecificAttenuation();

    double EffectivePathLength();
    std::vector<Matrix> EffectivePathLength();

    double TotalRainAtt();
    std::vector<Matrix> TotalRainAtt();


private:

double f;

double k;
double a;
double theta;
double tau;

};
}


#endif