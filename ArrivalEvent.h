#ifndef ARREVENT_
#define ARREVENT_

#include "Event.h"
#include "Station.h"
#include "Passenger.h"
using namespace std;

class ArrivalEvent : public Event
{
    int passenegerType;
    int startStation;
    int endStation;

public:
    ArrivalEvent(int time, int id, int passenegerType, int startStation, int endStation)
        : Event(time, id, "Arrival"),
          passenegerType(passenegerType), startStation(startStation), endStation(endStation) {}

    void execute(Station *stations, int numStations) override
    {

        Passenger passenger(passenegerType, id, time, startStation, endStation);
    }
};

#endif