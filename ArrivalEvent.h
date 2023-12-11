#ifndef ARREVENT_
#define ARREVENT_

#include "Event.h"
#include "Station.h"
#include "Passenger.h"
using namespace std;

class ArrivalEvent : public Event {
    int passenegerType;
    int startStation;
    int endStation;
    int priority;

public:
    ArrivalEvent(int time, int id, int passenegerType, int startStation, int endStation, int priority = -1)
        : Event(time, id),
          passenegerType(passenegerType), startStation(startStation), endStation(endStation), priority(priority) {}

    void execute(Station* stations, int numStations) override {
        
            Passenger passenger(passenegerType, id, time, startStation, endStation);

    }
};

#endif ARREVENT_