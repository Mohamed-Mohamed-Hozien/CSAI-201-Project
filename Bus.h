#include <iostream>
#include "Passenger.h"
#ifndef BUS_H
#define BUS_H
using namespace std;


class Bus
{
    int busType; // 1 for Mbus and 2 for Wbus
    unsigned int busCapacity;
    unsigned int passengersCount;
    Passenger* passengers; // Array of type Passenger
    int currentJourney;
    int checkupTime;
    int movetimeLaststation;
    int direction; 

    public:

    Bus(int type, unsigned int capacity, unsigned int passengersNum, int journey, int checkup, int moveTime)
    {
    busType = type;
    busCapacity = capacity;
    currentJourney = journey;
    checkupTime = checkup;
    movetimeLaststation = moveTime;
    passengersCount = passengersNum;
    passengers = new Passenger[capacity];
    direction = 1;
    }

    Bus() : busType(-1), busCapacity(0), passengersCount(0), passengers(nullptr),
        currentJourney(-1), checkupTime(-1), movetimeLaststation(-1), direction(0) {}


    ~Bus() {
    delete[] passengers;
    }

    int getDirection()
    {
        return direction;
    }
    int getBusType() 
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
    int getCurrentJourney() 
    {
        return currentJourney;
    }
    int getCheckupTime()
    {
        return checkupTime;
    }
    int getMoveTimeLastStation()
    {
        return movetimeLaststation;
    }
    Passenger* getPassengers() 
    {
        return passengers;
    }

    void setDirection(int dir)
    {
        direction = dir;
    }

    void setBusType(int type) 
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
    void setCurrentJourney(int journey)
    {
        currentJourney = journey;
    }
    void setCheckupTime(int checkup)
    {
        checkupTime = checkup;
    }
    void setMoveTimeLastStation(int moveTime)
    {
        movetimeLaststation = moveTime;
    }
    
    bool insertPassenger(Passenger& newPassenger) 
    {
    if (passengersCount < busCapacity) 
    {
        passengers[passengersCount++] = newPassenger;
        return true;
    } 
    return false;
    }


    
    friend std::ostream& operator<<(std::ostream& os, const Bus& bus) {
        os << "Bus Type: " << bus.busType << "\n"
            << "Bus Capacity: " << bus.busCapacity << "\n"
            << "Passengers Count: " << bus.passengersCount << "\n"
            << "Current Journey: " << bus.currentJourney << "\n"
            << "Checkup Time: " << bus.checkupTime << "\n"
            << "Move Time Last Station: " << bus.movetimeLaststation << "\n"
            << "Direction: " << bus.direction << "\n";

        os << "Passengers:\n";
        for (unsigned int i = 0; i < bus.passengersCount; ++i) {
            os << "Passenger " << i + 1 << ":\n" << bus.passengers[i] << "\n";
        }

        return os;
    }


};

#endif