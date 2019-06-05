
#include <iostream> //FOR TESTING PURPOSES, TO BE REMOVED LATER

#include "structs.h"
#include "control.h"
#include "RainGenerator.h"
#include "RainAttenuation.h"

int main(){

ns3::Control controlSettings(52.52,13.4049);

ns3::RainGenerator rainGenerator(controlSettings);
rainGenerator.Run();
std::vector<double> test;



// ns3::RainPropagation RainProp(controlSettings,rainGenerator.GetSimulatedValues(0),0,0);
// RainProp.Run();

return 0;
}
