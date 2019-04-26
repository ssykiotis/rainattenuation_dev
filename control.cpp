#include "control.h"
#include <vector>

namespace rainprop{

    Control::Control(){
        loc.lat = 0;
        loc.lon = 0;
        f = 0;
        dist = 0;
        FSMC_states = 0;
        FSMC_gran = 1;
        SetMonthdays();
        SetMonthhours();
    };

    Control::Control(double lat,double lon){
        this->loc.lat = lat;
        this->loc.lon = lon;
        f = 0;
        dist = 0;
        FSMC_states = 0;
        FSMC_gran = 1;
        SetMonthdays();
        SetMonthhours();
        ComputeMonthhoursCumSum();
    };

    void Control::SetMonthdays(){
        monthdays.push_back(31);
        monthdays.push_back(28);
        monthdays.push_back(31);
        monthdays.push_back(30);
        monthdays.push_back(31);
        monthdays.push_back(30);
        monthdays.push_back(31);
        monthdays.push_back(31);
        monthdays.push_back(30);
        monthdays.push_back(31);
        monthdays.push_back(30);
        monthdays.push_back(31);
    };

    void Control::SetMonthhours(){

        monthhours.push_back(744);
        monthhours.push_back(672);
        monthhours.push_back(744);
        monthhours.push_back(720);
        monthhours.push_back(744);
        monthhours.push_back(720);
        monthhours.push_back(744);
        monthhours.push_back(744);
        monthhours.push_back(720);
        monthhours.push_back(744);
        monthhours.push_back(720);
        monthhours.push_back(744);
    };

    void Control::SetLocation(double lat, double lon){
       Cords loc = {lat,lon};
       this-> loc = loc;
    };

    void Control::SetFrequency(double freq){
        this->f = freq;
    };

    void Control::SetDistance(double dist){
        this->dist = dist;
    };

    void Control::SetFSMCSettings(int granularity,int states){
        this->FSMC_gran = granularity;
        this->FSMC_states = states;
    };

    Cords Control::GetLocation(){
        return this->loc;
    };

    double Control::GetFrequency(){
        return this->f;
    };

    double Control::GetDistance(){
        return this->dist;
    };

    int Control::GetFSMCStates(){
        return this->FSMC_states;
    };

    int Control::GetFSMCGran(){
        return this->FSMC_gran;
    };

    void Control::ComputeMonthhoursCumSum(){
        std::vector<int> v_cum;
        v_cum.push_back(0);

        for (int i = 1; i < monthhours.size()+1; i++)
        {
          v_cum.push_back( v_cum[i-1] + monthhours [i-1] );
        }

        this->monthhours_cumsum = v_cum;
    };

}