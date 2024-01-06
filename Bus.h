#include <iostream>
#include "Passenger.h"
#include "PriorityQueue.h"
#ifndef BUS_H
#define BUS_H
using namespace std;


class Bus
{
    int busType; // 1 for Mbus and 2 for Wbus
    unsigned int busCapacity;
    unsigned int passengersCount;
    int currentJourney;
    int checkupTime;
    int movetimeLaststation;
    int direction;
    int nextStation;

    public:
    PriorityQueue<Passenger*> onBoardedPassengers;


    Bus(int type, unsigned int capacity, unsigned int passengersNum, int journey, int checkup, int moveTime)
    {
    busType = type;
    busCapacity = capacity;
    currentJourney = journey;
    checkupTime = checkup;
    movetimeLaststation = moveTime;
    passengersCount = passengersNum;
    direction = 1;
    nextStation =1;
    }
    Bus() : busType(-1), busCapacity(0), passengersCount(0),
        currentJourney(0), checkupTime(-1), movetimeLaststation(-1), direction(0), nextStation(1) {}


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
    void setNextStation(int next)
    {
        nextStation = next;
    }
    int getNextStation()
    {
        return nextStation;
    }
    bool insertPassenger(Passenger* newPassenger, int time) 
    {
        if (newPassenger->getEndStation() > newPassenger->getStartStation()){
            if (passengersCount < busCapacity) 
            {
                //multiplied the end station by -1 in order to have higher priority for people leaving the bus in smaller station.
                //ex. start = 1, end = 3. then the priority becomes -3
                //ex. start = 1, end = 5, then the priority becomes -5
                //here th efirst example will be on th etop of the queue before the second
                onBoardedPassengers.enqueue(newPassenger, -1 * newPassenger->getEndStation());
                passengersCount++;
                newPassenger->setGetOnTime(time);
                return true;
            } 
            return false;
        }
        else {
            if (passengersCount < busCapacity) 
            {
                onBoardedPassengers.enqueue(newPassenger, newPassenger->getEndStation());
                passengersCount++;
                newPassenger->setGetOnTime(time);
                return true;
            } 
            return false;
        }
    }

    // with the intention of being used in the station class to empty the bus at the front of the queue of the station    
void removePassenger(int stationNum, LinkedList<Passenger*>& removedPassengers,int time) {
    Passenger* passenger = nullptr;

    while (passengersCount > 0) {
        onBoardedPassengers.getFront(passenger);

        if (passenger->getEndStation() == stationNum) {
            onBoardedPassengers.dequeue(passenger);
            removedPassengers.InsertEnd(passenger); // Add the removed passenger to the linked list
            passengersCount--;
            passenger->setGetOffTime(time);
        } else {
            // Stop the loop when we find a passenger whose end station is not stationNum
            break;
        }
    }
}

    bool isFull(){
        return passengersCount < busCapacity;
    }
    


    
    // friend std::ostream& operator<<(std::ostream& os, const Bus& bus) {
    //     os << "Bus Type: " << bus.busType << "\n"
    //         << "Bus Capacity: " << bus.busCapacity << "\n"
    //         << "Passengers Count: " << bus.passengersCount << "\n"
    //         << "Current Journey: " << bus.currentJourney << "\n"
    //         << "Checkup Time: " << bus.checkupTime << "\n"
    //         << "Move Time Last Station: " << bus.movetimeLaststation << "\n"
    //         << "Direction: " << bus.direction << "\n";

    //     os << "Passengers:\n";
    //     for (unsigned int i = 0; i < bus.passengersCount; ++i) {
    //         os << "Passenger " << i + 1 << ":\n" << bus.passengers[i] << "\n";
    //     }

    //     return os;
    // }


};

#endif