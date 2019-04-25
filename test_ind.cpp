#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include "structs.h"
#include "math.h"

using namespace rainprop;

int main(){

  for (int i = 1; i < 13; i++)
  {
      char buffer[50];
      int n = sprintf(buffer,"rain_data/ITU/temperature/T_Month%.2d.txt",i);
      std::cout << buffer << std::endl;
  }
    return 0;
};
