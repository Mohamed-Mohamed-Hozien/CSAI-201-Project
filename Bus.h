#include <iostream>
#ifndef BUS_H
#define BUS_H
using namespace std;

class Bus
{
    string busType;
    unsigned int busCapacity;
    unsigned int passengersCount;
    // Passenger passengers[busCapacity]; // Array of type passengers
    string currentJourney;
    string checkupTime;
    string movetimeLaststation;

    public:
    Bus(string type, unsigned int capacity, unsigned int passengersNum, string journey, string checkup, string moveTime){
    busType = type;
    busCapacity = capacity;
    currentJourney = journey;
    checkupTime = checkup;
    movetimeLaststation = moveTime;
    passengersCount = passengersNum;
    }
    // Bus::~Bus() {
    // delete[] passengers;
    // }

    string getBusType() 
    {
       return busType;
    }
    unsigned int getBusCapacity() 
    {
        return busCapacity;
    }
    unsigned int getpassengersNum()
    {
        return passengersCount;
    }
    string getCurrentJourney() 
    {
        return currentJourney;
    }
    string getCheckupTime()
    {
        return checkupTime;
    }
    string getMoveTimeLastStation()
    {
        return movetimeLaststation;
    }


    void setBusType(string type) 
    {
        busType = type;
    }
    void setBusCapacity(unsigned int capacity) 
    {
        busCapacity = capacity;
    }
    void setpassengersNum(unsigned int passengersNum)
    {
        passengersCount = passengersNum;
    }
    void setCurrentJourney(string journey)
    {
        currentJourney = journey;
    }
    void setCheckupTime(string checkup)
    {
        checkupTime = checkup;
    }
    void setMoveTimeLastStation(string moveTime)
    {
        movetimeLaststation = moveTime;
    }
    // bool insertPassenger(Passenger& newPassenger) {
    // if (passengersCount < capacity) 
    // {
    //     passengers[passengersCount++] = newPassenger;
    //     return true;
    // } 
    // return false;
};

#endif
