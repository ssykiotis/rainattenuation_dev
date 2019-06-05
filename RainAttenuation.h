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
    std::vector<double> SpecAtt(std::vector<double> R);

    std::vector<double> EffectivePathLength();

    std::vector<double> TotalRainAtt();
    
    void SetRainValues(std::vector<std::vector<double>>R_01);

    void CalculateRainAttenuation();
    std::vector<double> Reshape(std::vector<std::vector<double> > V);

    std::vector<double> GetGammaR();
    std::vector<double> GetEffpl();
    std::vector<double> GetTotalAtt();

    double GetNextValue();

    void Run();

private:

    double f;
    double d;
    std::vector<double> R_01;

    double theta;
    double tau;
    SpecRainAttCoeff SpecGammaCoeffs;
    RainAttCoeff GammaCoeffs;

    std::vector<double> gamma_r;
    std::vector<double> effpl;
    std::vector<double> totalatt;
    int curridx;

};
}


#endif