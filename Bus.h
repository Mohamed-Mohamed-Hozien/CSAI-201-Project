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
    Bus::Bus(string type, unsigned int capacity, unsigned int passengersNum, string journey, string checkup, string moveTime){
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

    string Bus::getBusType() 
    {
       return busType;
    }
    unsigned int Bus::getBusCapacity() 
    {
        return busCapacity;
    }
    unsigned int Bus::getpassengersNum()
    {
        return passengersCount;
    }
    string Bus::getCurrentJourney() 
    {
        return currentJourney;
    }
    string Bus::getCheckupTime()
    {
        return checkupTime;
    }
    string Bus::getMoveTimeLastStation()
    {
        return movetimeLaststation;
    }


    void Bus::setBusType(string type) 
    {
        busType = type;
    }
    void Bus::setBusCapacity(unsigned int capacity) 
    {
        busCapacity = capacity;
    }
    void Bus::setpassengersNum(unsigned int passengersNum)
    {
        passengersCount = passengersNum;
    }
    void Bus::setCurrentJourney(string journey)
    {
        currentJourney = journey;
    }
    void Bus::setCheckupTime(string checkup)
    {
        checkupTime = checkup;
    }
    void Bus::setMoveTimeLastStation(string moveTime)
    {
        movetimeLaststation = moveTime;
    }
    // bool Bus::insertPassenger(Passenger& newPassenger) {
    // if (passengersCount < capacity) 
    // {
    //     passengers[passengersCount++] = newPassenger;
    //     return true;
    // } 
    // return false;
};

#endif
