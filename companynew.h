#pragma once
#include "LeaveEvent.h"
#include "ArrivalEvent.h"
#include "Station.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include "LinkedList.h"
// #include "UI.h"
using namespace std;
class Company
{
	Station *stationsArray;
	int maxWaitingTime;
	LinkedList<Passenger*> passengers;
	LinkedList<Bus> buses;



public:
	Queue<Event*> events;

	Event* createArrivalEvent(ifstream& file){
        string passengerType;
        int hour, minute, id, startStation, endStation, type = -1;
        char _;
        file >> passengerType >> hour >> _ >> minute >> id >> startStation >> endStation;
        if (passengerType == "SP") {
            string specialType;
            file >> specialType;
            if (specialType == "aged")
                type = 4;
            else if (specialType == "POD")
                type = 3;
            else
                type = 2;
        }
        else if (passengerType == "NP") {
            type = 1;
        }
        else if (passengerType == "WP") {
            type = 5;
        }
        int time  = hour * 60 + minute;
        return new ArrivalEvent(time, id, type, startStation, endStation);
    }

    Event* createLeaveEvent(ifstream& file){
        int hour, minute, id;
        char _;
        file >> hour >> _ >> minute >> id;
        int time = hour * 60 + minute;
        return new LeaveEvent(time, id);
    }



	void readInputFile(string fileName) {
		ifstream file(fileName);
		if (!file.is_open()) {
        cout << "Error opening the file " << fileName << endl;
        return;
        }
		int numberOfStations = 0;
		file >> numberOfStations;

		numberOfStations++;
        stationsArray = new Station[numberOfStations];
		int i =0;
        while ( i<numberOfStations) {
			stationsArray[i] = Station(i);
            i++;
		}
		//read max waiting time
		file >> maxWaitingTime;
        //read events
		int numberOfEvents;
		file >> numberOfEvents;
		while (numberOfEvents--) {
			char eventType;
			file >> eventType;

			Event* tempEvent;
            if (eventType == 'A') {
                tempEvent = createArrivalEvent(file);
            }
            else if (eventType == 'L') {
                tempEvent = createLeaveEvent(file);
            }
			events.enqueue(tempEvent);
		}
		file.close();
	}
};

