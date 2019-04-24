#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>

struct Koppen{
    double lat;
    double lon;
    std::string region;
};


int main(){

        std::vector<Koppen> v;
        std::ifstream ip("rain_data/koppen.csv");

        std::string readlat;
        std::string readlon;
        std::string readregion; 

        while(ip.good()){

          getline(ip,readlat,',');
          getline(ip,readlon,',');
          getline(ip,readregion,'\n'); 

          Koppen cords;
          cords.lat = atof(readlat.c_str());
          cords.lon = atof(readlon.c_str());
          cords.region = readregion;

          v.push_back(cords);
        }

        ip.close();

    std::string test = v[0].region;
    char cstr[test.size()];
    strcpy(cstr,test.c_str());

    char a = cstr[0];

    std::cout <<a<<std::endl;

    return 0;
};
