#include "control.h"
#include "RainSimulator.h"
#include <iostream>

int main(){

rainprop::Control controlSettings;

rainprop::RainSimulator rainSimulator(52.52,13.4049);

// controlSettings.SetLocation();
// rainSimulator.SetLocation(controlSettings.GetLocation());

std::cout <<rainSimulator.GetClimaticRegion() << std::endl;
std::cout << rainSimulator.GetLocation().lat <<std::endl;
std::cout << rainSimulator.GetLocation().lon <<std::endl;

rainSimulator.ITUR837_calculation();

return 0;
}
