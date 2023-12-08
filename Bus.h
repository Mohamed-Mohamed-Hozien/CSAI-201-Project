#include <iostream>
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
    Bus(string type, unsigned int capacity, unsigned int passengersNum, string journey, string checkup, string moveTime);
    // ~Bus();

    string getBusType();
    unsigned int getBusCapacity();
    unsigned int getpassengersNum();
    string getCurrentJourney();
    string getCheckupTime();
    string getMoveTimeLastStation();

    void setBusType(string type);
    void setBusCapacity(unsigned int capacity);
    void setpassengersNum(unsigned int passengersNum);
    void setCurrentJourney(string journey);
    void setCheckupTime(string checkup);
    void setMoveTimeLastStation(string moveTime);
    // bool insertPassenger(Passenger& newPassenger);
};