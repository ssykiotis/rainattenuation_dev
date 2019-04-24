#include "control.h"
#include "RainSimulator.h"
#include <iostream>

int main(){

rainprop::Control controlSettings;
rainprop::RainSimulator rainSimulator;

controlSettings.SetLocation(52.0,13.0);
rainSimulator.SetLocation(controlSettings.GetLocation());

std::cout <<rainSimulator.GetClimaticRegion() << std::endl;
std::cout << rainSimulator.GetLocation().lat <<std::endl;
std::cout << rainSimulator.GetLocation().lon <<std::endl;

return 0;
}
