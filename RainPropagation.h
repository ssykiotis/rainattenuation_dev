#ifndef RAINPROPAGATION_H
#define RAINPROPAGATION_H


#include "structs.h"
#include "control.h"

namespace rainprop{
class RainPropagation{

public:
    RainPropagation(Control controlSettings,std::vector<double> Rprctl); 
    RainPropagation(Control controlSettings,std::vector<double> Rprctl,double theta,double tau);  

    SpecRainAttCoeff SpecRainAttCoeffs();
    RainAttCoeff RainAttCoeffs();

    double SpecAtt(double R);
    std::vector<std::vector<double>> SpecAtt(std::vector<std::vector<double>> R);

    std::vector<double> EffectivePathLength(std::vector<double> Rprctl);

    double TotalRainAtt(double R,int month);
    std::vector<std::vector<double> > TotalRainAtt(std::vector<std::vector<double> >,int i);
    
    // std::vector<Matrix> TotalRainAtt();

private:

    double f;
    double d;

    double theta;
    double tau;
    SpecRainAttCoeff SpecGammaCoeffs;
    RainAttCoeff GammaCoeffs;
    std::vector<double> effpl;


};
}


#endif