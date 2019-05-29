
#include <iostream> //FOR TESTING PURPOSES, TO BE REMOVED LATER

#include "structs.h"
#include "control.h"
#include "RainGenerator.h"
#include "RainPropagation.h"
#include <fstream>
#include <cmath>


int main(){

rainprop::Control controlSettings(52.52,13.4049,60e09,1000);

rainprop::RainGenerator rainGenerator(controlSettings);
rainGenerator.Run();

rainprop::RainPropagation RainProp(controlSettings,rainGenerator.GetSimulatedValues(0),0,0);
RainProp.Run();

//////////////////////////////////////////////////////////////////////////////////

// double val=0;

// for (int i = 0; i < 200000; i++)
// {
//     val = RainProp.GetNextValue(); 
//     if (val!=-1){
//       std::cout << val << std::endl;
//     }    
// }

std::vector<double> gamma_r;
std::vector<double> effpl;
std::vector<double> totalatt;
std::vector<double> rainvalues;

std::ofstream outFile("specatts.csv");
std::ofstream outFile2("effpl.csv");
std::ofstream outFile3("att.csv");
std::ofstream outFile4("rainvalues.csv");
for (int k = 0; k < 12; k++)
{
    std::cout << k <<std::endl;
    RainProp.SetRainValues(rainGenerator.GetSimulatedValues(k));
    RainProp.Run();

    rainvalues = RainProp.Reshape(rainGenerator.GetSimulatedValues(k));
    gamma_r = RainProp.GetGammaR();
    effpl = RainProp.GetEffpl();
    totalatt = RainProp.GetTotalAtt();


    for (int i = 0; i < totalatt.size(); i++)
    {
    outFile  << gamma_r[i] << "\n"; 
    outFile2 << effpl[i]    << "\n";
    outFile3 << totalatt[i] << "\n";
    outFile4 << rainvalues[i] << "\n";
    }
}

return 0;
}
