#ifndef CONTROL_H
#define CONTROL_H

#include <stdlib.h>
#include <string>
#include <vector>


namespace rainprop{

    struct Cords{
        double lat;
        double lon;
    };  

    struct Koppen{
        double lat;
        double lon;
        std::string region;
    };

    struct ITUR837_values{
        std::vector<double> Temperature;
        std::vector<double> MonthlyTotal;
        std::vector<double> P_rain;
        std::vector<double> r; 
    };

    struct RainEvents{
        int i;
        int j;
        int length;
    };

    struct Matrix {
        std::vector< std::vector<double> > v;
    };
}

#endif