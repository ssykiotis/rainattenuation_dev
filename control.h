#ifndef CONTROL_H
#define CONTROL


// using namespace ns3;
#include <vector>
#include "structs.h"


namespace rainprop{



class Control{
    
public:

    Control();

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

private:

    void SetMonthdays();
    void SetMonthhours();

    Cords loc;                                        
    double f;                                    
    double dist;                                    
    int FSMC_gran;
    double FSMC_states;
    
    

};
}

#endif