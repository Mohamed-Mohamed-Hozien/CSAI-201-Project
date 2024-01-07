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
	int timeBetStations;
	LinkedList<Passenger*> finishedPassengers;
	LinkedList<Bus*> inCheckUpbuses;
    int NPassengerCount;
    int SPassengerCount;
    int WPassengerCount;
    int numPromotedPassengers;
    int WbusCapacity;
    int MbusCapacity;
    int maxJourneys;
    int WcheckUpTime;
    int McheckUpTime;
    int maxWaiting;
    int BoradingDuration;
    int MbusNum;
    int WbusNum;


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
		file >> timeBetStations;
        file >> WbusNum;
        file >> MbusNum;
        file >> WbusCapacity;
        file >> MbusCapacity;
        file >> maxJourneys;
        file >> WcheckUpTime;
        file >> McheckUpTime;
        file >> maxWaiting;
        file >> BoradingDuration;


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

    //adds all the busses to the first Station
    void addBussesToFirstStation() {
        int maxBusNum = max(MbusNum, WbusNum);
        for (int i = 0; i < maxBusNum; i++) {
            if (i < MbusNum) {
                Bus* bus = new Bus(1, MbusCapacity, 0, 0, McheckUpTime, 0);
                stationsArray[0].addBus2Station(bus);
            }
            if (i < WbusNum) {
                Bus* bus = new Bus(2, WbusCapacity, 0, 0, WcheckUpTime, 0);
                stationsArray[0].addBus2Station(bus);
            }
        }
    }
    
    void simulate(){
        readInputFile("random_file.txt");
        int time = 0;
        int lastBusOuttime = 15; //time since last bus release from station 0, innitialized with 15 to release the first bus immediately
        addBussesToFirstStation(); 
        while (time < 24*60){
            if (lastBusOuttime >=15){

            }
        }
    }
};

