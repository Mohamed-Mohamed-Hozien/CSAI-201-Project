#ifndef LEEVENT_
#define LEEVENT_

#include "Event.h"
#include "Station.h"
#include "Passenger.h"
using namespace std;

class LeaveEvent : public Event {
public:
    LeaveEvent(int time, int id) : Event(time, id, "Leave") {}
    int getID()  { return id; }
    void execute(Station* stations, int numStations) override {
            stations[id].removePassenger(id);
    }
};

#endif 