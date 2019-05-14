
#include <iostream> //FOR TESTING PURPOSES, TO BE REMOVED LATER

#include "structs.h"
#include "control.h"
#include "RainGenerator.h"
#include "RainPropagation.h"
#include "malloc.h"


int main(){

rainprop::Control controlSettings(52.52,13.4049);

rainprop::RainGenerator rainGenerator(controlSettings);

std::cout <<rainGenerator.GetClimaticRegion()<<std::endl;
std::cout << rainGenerator.GetLocation().lat <<std::endl;
std::cout << rainGenerator.GetLocation().lon <<std::endl;


rainGenerator.ITUR837_calculation();
rainGenerator.RainValues();
rainGenerator.SplitInRainEvents();
rainGenerator.SimulateRainYear();
rainGenerator.RainPercentile();

rainprop::RainPropagation RainProp(60e09,1000,0,0,rainGenerator.GetR_001());


// std::vector<rainprop::Matrix> rainatt{12};
// for (int i = 0; i < rainatt.size(); i++){
//     rainatt[i].v = RainProp.SpecAtt(rainGenerator.GetSimulatedValues(i));
// }
std::vector<double> r =RainProp.EffectivePathLength(rainGenerator.GetR_001());

return 0;
}
