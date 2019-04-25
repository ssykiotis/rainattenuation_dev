#include "control.h"
#include "RainSimulator.h"
#include <iostream>

int main(){

rainprop::Control controlSettings(52.52,13.4049);

rainprop::RainSimulator rainSimulator(controlSettings);

std::cout <<rainSimulator.GetClimaticRegion() << std::endl;
std::cout << rainSimulator.GetLocation().lat <<std::endl;
std::cout << rainSimulator.GetLocation().lon <<std::endl;

rainSimulator.ITUR837_calculation();

return 0;
}
