#ifndef RAINPROPAGATION_H
#define RAINPROPAGATION

#include "structs.h"

namespace rainprop{
class RainPropagation{

public:
    RainPropagation(double f,double d);
    RainPropagation(double f,double d,double theta,double tau);    

    SpecRainAttCoeff SpecRainAttCoeffs();
    RainAttCoeff RainAttCoeffs();

    // double SpecificAttenuation();
    // std::vector<Matrix> SpecificAttenuation();

    // double EffectivePathLength();
    // std::vector<Matrix> EffectivePathLength();

    // double TotalRainAtt();
    // std::vector<Matrix> TotalRainAtt();


private:

    double f;
    double d;

    double theta;
    double tau;
    SpecRainAttCoeff SpecGammaCoeffs;
    RainAttCoeff GammaCoeffs;

};
}


#endif