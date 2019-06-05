
#include <iostream> //FOR TESTING PURPOSES, TO BE REMOVED LATER

#include "structs.h"
#include "control.h"
#include "RainGenerator.h"
#include "RainAttenuation.h"

#include <fstream>
#include <iterator>
#include <string>
#include <vector>

int main(){

ns3::Control controlSettings(52.52,13.4049);

ns3::RainGenerator rainGenerator(controlSettings);
rainGenerator.Run();


ns3::RainAttenuation RainAtt(60e09,1000,rainGenerator.GetRainValues(6),100);

double ratt = RainAtt.CalcRainAtt();


return 0;
}
