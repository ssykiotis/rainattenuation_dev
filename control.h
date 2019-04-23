// using namespace ns3;
namespace rainprop{

class Control{
    
public:

    Control();

    void SetLocation(double lon, double lat);
    void SetFrequency(double freq);
    void SetDistance(double dist);
    void SetFSMCSettings(int granularity,int states);

    double GetLocationLon();
    double GetLocationLat();
    double GetFrequency();
    double GetDistance();
    int GetFSMCStates();
    int GetFSMCGran();

    void print();

private:

    void SetMonthdays(double monthdays[]);
    void SetMonthhours(double monthdays[],double monthhours[]);

    double locLat;                                   
    double locLon;                               
    double monthdays[];
    double monthhours[];          
    double f;                                    
    double dist;                                    
    int FSMC_gran;
    double FSMC_states;

};
}