#include "RainSimulator.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include "math.h"


namespace rainprop{

    RainSimulator::RainSimulator(double lat,double lon){
        this->loc.lon = lon;
        this->loc.lat = lat;
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
        std::vector<Koppen> koppen_search = koppen;

         for (int i = 0; i < koppen_search.size(); i++)
        {
            koppen_search[i].lat =fabs(koppen[i].lat-loc.lat);
            koppen_search[i].lon =fabs(koppen[i].lon-loc.lon);
        }
        

        int index=0;
        double min = koppen_search[0].lon;

        for (int i = 0; i < koppen_search.size(); i++)
        {
            if (koppen_search[i].lon<min) {
                index = i;
                min = koppen_search[i].lon;
            }
        }

        if(koppen[index+1].lon==koppen[index].lon){
            int last_index = index+1;
        
            while(koppen_search[last_index].lon==min){
                last_index++;
            }
            min = koppen_search[index].lat;
            for (int i = index; i < last_index; i++)
            {
                if (koppen_search[i].lat<min){
                    index = i;
                    min = koppen_search[i].lat;
                }
            }
        }

        std::string temp = koppen[index].region;
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

        Koppen cords;


        while(ip.good()){

          getline(ip,readlon,',');
          getline(ip,readlat,',');
          getline(ip,readregion,'\n'); 

          cords.lat = atof(readlat.c_str());
          cords.lon = atof(readlon.c_str());
          cords.region = readregion;

          v.push_back(cords);
        }

        ip.close();
        return v;
    };


}
