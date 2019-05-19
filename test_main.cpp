
#include <iostream> //FOR TESTING PURPOSES, TO BE REMOVED LATER

#include "structs.h"
#include "control.h"
#include "RainGenerator.h"
#include "RainPropagation.h"
#include <fstream>
#include <cmath>


int main(){

rainprop::Control controlSettings(52.52,13.4049,60e09,1000,7);

rainprop::RainGenerator rainGenerator(controlSettings);
rainGenerator.Run();

rainprop::RainPropagation RainProp(controlSettings,rainGenerator.GetSimulatedValues(0),0,0);
RainProp.Run();





//////////////////////////////////////////////////////////////////////////////////

// std::vector<double > totalatt;
// std::vector<std::vector<double> > specatts;

// double max = 0;
// std::ofstream outFile("att.csv");
// std::ofstream outFile2("rainvalues.csv");
// std::ofstream outFile3("specatts.csv");
// for (int k = 0; k < 12; k++)
// {
//     std::cout << k <<std::endl;
//     totalatt.clear();
//     totalatt = RainProp.TotalRainAtt(rainGenerator.GetSimulatedValues(k),k);
//     specatts = RainProp.SpecAtt(rainGenerator.GetSimulatedValues(k));
// for (int i = 0; i < totalatt.size(); i++)
// {
//     for (int j = 0; j < totalatt[i].size(); j++)
//     {
//         outFile  << totalatt[i][j] << " "; 
//         outFile2 << rainGenerator.GetSimulatedValues(k)[i][j]<<" ";
//         outFile3 << specatts[i][j] << " ";
//     }
//     outFile  << "\n";   
//     outFile2 << "\n";
//     outFile3 << "\n";
// }
// }

return 0;
}
