#ifndef RAINATTENUATION_H
#define RAINATTENUATION_H


#include "structs.h"

namespace ns3{
class RainAttenuation{

public:
    RainAttenuation(double f, double d,std::vector<double> R, double prctile);
    RainAttenuation(double f, double d, double theta, double tau,std::vector<double> R, double prctile);

    SpecRainAttCoeff SpecRainAttCoeffs();
    RainAttCoeff RainAttCoeffs();

    double SpecAtt(double R);
    double EffectivePathLength(double R);
    double CalcRainAtt();

    void CalcRainPrctile();
        
    double R_prctile;    
    std::vector<double> R_vec;


private:

    double f;
    double d;
    double prctile;

    double theta;
    double tau;
    SpecRainAttCoeff SpecGammaCoeffs;
    RainAttCoeff GammaCoeffs;

};

}

#endif