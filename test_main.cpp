#include <iostream>

#include "control.h"
#include "RainSimulator.h"
#include "RainPropagation.h"

int main(){

rainprop::Control controlSettings(52.52,13.4049);

rainprop::RainSimulator rainSimulator(controlSettings);

std::cout <<rainSimulator.GetClimaticRegion() << std::endl;
std::cout << rainSimulator.GetLocation().lat <<std::endl;
std::cout << rainSimulator.GetLocation().lon <<std::endl;

rainSimulator.ITUR837_calculation();
rainSimulator.RainValues();
rainSimulator.SplitInRainEvents();
rainSimulator.SimulateRainYear();

rainprop::RainPropagation RainProp(60e09,1000,0,0);

std::cout<<RainProp.SpecAtt(50)<<std::endl;

return 0;
}
