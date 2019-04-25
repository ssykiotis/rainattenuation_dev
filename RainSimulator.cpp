#include "RainSimulator.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include "math.h"

namespace rainprop
{

RainSimulator::RainSimulator(double lat, double lon)
{
    this->loc.lon = lon;
    this->loc.lat = lat;
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

void RainSimulator::ReadCsvValue(std::string target, const char *filename, int latMinIndex, int lonMinIndex)
{
    std::vector<double> v;
    for (int i = 1; i < 13; i++)
    {
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

        v.push_back(atof(val.c_str()));
    }

    if (target == "T")
    {
        itu_v.Temperature = v;
    }
    else if (target == "MT")
    {
        itu_v.MonthlyTotal = v;
    }
};

ITUR837_values RainSimulator::ITUR837_calculation()
{

    std::vector<double> latMap = ReadCoordinates("rain_data/ITU/temperature/LAT_T.csv");
    std::vector<double> lonMap = ReadCoordinates("rain_data/ITU/temperature/LON_T.csv");

    for (int i = 0; i < latMap.size(); i++)
    {
        latMap[i] = fabs(latMap[i] - loc.lat);
    }
    for (int i = 0; i < lonMap.size(); i++)
    {
        lonMap[i] = fabs(lonMap[i] - loc.lon);
    }

    int latMinIndex = FindMinIndex(latMap);
    int lonMinIndex = FindMinIndex(lonMap);
    ReadCsvValue("T", "rain_data/ITU/temperature/T_Month%.2d.csv", latMinIndex, lonMinIndex);

    latMap.clear();
    lonMap.clear();

    latMap = ReadCoordinates("rain_data/ITU/monthly_total/LAT_MT.csv");
    lonMap = ReadCoordinates("rain_data/ITU/monthly_total/LON_MT.csv");

    for (int i = 0; i < latMap.size(); i++)
    {
        latMap[i] = fabs(latMap[i] - loc.lat);
    }
    for (int i = 0; i < lonMap.size(); i++)
    {
        lonMap[i] = fabs(lonMap[i] - loc.lon);
    }

    latMinIndex = FindMinIndex(latMap);
    lonMinIndex = FindMinIndex(lonMap);
    ReadCsvValue("MT", "rain_data/ITU/monthly_total/MT_Month%.2d.csv", latMinIndex, lonMinIndex);
};

} // namespace rainprop
