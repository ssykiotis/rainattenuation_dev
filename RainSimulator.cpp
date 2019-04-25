#include "RainSimulator.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include "math.h"

namespace rainprop
{

RainSimulator::RainSimulator(Control controlSettings){
    this->loc.lat = controlSettings.GetLocation().lat;
    this->loc.lon = controlSettings.GetLocation().lon;
    this->control = controlSettings;
    cl_region = DecideClimaticRegion();
};

Cords RainSimulator::SetLocation(Cords loc)
{
    this->loc = loc;
};

Cords RainSimulator::GetLocation()
{
    return this->loc;
};

char RainSimulator::GetClimaticRegion()
{
    return this->cl_region;
};

char RainSimulator::DecideClimaticRegion()
{
    std::vector<Koppen> koppen = ReadKoppen();
    std::vector<Koppen> koppen_search = koppen;

    for (int i = 0; i < koppen_search.size(); i++)
    {
        koppen_search[i].lat = fabs(koppen[i].lat - loc.lat);
        koppen_search[i].lon = fabs(koppen[i].lon - loc.lon);
    }

    int index = 0;
    double min = koppen_search[0].lon;

    for (int i = 0; i < koppen_search.size(); i++)
    {
        if (koppen_search[i].lon < min)
        {
            index = i;
            min = koppen_search[i].lon;
        }
    }

    if (koppen[index + 1].lon == koppen[index].lon)
    {
        int last_index = index + 1;

        while (koppen_search[last_index].lon == min)
        {
            last_index++;
        }
        min = koppen_search[index].lat;
        for (int i = index; i < last_index; i++)
        {
            if (koppen_search[i].lat < min)
            {
                index = i;
                min = koppen_search[i].lat;
            }
        }
    }

    std::string temp = koppen[index].region;
    char cstr[temp.size()];
    strcpy(cstr, temp.c_str());
    char a = cstr[0];
    return a;
};

std::vector<Koppen> RainSimulator::ReadKoppen()
{
    std::vector<Koppen> v;
    std::ifstream ip("rain_data/koppen.csv");

    std::string readlat;
    std::string readlon;
    std::string readregion;

    Koppen cords;

    while (ip.good())
    {

        getline(ip, readlon, ',');
        getline(ip, readlat, ',');
        getline(ip, readregion, '\n');

        cords.lat = atof(readlat.c_str());
        cords.lon = atof(readlon.c_str());
        cords.region = readregion;

        v.push_back(cords);
    }

    ip.close();
    return v;
};

std::vector<double> RainSimulator::ReadCoordinates(const char *filename)
{
    std::vector<double> v;
    std::ifstream ip(filename);
    std::string readval;

    while (ip.good())
    {
        getline(ip, readval, '\n');
        v.push_back(atof(readval.c_str()));
    }
    ip.close();
    return v;
};

int RainSimulator::FindMinIndex(std::vector<double> map)
{
    int minIndex = 0;
    double min = map[0];

    for (int i = 0; i < map.size(); i++)
    {
        if (map[i] < min)
        {
            minIndex = i;
            min = map[i];
        }
    }
    return minIndex;
};

std::vector<Cords> RainSimulator::ClosestPoints(std::vector<double> latMap,std::vector<double> lonMap, int latIndex,int lonIndex){

    std::vector<Cords> sq1;
    sq1.push_back( {latIndex  , lonIndex-1} );
    sq1.push_back( {latIndex-1, lonIndex-1} );
    sq1.push_back( {latIndex-1, lonIndex  } );
    sq1.push_back( {latIndex  , lonIndex  } );

    std::vector<Cords> sq2;
    sq2.push_back( {latIndex  , lonIndex  } );
    sq2.push_back( {latIndex-1, lonIndex  } );
    sq2.push_back( {latIndex-1, lonIndex+1} );
    sq2.push_back( {latIndex  , lonIndex+1} );

    std::vector<Cords> sq3;
    sq3.push_back( {latIndex+1, lonIndex-1} );
    sq3.push_back( {latIndex  , lonIndex-1} );
    sq3.push_back( {latIndex  , lonIndex  } );
    sq3.push_back( {latIndex+1, lonIndex  } );
    
    std::vector<Cords> sq4;
    sq4.push_back( {latIndex+1, lonIndex  } );
    sq4.push_back( {latIndex  , lonIndex  } );
    sq4.push_back( {latIndex  , lonIndex+1} );
    sq4.push_back( {latIndex+1, lonIndex+1} );
    

    std::vector<double> dist; 
    Cords point;

    double d =0;
    for (int i = 0; i < sq1.size(); i++)
    {
        point = sq1[i];
        d+= pow(latMap[point.lat],2) + pow(lonMap[point.lon],2);
    }
    dist.push_back(d);

    d =0;
    for (int i = 0; i < sq2.size(); i++)
    {
        point = sq2[i];
        d+= pow(latMap[point.lat],2) + pow(lonMap[point.lon],2);
    }
    dist.push_back(d);
    
    d =0;
    for (int i = 0; i < sq3.size(); i++)
    {
        point = sq3[i];
        d+= pow(latMap[point.lat],2) + pow(lonMap[point.lon],2);
    }
    dist.push_back(d);

    d =0;
    for (int i = 0; i < sq4.size(); i++)
    {
        point = sq4[i];
        d+= pow(latMap[point.lat],2) + pow(lonMap[point.lon],2);
    }
    dist.push_back(d);

    int minIndex = 0;
    double min = dist[0];

    for (int i = 0; i < dist.size(); i++){
        if (dist[i]<min)
        {
            minIndex = i;
            min = dist[i];
        }
        
    }

    switch (minIndex)
    {
    case 0:
        return sq1;
    case 1:
        return sq2;    
    case 2:
        return sq3;    
    case 3:
        return sq4;
    default:
        break;
    }
    
};

double RainSimulator::BilinearInterpolation(std::vector<double> T, std::vector<Cords> sq, double lat,double lon, std::vector<double> latMap,std::vector<double>lonMap){

    double R = sq[0].lat;
    double C = sq[0].lon;
    double r = R+ (lat - latMap[R])/(latMap[R+1]-latMap[R]);
    double c = C+ (lon-lonMap[C])/(lonMap[C+1]-lonMap[C]);

    double I_rc = T[0]*(R-r+1)*(C-c+1)+T[1]*(r-R)*(C-c+1) +T[2]*(R-r+1)*(c-C) + T[3]*(r-R)*(c-C);
    return I_rc; 
};



double RainSimulator::ReadCsvValue(const char* filename,int i, int latMinIndex, int lonMinIndex){
        
        char buffer[100];
        int n = sprintf(buffer, filename, i);
        std::ifstream ip(buffer);
        std::string line;
        int LinesToGo = latMinIndex;
        while (getline(ip, line) && (LinesToGo > 0))
        {
            LinesToGo--;
        }
        ip.close();
        int index = 0;
        std::string delimiter = " ";
        while (index != lonMinIndex)
        {
            line.erase(0, line.find(delimiter) + delimiter.length());
            index++;
        }
        std::string val = line.substr(0, line.find(delimiter));

        return atof(val.c_str());

};

ITUR837_values RainSimulator::ITUR837_calculation(){


    //calculate Mean Temperatures
    std::vector<double> latMap = ReadCoordinates("rain_data/ITU/temperature/LAT_T.csv");
    std::vector<double> lonMap = ReadCoordinates("rain_data/ITU/temperature/LON_T.csv");

    std::vector<double> latMap_or = latMap;
    std::vector<double> lonMap_or = lonMap;
    for (int i = 0; i < latMap.size(); i++){
        latMap[i] = fabs(latMap[i] - loc.lat);
    }
    for (int i = 0; i < lonMap.size(); i++) {
        lonMap[i] = fabs(lonMap[i] - loc.lon);
    }

    int latMinIndex = FindMinIndex(latMap);
    int lonMinIndex = FindMinIndex(lonMap);

    std::vector<Cords> sq = ClosestPoints(latMap,lonMap,latMinIndex,lonMinIndex);
    std::vector<double> T;
    for (int i = 1; i < 13; i++){
        const char* filename = "rain_data/ITU/temperature/T_Month%.2d.csv";
        for (int j = 0; j < sq.size(); j++){
           T.push_back(ReadCsvValue(filename, i, sq[j].lat, sq[j].lon));    
        }
        itu_v.Temperature.push_back(BilinearInterpolation(T,sq,loc.lat,loc.lon,latMap_or,lonMap_or));
        T.clear();     
    } 

    latMap.clear();
    lonMap.clear();

    //calculate Mean Monthly Total Rainfall
    latMap = ReadCoordinates("rain_data/ITU/monthly_total/LAT_MT.csv");
    lonMap = ReadCoordinates("rain_data/ITU/monthly_total/LON_MT.csv");

    latMap_or = latMap;
    lonMap_or = lonMap;

    for (int i = 0; i < latMap.size(); i++){
        latMap[i] = fabs(latMap[i] - loc.lat);
    }
    for (int i = 0; i < lonMap.size(); i++){
        lonMap[i] = fabs(lonMap[i] - loc.lon);
    }

    latMinIndex = FindMinIndex(latMap);
    lonMinIndex = FindMinIndex(lonMap);

    sq = ClosestPoints(latMap,lonMap,latMinIndex,lonMinIndex);
    std::vector<double> MT;
    for (int i = 1; i < 13; i++){
        const char* filename = "rain_data/ITU/monthly_total/MT_Month%.2d.csv";
        for (int j = 0; j < sq.size(); j++){
           MT.push_back(ReadCsvValue(filename, i, sq[j].lat, sq[j].lon));    
        }
        itu_v.MonthlyTotal.push_back(BilinearInterpolation(MT,sq,loc.lat,loc.lon,latMap_or,lonMap_or));
        MT.clear();     
    } 

    //
    for (int i = 0; i < 12; i++){
        itu_v.Temperature[i] -= 273.15;
        if (itu_v.Temperature[i]>=0){
            itu_v.r.push_back(pow(0.578,0.083*itu_v.Temperature[i]));
        }
        else{
            itu_v.r.push_back(0.5874);
        }
        itu_v.P_rain.push_back(itu_v.MonthlyTotal[i]/(24*control.monthdays[i]*itu_v.r[i]));
        if(itu_v.P_rain[i]>0.7){
            itu_v.P_rain[i] = 0.7;
            itu_v.r[i] = 100*itu_v.MonthlyTotal[i]/(70*24);
        }
    }
    
};

} // namespace rainprop
