#ifndef EVENT_H
#define EVENT_H

#include "Station.h"
class Event
{
protected:
	int time;
	int id;
public:
	Event(int Time, int ID) {
		time = Time;
		id = ID;
	}
	virtual void execute(Station* stations, int numStations)= 0;
	int getTime() {
		return time ;
	}
};

#endif EVENT_H