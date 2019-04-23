#include "control.h"
#include <iostream>

namespace rainprop{

    Control::Control(){
        locLat = 0;
        locLon = 0;
        f = 0;
        dist = 0;
        FSMC_states = 0;
        FSMC_gran = 1;
        SetMonthdays(monthdays);
        SetMonthhours(monthdays,monthhours);    
    };

    void Control::SetMonthdays(double monthdays[]){
        monthdays[0] = 31;
        monthdays[1] = 28;
        monthdays[2] = 31;
        monthdays[3] = 30;
        monthdays[4] = 31;
        monthdays[5] = 30;
        monthdays[6] = 31;
        monthdays[7] = 31;
        monthdays[8] = 30;
        monthdays[9] = 31;
        monthdays[10] = 30;
        monthdays[11] = 31;
    };

    void Control::SetMonthhours(double monthdays[12],double monthhours[]){

        for (int i = 0; i < 12; i++)
        {
            monthhours[i] = 24*monthdays[i];
        }
    };

    void Control::SetLocation(double lon, double lat){
        this->locLon = lon;
        this->locLat = lat;
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

    double Control::GetLocationLon(){
        return this->locLon;
    };

    double Control::GetLocationLat(){
         return this->locLat;
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

    void Control::print(){
        std::cout << "Hello World";
    };

}