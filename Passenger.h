
#ifndef _PASSENGER
#define _PASSENGER

#include <iostream>

class Passenger
{
private:
    int id;
    int type;
    int arrivalTime; 
    int startStation;
    int endStation;
    int getOnTime;
    int getOffTime;
    int finishTime;

public:
    Passenger(int t, int ID, int aTime, int sStation, int eStation, int onTime, int offTime)
    {
        id = ID;
        type = t; // Normal = 1 , pregnant = 2, POD = 3, aged = 4 , WP = 5
        arrivalTime = aTime;
        startStation = sStation;
        endStation = eStation;
        getOnTime = onTime;
        getOffTime = offTime;
        finishTime = -1;
    }

    // default constructor
    Passenger()
    {
        id = -1;
        type = -1;
        arrivalTime = -1;
        startStation = -1;
        endStation = -1;
        getOnTime = -1;
        getOffTime = -1;
        finishTime = -1;
    }
    int getID()
    {
        return id;
    }
    int getType()
    {
        return type;
    }
    int getArrivalTime()
    {
        return arrivalTime;
    }
    int getStartStation()
    {
        return startStation;
    }
    int getEndStation()
    {
        return endStation;
    }
    int getGetOnTime()
    {
        return getOnTime;
    }
    int getGetOffTime()
    {
        return getOffTime;
    }
    int getFinishTime()
    {
        return finishTime;
    }

    void setID(int ID)
    {
        id = ID;
    }

    void setType(int t)
    {
        type = t;
    }

    void setArrivalTime(int aTime)
    {
        arrivalTime = aTime;
    }
    void setStartStation(int sStation)
    {
        startStation = sStation;
    }
    void setEndStation(int eStation)
    {
        endStation = eStation;
    }
    void setGetOnTime(int onTime)
    {
        getOnTime = onTime;
    }
    void setGetOffTime(int offTime)
    {
        getOffTime = offTime;
    }

    void setFinishTime(int fTime)
    {
        finishTime = fTime;
    }
    
    int calculateWaitTime(int movingTime)
    {
        return movingTime - arrivalTime;
    }

    int calculaTripTime() // getOffTime - getOnTime
    {
        return getOffTime - getOnTime;
    }
    friend std::ostream& operator<<(std::ostream& os, const Passenger& passenger) {
        os << "Passenger ID: " << passenger.id << "\n"
            << "Type: " << passenger.type << "\n"
            << "Arrival Time: " << passenger.arrivalTime << "\n"
            << "Start Station: " << passenger.startStation << "\n"
            << "End Station: " << passenger.endStation << "\n"
            << "Get On Time: " << passenger.getOnTime << "\n"
            << "Get Off Time: " << passenger.getOffTime << "\n"
            << "Finish Time: " << passenger.finishTime << "\n";

        return os;
    }

};

#endif