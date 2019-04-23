#include "control.h"
#include <iostream>

int main(){

rainprop::Control controlSettings;

controlSettings.print();
std::cout << controlSettings.GetLocationLat()<<std::endl;
// std::cout << controlSettings.GetLocationLat() << "\n";
// std::cout << controlSettings.GetLocationLon() << "\n";

}