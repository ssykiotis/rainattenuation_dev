#ifndef CONTROL_H
#define CONTROL

#include <vector>

#include "structs.h"

// using namespace ns3;



namespace rainprop{

class Control{
    
public:
    Control();
    Control(double lat,double lon);

    void SetLocation(double lon, double lat);
    void SetFrequency(double freq);
    void SetDistance(double dist);
    void SetFSMCSettings(int granularity,int states);


    Cords GetLocation();
    double GetFrequency();
    double GetDistance();
    int GetFSMCStates();
    int GetFSMCGran();

    std::vector<int> monthdays;
    std::vector<int> monthhours;
    std::vector<int> monthhours_cumsum;

private:

    void SetMonthdays();
    void SetMonthhours();
    void ComputeMonthhoursCumSum();

    Cords loc;                                        
    double f;                                    
    double dist;                                    
    int FSMC_gran;
    double FSMC_states;   

};
}

#endif