#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include "structs.h"
#include "math.h"

using namespace rainprop;

int main(){

  double lat = 52.52;
  double lon = 13.4049;
   std::vector<Koppen> koppen;
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

          koppen.push_back(cords);
        }

        ip.close();

        /////////////
        std::vector<Koppen> koppen_search = koppen;

        for (int i = 0; i < koppen_search.size(); i++)
        {
            koppen_search[i].lat =fabs(koppen[i].lat-lat);
            koppen_search[i].lon =fabs(koppen[i].lon-lon);
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
        
            while(koppen_search[last_index].lat==min){
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
        std::cout << index <<std::endl;

    
        
    return 0;
};
