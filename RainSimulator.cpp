#include "RainSimulator.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>


namespace rainprop{

    RainSimulator::RainSimulator(){
        cl_region = DecideClimaticRegion();
    }; 

     Cords RainSimulator::SetLocation(Cords loc){
         this->loc = loc;
    };

    Cords RainSimulator::GetLocation(){
        return this->loc;
    };



    char RainSimulator::GetClimaticRegion(){
        return this->cl_region;
    };

    char RainSimulator::DecideClimaticRegion(){
        std::vector<Koppen> koppen = ReadKoppen();
        

        std::string temp = koppen[0].region;
        char cstr[temp.size()];
        strcpy(cstr,temp.c_str());
        char a = cstr[0];
        return a;
    };

    std::vector<Koppen> RainSimulator::ReadKoppen(){
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
        return v;
    };


}
