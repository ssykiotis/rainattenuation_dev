#ifndef RAINPROPAGATION_H
#define RAINPROPAGATION_H


#include "structs.h"

namespace rainprop{
class RainPropagation{

public:
    RainPropagation(double f,double d,std::vector<double> Rprctl);
    RainPropagation(double f,double d,double theta,double tau,std::vector<double> Rprctl);    

    SpecRainAttCoeff SpecRainAttCoeffs();
    RainAttCoeff RainAttCoeffs();

    double SpecAtt(double R);
    std::vector<std::vector<double>> SpecAtt(std::vector<std::vector<double>> R);

    std::vector<double> EffectivePathLength(std::vector<double> Rprctl);

    double TotalRainAtt();
    
    // std::vector<Matrix> TotalRainAtt();
    std::vector<double> effpl;

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