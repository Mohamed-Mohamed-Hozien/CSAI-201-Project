
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
    int getOffTime; // movingtime4
    int finishTime;
    int movingTime;

public:
    Passenger(int t, int ID, int aTime, int sStation, int eStation)
    {
        id = ID;
        type = t; // Normal = 1 , pregnant = 2, POD = 3, aged = 4 , WP = 5
        arrivalTime = aTime;
        startStation = sStation;
        endStation = eStation;
        getOnTime = -1;
        getOffTime = -1;
        finishTime = -1;
        movingTime = -1;
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
        movingTime = -1;
    }

    int getMovingTime()
    {
        return movingTime;
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

    void setMovingTime(int mTime)
    {
        movingTime = mTime;
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
    friend std::ostream &operator<<(std::ostream &os, const Passenger &passenger)
    {
        os << "Passenger ID: " << passenger.id << ", "
           << "Type: " << passenger.type << ", "
           << "Arrival Time: " << passenger.arrivalTime << ", "
           << "Start Station: " << passenger.startStation << ", "
           << "End Station: " << passenger.endStation << ", "
           << "Get On Time: " << passenger.getOnTime << ", "
           << "Get Off Time: " << passenger.getOffTime << ", "
           << "Finish Time: " << passenger.finishTime << "\n";

        return os;
    }

    int getWaitingTime()
    {
        return movingTime - arrivalTime;
    }
};

#endif