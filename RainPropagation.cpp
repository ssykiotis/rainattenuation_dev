#include "RainPropagation.h"
#include <math.h> 
#include <cmath>

namespace rainprop{

RainPropagation::RainPropagation(double f,double d){
    this->f = f;
    this->d = d;
    this->theta = 0;
    this->tau = 0;
    this->SpecGammaCoeffs = SpecRainAttCoeffs();
    this->GammaCoeffs = RainAttCoeffs();
};
RainPropagation::RainPropagation(double f,double d,double theta,double tau){
    this->f = f;
    this->d = d;
    this->theta = theta;
    this->tau = tau;
    this->SpecGammaCoeffs = SpecRainAttCoeffs();
    this->GammaCoeffs = RainAttCoeffs();
};

SpecRainAttCoeff RainPropagation::SpecRainAttCoeffs(){
    std::vector <std::vector<double> > k_h_table{  {-5.33980,-0.10008, 1.13098},
                                                   {-0.35351, 1.26970, 0.45400},
                                                   {-0.23789, 0.86036, 0.15354},
                                                   {-0.94158, 0.64552, 0.16817}
                                                 };

    std::vector <std::vector<double> > k_v_table{  {-3.80595, 0.56934, 0.81061},
                                                   {-3.44965,-0.22911, 0.51059},
                                                   {-0.39902, 0.73042, 0.11899},
                                                   { 0.50167, 1.07319, 0.27195}
                                                  };

    std::vector <std::vector<double> > a_h_table{  {-0.14318, 1.82442,-0.55187},
                                                   { 0.29591, 0.77564, 0.19822},
                                                   { 0.32177, 0.63773, 0.13164},
                                                   {-5.37610,-0.96230, 1.47828},
                                                   {16.17210,-3.29980, 3.43990}
                                                  };

    std::vector <std::vector<double> > a_v_table{  {-0.07771, 2.33840,-0.76284},
                                                   { 0.56727, 0.95545, 0.54039},
                                                   {-0.20238, 1.14520, 0.26809},
                                                   {-48.2991,0.791669,0.116226},
                                                   { 48.5833,0.791459,0.116479}
                                                  };                                                  

    double k_h_m = -0.18961;
    double k_h_c = 0.71147;

    double k_v_m = -0.16398;
    double k_v_c = 0.63297;

    double a_h_m = 0.67849;
    double a_h_c = -1.95537;
    
    double a_v_m = -0.053739;
    double a_v_c = 0.83433;

    double log_f =log10(f/1e09);
    SpecRainAttCoeff gammacoeffs {0,0,0,0};

    for (int i = 0; i < k_h_table.size(); i++){
        gammacoeffs.k_h += k_h_table[i][0]*exp(-pow((log_f-k_h_table[i][1])/k_h_table[i][2],2));
        gammacoeffs.k_v += k_v_table[i][0]*exp(-pow((log_f-k_v_table[i][1])/k_v_table[i][2],2)); 
    }
    gammacoeffs.k_h+=log_f*k_h_m+k_h_c;
    gammacoeffs.k_v+=log_f*k_v_m+k_v_c;

    for (int i = 0; i < a_h_table.size(); i++){
        gammacoeffs.a_h += a_h_table[i][0]*exp(-pow((log_f-a_h_table[i][1])/a_h_table[i][2],2));
        gammacoeffs.a_v += a_v_table[i][0]*exp(-pow((log_f-a_v_table[i][1])/a_v_table[i][2],2)); 
    }
    gammacoeffs.a_h+=log_f*a_h_m+a_h_c;
    gammacoeffs.a_v+=log_f*a_v_m+a_v_c;
    gammacoeffs.k_h = pow10(gammacoeffs.k_h);
    gammacoeffs.k_v = pow10(gammacoeffs.k_v);

    return gammacoeffs;

    

};

RainAttCoeff RainPropagation::RainAttCoeffs(){
    RainAttCoeff attcoeffs;
    attcoeffs.k = (SpecGammaCoeffs.k_h+SpecGammaCoeffs.k_v+(SpecGammaCoeffs.k_h-SpecGammaCoeffs.k_v)*pow(cos(theta),2)*cos(2*tau))/2;
    attcoeffs.a = (SpecGammaCoeffs.k_h*SpecGammaCoeffs.a_h+SpecGammaCoeffs.k_v*SpecGammaCoeffs.a_v
        +(SpecGammaCoeffs.k_h*SpecGammaCoeffs.a_h-SpecGammaCoeffs.k_v*SpecGammaCoeffs.a_h)*pow(cos(theta),2)*cos(2*tau))/(2*attcoeffs.k);
    return attcoeffs;
};

double RainPropagation::SpecAtt(double R){
    return GammaCoeffs.k*pow(R,GammaCoeffs.a);
};

std::vector<std::vector<double> > RainPropagation::SpecAtt(std::vector<std::vector<double>> R){
    std::vector<std::vector<double> > gamma_R = R;

    for (int i = 0; i < R.size(); i++){
        for (int j = 0; j < R[i].size(); j++){
            gamma_R[i][j]= SpecAtt(R[i][j] ) ;
        }
    }
    return gamma_R;
};

}