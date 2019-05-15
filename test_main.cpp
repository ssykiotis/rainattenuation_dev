
#include <iostream> //FOR TESTING PURPOSES, TO BE REMOVED LATER

#include "structs.h"
#include "control.h"
#include "RainGenerator.h"
#include "RainPropagation.h"
#include "malloc.h"


int main(){

rainprop::Control controlSettings(52.52,13.4049);

rainprop::RainGenerator rainGenerator(controlSettings);
rainGenerator.Run();

rainprop::RainPropagation RainProp(60e09,1000,0,0,rainGenerator.GetR_001());


// std::vector<rainprop::Matrix> rainatt{12};
// for (int i = 0; i < rainatt.size(); i++){
//     rainatt[i].v = RainProp.SpecAtt(rainGenerator.GetSimulatedValues(i));
// }
std::vector<double> r =RainProp.EffectivePathLength(rainGenerator.GetR_001());

return 0;
}
