#ifndef EVENT_H
#define EVENT_H

#include "Station.h"
class Event
{
protected:
	int time;
	int id;
	string type;
public:
	Event(int Time, int ID, string type) {
		this->type = type;
		time = Time;
		id = ID;
	}
	virtual void execute(Station* stations, int numStations)= 0;
	string getType() {
		return type;
	}
	int getTime() {
		return time ;
	}
	int getId() { return id; }
};

#endif 